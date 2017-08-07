#
# (c) 2017 Aleph Objects, Inc.
#
# The code in this page is free software: you can
# redistribute it and/or modify it under the terms of the GNU
# General Public License (GNU GPL) as published by the Free Software
# Foundation, either version 3 of the License, or (at your option)
# any later version.  The code is distributed WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
#

# Marlin implements an error correcting scheme on the serial connections.
# GCode commands are sent with a line number and a checksum. If Marlin
# detects an error, it requests that the transmission resume from the
# last known good line number.
#
# In addition to this resend mechanism, Marlin also implements flow
# control. Sent commands are acknowleged by "ok" when complete.
# However, to optimize path planning, Marlin contains a command
# buffer and slicing software should send enough commands to keep
# that buffer filled (minus a reserve capacity for emergency commands
# such as an emergency STOP). It is thus necessary to send a certain
# number prior the earlier ones being acknowleged and to track how
# many commands have been sent but not yet acknowleged.
#
# The class MarlinSerialProtocol implements the error correction
# and also manages acknowlegements and flow control.
#
# The prototypical use case for this class is as follows:
#
#   for line in enumerate(gcode):
#     serial.sendCommand(line)
#     while(not serial.clearToSend()):
#       serial.readLine()
#

import functools

class GCodeHistory:
  """This class implements a history of GCode commands. Right now, we
     keep the entire history, but this probably could be reduced to a
     smaller range. This class keeps a pointer to the position of
     the first unsent command, which typically is the one just recently
     appended, but after a resend request from Marlin that position can
     rewound to further back."""
  def __init__(self):
    self.clear()

  def clear(self):
    self.list = [None] # Pad so the first element is at index 1
    self.pos  = 1

  def append(self, cmd):
    self.list.append(cmd)

  def rewindTo(self, position):
    self.pos = max(1,min(position, len(self.list)))

  def getAppendPosition(self):
    """Returns the position at which the next append will happen"""
    return len(self.list)

  def getNextCommand(self):
    """Returns the next unsent command."""
    if(not self.atEnd()):
      res = self.pos, self.list[self.pos]
      self.pos += 1;
      return res

  def atEnd(self):
    return self.pos == len(self.list)

class MarlinSerialProtocol:
  """This class implements the Marlin serial protocol, such
  as adding a checksum to each line, replying to resend
  requests and keeping the Marlin buffer full"""
  def __init__(self, serial):
    self.serial                 = serial
    self.marlinBufSize          = 4
    self.marlinReserve          = 1
    self.pendingOk              = 0
    self.history                = GCodeHistory()
    self.restart()

  def _stripCommentsAndWhitespace(self, str):
    return str.split(';', 1)[0].strip()

  def _replaceEmptyLineWithM105(self, str):
    """Marlin will not accept empty lines, so replace blanks with M115 (Get Extruder Temperature)"""
    return "M105" if str == "" else str

  def _computeChecksum(self, data):
    """Computes the GCODE checksum, this is the XOR of all characters in the payload, including the position"""
    return functools.reduce(lambda x,y: x^y, map(ord, data))

  def _addPositionAndChecksum(self, position, cmd):
    """An GCODE with line number and checksum consists of N{position}{cmd}*{checksum}"""
    data = "N%d%s"    % (position, cmd)
    return "N%d%s*%d" % (position, cmd, self._computeChecksum(data))

  def _sendToMarlin(self):
    """Sends as many commands as are available and to fill the Marlin buffer.
       Commands are read from the history. Generally only the most recently
       appended command is sent; but after a resend request, we may be
       further back in the history than that"""
    while(not self.history.atEnd() and self.marlinBufferCapacity() > 0):
      pos, cmd = self.history.getNextCommand();
      self.serial.write(cmd + '\n')
      self.serial.flush()
      self.pendingOk += 1

  def _isResend(self, line):
    """If the line is a resend command from Marlin, returns the line number. This
       code was taken from Cura 1, I do not know why it is so convoluted."""
    if "resend" in line.lower() or "rs" in line:
      try:
        return int(line.replace("N:"," ").replace("N"," ").replace(":"," ").split()[-1])
      except:
        if "rs" in line:
          return int(line.split()[1])

  def _resendFrom(self, position):
    """If Marlin requests a resend, we need to backtrack."""
    self.history.rewindTo(position)
    self.pendingOk    = 1

    # When receive a resend request, we must temporarily
    # switch to sending commands one at a time, otherwise
    # buffering could lead to additional errors, which
    # cause Marlin to send more resend requests and
    # to us never recovering.
    self.resyncCountdown = self.marlinBufSize

  def _flushReadBuffer(self):
    while self.serial.readline() != b"":
      pass

  def sendCommand(self, cmd):
    """Sends a command. Should only be called if clearToSend() is true"""
    cmd = self._stripCommentsAndWhitespace(cmd)
    cmd = self._replaceEmptyLineWithM105(cmd)
    cmd = self._addPositionAndChecksum(self.history.getAppendPosition(), cmd)
    # Add command to the history, but immediately send it out.
    self.history.append(cmd)
    self._sendToMarlin()

  def readLine(self):
    """This reads data from Marlin. If no data is available '' will be returned after
       the comm timeout. This *must* be called periodically to keep outgoing data moving
       from the buffers."""
    self._sendToMarlin()
    line = self.serial.readline()
    if self._isResend(line):
      # When a resend is requested, handle it.
      # Return blank to caller.
      position = self._isResend(line)
      self._resendFrom(position)
      line = b""
    elif line.startswith(b"ok"):
      self.pendingOk -= 1
      # Decrement the resync countdown so we
      # can eventually return to buffered mode
      if self.resyncCountdown > 0:
        self.resyncCountdown -= 1

    return line

  def clearToSend(self):
      self._sendToMarlin()
      return self.marlinBufferCapacity() > 0

  def marlinBufferCapacity(self):
    """Returns how many buffer positions are open in Marlin. This is the difference between
       the non-reserved buffer spots and the number of not yet acknowleged commands"""
    if self.resyncCountdown > 0:
      # If we are have recently received a resend request, go
      # into unbuffered line-by-line mode temporarily.
      return 0 if self.pendingOk else 1
    else:
      return (self.marlinBufSize - self.marlinReserve) - self.pendingOk

  def restart(self):
    """Clears all buffers and issues a M110 to Marlin. Call this at the start of every print."""
    self. _flushReadBuffer()
    self.resyncCountdown = self.marlinBufSize
    self.history.clear()
    self.sendCommand(b"M110")

  def close(self):
    self.serial.close()