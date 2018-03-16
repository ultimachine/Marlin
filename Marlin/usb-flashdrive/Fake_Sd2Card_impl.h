/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/********************************************************************************************
 * This program/sketch is used to run a USB Thumb Drive.                                    *
 *                                                                                          *
 * NOTE - This Arduino Sketch has been modified to initialize a MAX3421E USB Host Interface *
 * chip, write 3 test files, print out the directory of the thumb drive and print out the   *
 * contents of a short .txt file.                                                           *
 *                                                                                          *
 * The code is leveraged from the following:                                                *
 *                                                                                          *
 * Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.                           *
 *                                                                                          *
 * This software may be distributed and modified under the terms of the GNU                 *
 * General Public License version 2 (GPL2) as published by the Free Software                *
 * Foundation and appearing in the file GPL2.TXT included in the packaging of               *
 * this file. Please note that GPL2 Section 2[b] requires that all works based              *
 * on this software must also be made publicly available under the terms of                 *
 * the GPL2 ("Copyleft").                                                                   *
 *                                                                                          *
 * Contact information                                                                      *
 * -------------------                                                                      *
 *                                                                                          *
 * Circuits At Home, LTD                                                                    *
 * Web      :  http://www.circuitsathome.com                                                *
 * e-mail   :  support@circuitsathome.com                                                   *
 *                                                                                          *
 * SPECIAL NOTE - In order to work with a modified Eisny or RAMBo, the SPI chip select pin  *
 * (CS) (D10) has been remapped from PORTB Pin-4 to PORTB Pin-0.  This has been done in the *
 * __AVR_ATmega2560__ section of the avrpins.h file.                                        *
 *                                                                                          *
 ********************************************************************************************/

#include <SPI.h>

//#define _usb_h_

#include "Marlin.h"
#include "../watchdog.h"

#undef MACROS_H

#define USB_HOST_SERIAL customizedSerial

#include "lib/masstorage.h"
#include "lib/masstorage.cpp"
#include "lib/message.cpp"
#include "lib/parsetools.cpp"
#include "lib/Usb.cpp"


#include "Fake_Sd2Card.h"

#define MAX_USB_RST 7

// USB host objects.v
USB usb;
BulkOnly bulk(&usb);

#define error(msg) {Serial.print("Error: "); Serial.println(msg);}

#define TIMEOUT_MILLIS 4000

//------------------------------------------------------------------------------
bool initUSB(USB* usb) {
  uint8_t current_state = 0;
  uint32_t m = millis();

  for (uint8_t i = 0; usb->Init(1000) == -1; i++)
  {
    SERIAL_ECHOLNPGM("No USB HOST Shield?");
    watchdog_reset();
    if (i > 10) {
      return false;
    }
  }

  usb->vbusPower(vbus_on);

  while ((millis() - m) < TIMEOUT_MILLIS) {
    usb->Task();
    current_state = usb->getUsbTaskState();
    if(current_state == USB_STATE_RUNNING) {
      return true;
    }
    watchdog_reset();
  }
  return false;
}

Sd2Card::Sd2Card() {
};

bool Sd2Card::init(uint8_t sckRateID, uint8_t chipSelectPin) {
  if (!initUSB(&usb))
  {
    SERIAL_ECHOLNPGM("initUSB failed");
  }
  else
  {
    SERIAL_ECHOLNPGM("USB Initialized\n");
  }

  if(!bulk.LUNIsGood(0)) {
    SERIAL_ECHOLNPGM("LUN zero is not good\n");
    return false;
  }

  SERIAL_ECHOLNPAIR("LUN Capacity: ",bulk.GetCapacity(0));

  const uint32_t sectorSize = bulk.GetSectorSize(0);
  if(sectorSize != 512) {
    SERIAL_ECHOLNPAIR("Expecting sector size of 512, got: ",sectorSize);
    return false;
  }

  return true;
}

bool Sd2Card::readBlock(uint32_t block, uint8_t* dst) {
  return bulk.Read(0, block, 512, 1, dst) == 0;
}

bool Sd2Card::writeBlock(uint32_t blockNumber, const uint8_t* src) {
  return bulk.Write(0, blockNumber, 512, 1, src) == 0;
}

