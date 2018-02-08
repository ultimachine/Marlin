/****************************************************************************
 *   Written By Marcio Teixeira 2018 - Aleph Objects, Inc.                  *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <http://www.gnu.org/licenses/>.                              *
 ****************************************************************************/

class Marlin_LCD_API {
  public:
    typedef const __FlashStringHelper *progmem_str;

    enum axis_t {
      X,
      Y,
      Z,
      E0,
      E1
    };

    static const uint8_t extruderCount;
    static const uint8_t fanCount;

    static const float getActualTemp_celsius(const uint8_t extruder);
    static const float getTargetTemp_celsius(const uint8_t extruder);
    static const float getFan_percent(const uint8_t fan);

    static const float getAxisPosition_mm(const axis_t axis);
    static const float getAxisSteps_per_mm(const axis_t axis);
    static const uint8_t getProgress_percent();
    static const uint32_t getProgress_seconds_elapsed();
    static const uint8_t getFeedRate_percent();
    static const float getZOffset_mm();
    static const bool isAxisPositionKnown(const axis_t axis);
};

#if defined(MSG_MARLIN)
const uint8_t Marlin_LCD_API::extruderCount = EXTRUDERS;
const uint8_t Marlin_LCD_API::fanCount      = 1;

const float Marlin_LCD_API::getActualTemp_celsius(const uint8_t extruder) {
  if(extruder) {
    thermalManager.degHotend(extruder-1);
  } else {
    thermalManager.degBed();
  }
}

const float Marlin_LCD_API::getTargetTemp_celsius(const uint8_t extruder) {
  if(extruder) {
    thermalManager.degTargetHotend(extruder-1);
  } else {
    thermalManager.degTargetBed();
  }
}

const float Marlin_LCD_API::getFan_percent(const uint8_t fan) {
 return ((fanSpeeds[fan] + 1) * 100) / 256;
}

const float Marlin_LCD_API::getAxisPosition_mm(const Marlin_LCD_API::axis_t axis) {
  switch(axis) {
    case X:  return current_position[X_AXIS];  break;
    case Y:  return current_position[Y_AXIS];  break;
    case Z:  return current_position[Z_AXIS];  break;
    case E0: return current_position[E_AXIS]; break;
    case E1: return current_position[E_AXIS+1]; break;
  }
}

const float Marlin_LCD_API::getAxisSteps_per_mm(const Marlin_LCD_API::axis_t axis) {
  return 0;
}

const uint8_t Marlin_LCD_API::getProgress_percent() {
  #if ENABLED(SDSUPPORT)
    return card.percentDone();
   #endif
}

const uint32_t Marlin_LCD_API::getProgress_seconds_elapsed() {
  const duration_t elapsed = print_job_timer.duration();
  return elapsed.value;
}

const uint8_t Marlin_LCD_API::getFeedRate_percent() {
  return feedrate_percentage;
}

const bool Marlin_LCD_API::isAxisPositionKnown(const axis_t axis) {
  switch(axis) {
    case X:  return axis_known_position[X_AXIS];  break;
    case Y:  return axis_known_position[Y_AXIS];  break;
    case Z:  return axis_known_position[Z_AXIS];  break;
  }
}
#endif