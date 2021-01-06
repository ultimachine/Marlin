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

/**
 * ARCHIM2 pin assignment (pins_ARCHIM2.h)
 *
 * The Archim2 board requires Arduino Archim addons installed.
 * Add the following URL to Arduino IDE's Additional Board Manager URLs:
 * https://raw.githubusercontent.com/ultimachine/ArduinoAddons/master/package_ultimachine_index.json
 * In the Arduino IDE Board Manager search for Archim and install the package.
 * Change your target board to "Archim".
 *
 * Further information is provided by UltiMachine
 * https://github.com/ultimachine/Archim/wiki/Archim-v2.0
 * https://github.com/ultimachine/Archim/wiki
 *
 */

#ifndef __SAM3X8E__
  #error "Oops!  Make sure you have 'Archim' selected from the 'Tools -> Boards' menu."
#endif

//Schematic Pinmap
#define	DIAG1	37
#define	DIAG2	92
#define	DIAG3	48
#define	DIAG4	44
#define	DIAG5	104
#define	DIAG6	78
#define	DIAG7	19
#define	DIAG8	18
#define	DIR1	38
#define	DIR2	51
#define	DIR3	47
#define	DIR4	36
#define	DIR5	105
#define	DIR6	97
#define	DIR7	99
#define	DIR8	26
#define	DRV_EN	41
#define	Fan1	4
#define	Fan2	5
#define	Fan3	66
#define	Fan4	67
#define	Heat1	9
#define	Heat2	8
#define	Heat3	6
#define	HeatBed	7
#define	M_nCS1	59
#define	M_nCS2	49
#define	M_nCS3	45
#define	M_nCS4	107
#define	M_nCS5	101
#define	M_nCS6	102
#define	M_nCS7	25
#define	M_nCS8	27
#define	MAX_ES1	32
#define	MAX_ES2	15
#define	MAX_ES3	30
#define	MAX_ES4	98
#define	MIN_ES1	14
#define	MIN_ES2	29
#define	MIN_ES3	31
#define	MIN_ES4	53
#define	STEP1	39
#define	STEP2	50
#define	STEP3	46
#define	STEP4	96
#define	STEP5	103
#define	STEP6	22
#define	STEP7	100
#define	STEP8	28
#define	TACH_1	3
#define	TACH_2	12
#define	TACH_3	11
#define	TACH_4	10
#define	TC_nCS1	106
#define	TC_nCS2	108
#define	TC_nCS3	58
#define	TC_nCS4	61
#define	TC_nCS5	62
#define	THERM_AN1	64
#define	THERM_AN2	63
#define	THERM_AN3	65
#define SPIFLASH_CS 52


// TMC2130 Diag Pins (currently just for reference)
#define X_DIAG_PIN         DIAG1
#define Y_DIAG_PIN         DIAG2
#define Z_DIAG_PIN         DIAG3
#define E0_DIAG_PIN        DIAG4
#define E1_DIAG_PIN        DIAG5
#define E2_DIAG_PIN        DIAG6
#define E3_DIAG_PIN        DIAG7
#define E4_DIAG_PIN        DIAG8

// Limit Switches
//

// Only use Diag Pins when SENSORLESS_HOMING is enabled for the TMC2130 drivers.

// Otherwise use a physical endstop based configuration.

#if DISABLED(SENSORLESS_HOMING)
 #define X_MIN_PIN          MIN_ES1
 #define X_MAX_PIN          MAX_ES1
 #define Y_MIN_PIN          MIN_ES2
 #define Y_MAX_PIN          MIN_ES3
#else
  #if X_HOME_DIR == -1
    #define X_MIN_PIN      X_DIAG_PIN
    #define X_MAX_PIN      MAX_ES1
  #else
    #define X_MIN_PIN      MIN_ES1
    #define X_MAX_PIN      X_DIAG_PIN
  #endif

  #if Y_HOME_DIR == -1
    #define Y_MIN_PIN      Y_DIAG_PIN
    #define Y_MAX_PIN      MAX_ES2
  #else
    #define Y_MIN_PIN      MIN_ES2
    #define Y_MAX_PIN      Y_DIAG_PIN
  #endif
