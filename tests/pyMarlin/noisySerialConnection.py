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

import random
import string

class NoisySerialConnection:
  """Wrapper class which injects character noise into the outgoing packets
     of a serial connection for testing Marlin's error correction"""
  def __init__(self, serial):
    self.serial     = serial
    self.errorRate  = 0

  def _corruptStr(self, str):
    """Introduces a single character error on a string"""
    charToCorrupt = random.randint(0, len(str) - 1)
    return str[:charToCorrupt] + random.choice(string.ascii_letters) + str[charToCorrupt+1:]

  def write(self, data):
    if(random.random() < self.errorRate):
      data = self._corruptStr(data)
    self.serial.write(data)

  def readline(self):
    return self.serial.readline()

  def flush(self):
    self.serial.flush()

  def close(self):
    self.serial.close()

  def setErrorRate(self, badWrites, totalWrites):
    """Inserts a single character error into every badWrites out of totalWrites"""
    self.errorRate = float(badWrites)/float(totalWrites)