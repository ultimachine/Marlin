#!/usr/bin/python
#
# A tool to send a GCODE file to Marlin via a serial or USB connection.
#
# This tool can also exercise error correction and recovery in Marlin by
# corrupting a fraction of the GCODE packets that are sent.
#

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

from __future__ import print_function
from pyMarlin   import *

import argparse
import serial

UseNoisySerial = True

def load_gcode(filename):
  with open(filename, "r") as f:
    gcode = f.readlines()
  print("Read %d lines" % len(gcode))
  return gcode

def send_gcode_test(filename, serial):
  gcode = load_gcode("test.gco");

  for i, line in enumerate(gcode):
    serial.sendCommand(line)
    while(not serial.clearToSend()):
      serial.readLine()
    if(i % 1000 == 0):
      print("Progress: %d" % (i*100/len(gcode)), end='\r')

parser = argparse.ArgumentParser(description='''sends gcode to a printer while injecting errors to test error recovery.''')
parser.add_argument('-f', '--fake',   help='Use a fake Marlin simulation instead of serial port, for self-testing.', action='store_false', dest='port')
parser.add_argument('-p', '--port',   help='Serial port.', default='/dev/ttyACM1')
parser.add_argument('-e', '--errors', help='Corrupt 1 out N lines to exercise error recovery.', default='0', type=int)
parser.add_argument('-l', '--log',    help='Write log file.')
parser.add_argument('filename',       help='file containing gcode.')
args = parser.parse_args()

print()

if args.port:
  print("Serial port: ", args.port)
  sio = serial.Serial(args.port, 115000, timeout = 3, writeTimeout = 10000)
else:
  print("Using simulated Marlin device.")
  sio = FakeMarlinSerialDevice()

if args.log:
  print("Writing log file: ", args.log)
  chatty = LoggingSerialConnection(sio, args.log)
else:
  chatty = sio

if args.errors:
  print("1 out of %d lines will be corrupted." % args.errors)
  noisy = NoisySerialConnection(chatty)
  noisy.setErrorRate(1, args.errors)
else:
  noisy = chatty

print()

proto = MarlinSerialProtocol(noisy)
send_gcode_test(args.filename, proto)
proto.close()