#endif

#define Z_MIN_PIN          MIN_ES3
#define Z_MAX_PIN          MAX_ES3
//#define Y2_MAX_PIN         MAX_ES4
//#define Z2_MIN_PIN         MIN_ES4

// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN  MAX_ES1
#endif

// Steppers
//
#define X_STEP_PIN         STEP1
#define X_DIR_PIN          DIR1
#define X_ENABLE_PIN       -1
#define X_CS_PIN           M_nCS1

#define Y_STEP_PIN         STEP2
#define Y_DIR_PIN          DIR2
#define Y_ENABLE_PIN       -1
#define Y_CS_PIN           M_nCS2

#define Y2_STEP_PIN         STEP3
#define Y2_DIR_PIN          DIR3
#define Y2_ENABLE_PIN       -1
#define Y2_CS_PIN           M_nCS3

#define Z_STEP_PIN          STEP4
#define Z_DIR_PIN           DIR4
#define Z_ENABLE_PIN        -1
#define Z_CS_PIN            M_nCS4

#define Z2_STEP_PIN         STEP5
#define Z2_DIR_PIN          DIR5
#define Z2_ENABLE_PIN       -1
#define Z2_CS_PIN           M_nCS5

#define E0_STEP_PIN         STEP6
#define E0_DIR_PIN          DIR6
#define E0_ENABLE_PIN       -1
#define E0_CS_PIN           M_nCS6

#define E1_STEP_PIN         STEP7
#define E1_DIR_PIN          DIR7
#define E1_ENABLE_PIN       -1
#define E1_CS_PIN           M_nCS7

#define E2_STEP_PIN         STEP8
#define E2_DIR_PIN          DIR8
#define E2_ENABLE_PIN       -1
#define E2_CS_PIN           M_nCS8


// Temperature Sensors
//
#define TEMP_0_PIN          THERM_AN1
#define TEMP_1_PIN          THERM_AN2
#define TEMP_2_PIN          -1
#define TEMP_BED_PIN        THERM_AN3
#define TEMP_3_PIN          -1

// Heaters / Fans
//
#ifndef FAN_PIN
  #define FAN_PIN           Fan1
#endif
#define FAN1_PIN            Fan2
#define FAN2_PIN            Fan3
#define FAN3_PIN            Fan4 

#define TACH_0_PIN         TACH_1
#define TACH_1_PIN         TACH_2
#define TACH_2_PIN         TACH_3
#define TACH_3_PIN         TACH_4

#define HEATER_0_PIN        Heat1
#define HEATER_1_PIN        Heat2
#define HEATER_2_PIN        Heat3
#define HEATER_BED_PIN      HeatBed
#define HEATER_3_PIN       -1

//

// Misc. Functions
//
#define SDSS               87

//////////////////////////

// LCDs and Controllers //
//////////////////////////
//#define ARCHIMAJOR_REV_01B
#if ENABLED(ULTRA_LCD)
  #if ENABLED(NEWPANEL)
    #ifdef ARCHIMAJOR_REV_01B //First version
        #define BEEPER_PIN      23
        #define LCD_PINS_RS     17
        #define LCD_PINS_ENABLE 24
        #define LCD_PINS_D4     69
        #define LCD_PINS_D6     68
        #define LCD_PINS_D7     34
        #define SD_DETECT_PIN    2
        #define BTN_EN1         60
        #define BTN_EN2         13
        #define BTN_ENC         16
    #else // Archimajor 0.2b
        #define BEEPER_PIN      20
        #define LCD_PINS_RS     21
        #define LCD_PINS_ENABLE 93
        #define LCD_PINS_D4     69
        #define LCD_PINS_D5     77
        #define LCD_PINS_D6     68
        #define LCD_PINS_D7     34
        #define SD_DETECT_PIN    2
        #define BTN_EN1         60
        #define BTN_EN2         13
        #define BTN_ENC        109
    #endif // Archimajor REV
  #endif
// NEWPANEL
#endif 
// ULTRA_LCD

// Enable TMC5160 outputs.
#define BOARD_INIT() do{ OUT_WRITE(DRV_EN, LOW); }while(0)
