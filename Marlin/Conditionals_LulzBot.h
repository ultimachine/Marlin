#ifndef CONDITIONALS_LULZBOT
#define CONDITIONALS_LULZBOT

/* We define the LULZBOT_ values based on which printer or toolhead variants we are compiling
 * for, these constants are then placed where appropriate in the following files:
 *
 *    - Configuration.h
 *    - Configuration_adv.h
 *    - pins.h
 *    - Default_Version.h
 *
 * Using our own set of constants and limiting modification to Marlin's files makes it easier to
 * merge from upstream. All values are prefixed with LULZBOT_ so that it is easy to see what
 * was changed and where. If a setting is commented out, we define a LULZBOT_{SETTING}_DISABLED
 * here, just so we have a record of things that got disabled.
 */

#if ( \
    !defined(LULZBOT_Gladiola_Mini) && \
    !defined(LULZBOT_Huerfano_Mini) && \
    !defined(LULZBOT_Gladiola_GLCD) && \
    !defined(LULZBOT_Huerfano_GLCD) && \
    !defined(LULZBOT_Oliveoil_TAZ_6) && \
    !defined(LULZBOT_Huerfano_TAZ_7) \
) || ( \
    !defined(TOOLHEAD_Gladiola_SingleExtruder) && \
    !defined(TOOLHEAD_Albatross_Flexystruder) && \
    !defined(TOOLHEAD_Heather_Aero) && \
    !defined(TOOLHEAD_Tilapia_SingleExtruder) && \
    !defined(TOOLHEAD_Kanyu_Flexystruder) && \
    !defined(TOOLHEAD_Opah_Moarstruder) && \
    !defined(TOOLHEAD_Javelin_DualExtruder) && \
    !defined(TOOLHEAD_Longfin_FlexyDually) && \
    !defined(TOOLHEAD_Yellowfin_DualExtruder) && \
    !defined(TOOLHEAD_Angelfish_Aero) \
)
    #error Must specify model and toolhead to build:
    #error
    #error   make clean
    #error   make MODEL=<model> TOOLHEAD=<toolhead>
    #error
    #error   Printer Model Choices:
    #error      Gladiola_Mini            // Lulzbot Mini  (Gladiola)
    #error      Huerfano_Mini            // Lulzbot Mini  (Huerfano)
    #error      Gladiola_GLCD            // Lulzbot Mini  (Gladiola w/ LCD)
    #error      Huerfano_GLCD            // Lulzbot Mini  (Huerfano w/ LCD)
    #error      Oliveoil_TAZ_6           // Lulzbot TAZ 6 (Olive Oil)
    #error      Huerfano_TAZ_7           // Lulzbot TAZ 7 (Huerfano)
    #error
    #error   Mini Toolhead Choices:
    #error      Gladiola_SingleExtruder  // Standard Single Extruder (Gladiola)
    #error      Albatross_Flexystruder   // Flexystruder (Albatross)
    #error      Heather_Aero             // Titan AERO (Heather)
    #error
    #error   TAZ Toolhead Choices:
    #error      Tilapia_SingleExtruder   // Standard Single Extruder (Tilapia)
    #error      Kanyu_Flexystruder       // Flexystruder (Kanyu)
    #error      Opah_Moarstruder         // Moarstruder (Opah)
    #error      Javelin_DualExtruder     // Dual Extruder v2 (Javelin)
    #error      Longfin_FlexyDually      // FlexyDually (Longfin)
    #error      Yellowfin_DualExtruder   // Dual Extruder v3 (Yellowfin)
    #error      Angelfish_Aero           // Titan AERO (Angelfish)
#endif

#define LULZBOT_FW_VERSION ".17"

// Select options based on printer model

#if defined(LULZBOT_Gladiola_Mini)
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
#endif

#if defined(LULZBOT_Huerfano_Mini)
    // Prototype Mini w/ Z-Belt
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini 2"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
#endif

#if defined(LULZBOT_Gladiola_GLCD)
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini GLCD"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
    #define LULZBOT_USE_LCD_DISPLAY
#endif

#if defined(LULZBOT_Huerfano_GLCD)
    // Prototype Mini w/ Z-Belt
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini 2 GLCD"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
    #define LULZBOT_USE_LCD_DISPLAY
#endif

#if defined(LULZBOT_Oliveoil_TAZ_6)
    #define LULZBOT_CUSTOM_MACHINE_NAME "TAZ 6"
    #define LULZBOT_IS_TAZ
    #define LULZBOT_TAZ_BED
    #define LULZBOT_USE_LCD_DISPLAY
#endif

#if defined(LULZBOT_Huerfano_TAZ_7)
    // Prototype TAZ w/ Z-Belt
    #define LULZBOT_CUSTOM_MACHINE_NAME "TAZ 7"
    #define LULZBOT_IS_TAZ
    #define LULZBOT_TAZ_BED
    #define LULZBOT_USE_LCD_DISPLAY
#endif

// Shared values
#define LULZBOT_STRING_CONFIG_H_AUTHOR        "(Aleph Objects Inc., LulzBot Diffusion)"
#define LULZBOT_BUFSIZE                       10
#define LULZBOT_EEPROM_SETTINGS
#define LULZBOT_EMERGENCY_PARSER

// Temperature settings

#define LULZBOT_TEMP_SENSOR_0                 5
#define LULZBOT_TEMP_SENSOR_BED               7
#define LULZBOT_TEMP_RESIDENCY_TIME           1
#define LULZBOT_TEMP_HYSTERESIS               10
#define LULZBOT_TEMP_WINDOW                   10

#define LULZBOT_TEMP_BED_RESIDENCY_TIME       1
#define LULZBOT_TEMP_BED_HYSTERESIS           5
#define LULZBOT_TEMP_BED_WINDOW               5

#define LULZBOT_HEATER_MAXTEMP                305
#define LULZBOT_EXTRUDE_MINTEMP               120

#define LULZBOT_PIDTEMPBED

#define LULZBOT_MAX_BED_POWER                 206

#define LULZBOT_THERMAL_PROTECTION_PERIOD     15     // Seconds
#define LULZBOT_THERMAL_PROTECTION_HYSTERESIS 30     // Degrees Celsius

#define LULZBOT_THERMAL_PROTECTION_BED_PERIOD     15     // Seconds
#define LULZBOT_THERMAL_PROTECTION_BED_HYSTERESIS 10     // Degrees Celsius

// Motherboard specifics and custom pins for probing.

#if defined(LULZBOT_IS_MINI)
    #define LULZBOT_MOTHERBOARD                   BOARD_MINIRAMBO
    #define LULZBOT_CONTROLLER_FAN_PIN            FAN1_PIN  // Digital pin 6
    #define LULZBOT_Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN
    #define LULZBOT_BAUDRATE 115200

#elif defined(LULZBOT_IS_TAZ)
    #define LULZBOT_MOTHERBOARD                   BOARD_RAMBO
    #define LULZBOT_CONTROLLER_FAN_PIN            FAN2_PIN  // Digital pin 2
    #define LULZBOT_Z_MIN_PROBE_ENDSTOP
    #define LULZBOT_Z_MIN_PROBE_PIN               SERVO0_PIN // Digital pin 22
    #define LULZBOT_BAUDRATE 250000
#endif

#define LULZBOT_USE_CONTROLLER_FAN
#define LULZBOT_USE_XMIN_PLUG
#define LULZBOT_USE_YMIN_PLUG
#define LULZBOT_USE_ZMIN_PLUG
#define LULZBOT_USE_XMAX_PLUG
#define LULZBOT_USE_YMAX_PLUG
#define LULZBOT_USE_ZMAX_PLUG

/* Endstop settings are determined by printer model, except for the
 * X_MAX which varies by toolhead. */

#if defined(LULZBOT_Gladiola_Mini) || defined(LULZBOT_Gladiola_GLCD)
    #define LULZBOT_X_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Y_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Y_MAX_ENDSTOP_INVERTING       true
    #define LULZBOT_Z_MAX_ENDSTOP_INVERTING       true

#elif defined(LULZBOT_IS_TAZ) || defined(LULZBOT_Huerfano_Mini) || defined(LULZBOT_Huerfano_GLCD)
    #define LULZBOT_X_MIN_ENDSTOP_INVERTING       false
    #define LULZBOT_Y_MIN_ENDSTOP_INVERTING       false
    #define LULZBOT_Y_MAX_ENDSTOP_INVERTING       false
    #define LULZBOT_Z_MAX_ENDSTOP_INVERTING       false
#endif

#define LULZBOT_Z_MIN_ENDSTOP_INVERTING           true
#define LULZBOT_Z_MIN_PROBE_ENDSTOP_INVERTING     true

#define LULZBOT_INVERT_X_DIR                      false
#define LULZBOT_INVERT_Y_DIR                      true
#define LULZBOT_INVERT_Z_DIR                      false
#define LULZBOT_INVERT_E0_DIR                     true
#define LULZBOT_INVERT_E1_DIR                     true

#if defined(LULZBOT_IS_MINI)
    #define LULZBOT_HOMING_Z_WITH_PROBE           false
    #define LULZBOT_INVERT_X_HOME_DIR             -1
    #define LULZBOT_INVERT_Y_HOME_DIR              1
    #define LULZBOT_INVERT_Z_HOME_DIR              1
    #define LULZBOT_QUICKHOME

#elif defined(LULZBOT_IS_TAZ)
    #define LULZBOT_HOMING_Z_WITH_PROBE           true
    #define LULZBOT_INVERT_X_HOME_DIR             -1
    #define LULZBOT_INVERT_Y_HOME_DIR              1
    #define LULZBOT_INVERT_Z_HOME_DIR             -1
    #define LULZBOT_QUICKHOME

    #define LULZBOT_AFTER_Z_HOME_Z_RAISE           5
    #define LULZBOT_AFTER_Z_HOME_Z_ORIGIN          0
#endif

#if defined(LULZBOT_MINI_BED)
    #define LULZBOT_LEFT_PROBE_BED_POSITION        0
    #define LULZBOT_RIGHT_PROBE_BED_POSITION     164
    #define LULZBOT_BACK_PROBE_BED_POSITION      162
    #define LULZBOT_FRONT_PROBE_BED_POSITION      -6

    #define LULZBOT_HOMING_FEEDRATE_XY            (30*60)
    #define LULZBOT_HOMING_FEEDRATE_Z             (12*60)

#elif defined(LULZBOT_TAZ_BED)
    #define LULZBOT_LEFT_PROBE_BED_POSITION       -9
    #define LULZBOT_RIGHT_PROBE_BED_POSITION     288
    #define LULZBOT_BACK_PROBE_BED_POSITION      289
    #define LULZBOT_FRONT_PROBE_BED_POSITION      -9

    #define LULZBOT_HOMING_FEEDRATE_XY            (50*60)
    #define LULZBOT_HOMING_FEEDRATE_Z             (8*60)

    // Only the TAZ models have a Z-homing button
    #define LULZBOT_Z_SAFE_HOMING
    #define LULZBOT_Z_SAFE_HOMING_X_POINT         (-19)
    #define LULZBOT_Z_SAFE_HOMING_Y_POINT         (258)
    #define LULZBOT_Z_HOMING_HEIGHT               5
#endif

#if defined(LULZBOT_MINI_BED)
    // Mini has a horizontal wiping pad on the back of the bed
    #define LULZBOT_WIPE_X1                       115
    #define LULZBOT_WIPE_X2                       45
    #define LULZBOT_WIPE_Y1                       173
    #define LULZBOT_WIPE_Y2                       173

#elif defined(LULZBOT_TAZ_BED)
    // TAZ has a vertical wiping pad on the left side of the bed
    #define LULZBOT_WIPE_X1                      -16
    #define LULZBOT_WIPE_X2                      -16
    #define LULZBOT_WIPE_Y1                       95
    #define LULZBOT_WIPE_Y2                       25
#endif

#define LULZBOT_NOZZLE_CLEAN_FEATURE

//#define LULZBOT_AUTO_BED_LEVELING_3POINT

#if defined(LULZBOT_AUTO_BED_LEVELING_3POINT)
  // Experimental three point leveling.
  #define LULZBOT_ABL_PROBE_PT_1_X LULZBOT_LEFT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_1_Y LULZBOT_FRONT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_2_X LULZBOT_RIGHT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_2_Y LULZBOT_FRONT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_3_X LULZBOT_RIGHT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_3_Y LULZBOT_BACK_PROBE_BED_POSITION
#else
  // Traditionally LulzBot printers have employed a four-point leveling
  // using a degenerate 2x2 grid. This is the traditional behavior.
  #define LULZBOT_GRID_MAX_POINTS_X            2
  #define LULZBOT_GRID_MAX_POINTS_Y            2
  #if defined(LULZBOT_IS_MINI)
    // We can't control the order of probe points exactly,
    // but on a Mini setting this makes the probe look better.
    #define LULZBOT_PROBE_Y_FIRST
  #endif
#endif

/* Define probe parameters related to bed leveling,
 * e.g. the washers on the bed. These are confusingly
 * named Z_MIN_PROBE in Marlin. The Z-Home switch
 * is called Z_MIN_ENDSTOP
 */
#define LULZBOT_FIX_MOUNTED_PROBE
#define LULZBOT_PROBE_DOUBLE_TOUCH
#define LULZBOT_X_PROBE_OFFSET_FROM_EXTRUDER  0
#define LULZBOT_Y_PROBE_OFFSET_FROM_EXTRUDER  0
#define LULZBOT_Z_PROBE_OFFSET_RANGE_MIN      -2
#define LULZBOT_Z_PROBE_OFFSET_RANGE_MAX      5
#define LULZBOT_XY_PROBE_SPEED                6000
#define LULZBOT_Z_PROBE_SPEED_SLOW           (1*60)
#define LULZBOT_Z_PROBE_SPEED_FAST           (8*60)
#define LULZBOT_Z_CLEARANCE_DEPLOY_PROBE      5
#define LULZBOT_Z_CLEARANCE_BETWEEN_PROBES    5

/* We use G92 for adjusting the coordinate space in the Yellowfin toolhead,
 * however upstream Marlin has made it so G92 adjusts the software endstops,
 * which makes G92 unusable for our use case. As an interim measure, revert
 * to the previous behavior of G29 using NO_WORKSPACE_OFFSETS
*/
#define LULZBOT_NO_WORKSPACE_OFFSETS

/* Enable the probe pins only only when homing/probing,
 * as this helps reduce EMI by grounding the lines.
 *
 * On Mini:
 *   Z_MIN_PIN are the bed washers.
 *
 * On TAZ:
 *   Z_MIN_PIN corresponds to the Z-Home push button.
 *   LULZBOT_Z_MIN_PROBE_PIN are the bed washers.
 */
#if defined(LULZBOT_MINI_BED)
    #define LULZBOT_ENABLE_PROBE_PINS(enable) { \
        if(enable) { \
          /* Set as inputs with pull-up resistor */ \
          SET_INPUT(Z_MIN_PIN); \
          WRITE(Z_MIN_PIN, HIGH); \
        } else { \
          /* Ground to prevent EMI */ \
          SET_OUTPUT(Z_MIN_PIN); \
          WRITE(Z_MIN_PIN, LOW); \
        } \
    }

#elif defined(LULZBOT_TAZ_BED)
    #define LULZBOT_ENABLE_PROBE_PINS(enable) { \
        if(enable) { \
          /* Set both as inputs with pull-up resistor */ \
          SET_INPUT(LULZBOT_Z_MIN_PROBE_PIN); \
          WRITE(LULZBOT_Z_MIN_PROBE_PIN, HIGH); \
          SET_INPUT(Z_MIN_PIN); \
          WRITE(Z_MIN_PIN, HIGH); \
        } else { \
          /* Ground both pins to prevent EMI */ \
          SET_OUTPUT(LULZBOT_Z_MIN_PROBE_PIN); \
          WRITE(LULZBOT_Z_MIN_PROBE_PIN, LOW); \
          SET_OUTPUT(Z_MIN_PIN); \
          WRITE(Z_MIN_PIN, LOW); \
        } \
    }
#endif

#define LULZBOT_FAN_KICKSTART_TIME          100
#define LULZBOT_FAN_MIN_PWM                  70
#define LULZBOT_HOST_KEEPALIVE_FEATURE_DISABLED

#if defined(LULZBOT_USE_LCD_DISPLAY)
    #define LULZBOT_REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
    #define LULZBOT_SDSUPPORT
    #define LULZBOT_XYZ_HOLLOW_FRAME_DISABLE
    #define LULZBOT_MENU_HOLLOW_FRAME_DISABLE
    #define LULZBOT_USE_SMALL_INFOFONT
    #define LULZBOT_BABYSTEPPING
    #define LULZBOT_BABYSTEP_ZPROBE_OFFSET
    #define LULZBOT_SHOW_CUSTOM_BOOTSCREEN
    #define LULZBOT_ENCODER_PULSES_PER_STEP 2
    #define LULZBOT_ENCODER_STEPS_PER_MENU_ITEM 1
    #define LULZBOT_COOLING_MESSAGES
    #define LULZBOT_MENU_BED_LEVELING_GCODE "G28 XY\nM109 S175\nG28 Z\nM109 R145\nG12\nG29\nM104 S0"
    #if defined(LULZBOT_Gladiola_GLCD) || defined(LULZBOT_Huerfano_GLCD)
        // In the experimental Gladiola_GLCD, the encoder direction is reversed.
        #define LULZBOT_REVERSE_ENCODER_DIRECTION
    #endif
    // Confusingly, Marlin shows three separate e-step settings: the active nozzle, nozzle1, nozzle2.
    // We hide the first since it is redundant.
    #define LULZBOT_HIDE_E_STEPS_FOR_ACTIVE_NOZZLE
#endif

/*********************************************** COMMON TOOLHEADS PARAMETERS *****************************/

#define LULZBOT_DEFAULT_EJERK                10.0
#if defined(LULZBOT_IS_TAZ)
    #define LULZBOT_E_STEPS                  830
#elif defined(LULZBOT_IS_MINI)
    #define LULZBOT_E_STEPS                  833
#endif

/*********************************************** MINI TOOLHEADS *******************************************/

#if defined(TOOLHEAD_Gladiola_SingleExtruder) || defined(TOOLHEAD_Albatross_Flexystruder) || defined(TOOLHEAD_Heather_Aero)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING
    #define LULZBOT_UUID                       "351487b6-ca9a-4c1a-8765-d668b1da6585"
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_X_MAX_POS                  175
    #define LULZBOT_X_MIN_POS                    0
    #define LULZBOT_Y_MAX_POS                  191
    #define LULZBOT_Y_MIN_POS                  -10
    #define LULZBOT_AO_Hexagon

    #define PWM_MOTOR_CURRENT_E               1250
#endif /* TOOLHEAD_Gladiola_SingleExtruder || TOOLHEAD_Albatross_Flexystruder || TOOLHEAD_Heather_Aero */

#if defined(TOOLHEAD_Gladiola_SingleExtruder)
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Single Extruder"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING        true
#endif /* TOOLHEAD_Gladiola_SingleExtruder */

#if defined(TOOLHEAD_Albatross_Flexystruder)
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Flexystruder"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING        true
#endif /* TOOLHEAD_Albatross_Flexystruder */

#if defined(TOOLHEAD_Heather_Aero)
    // Prototype Aero toolhead for Mini
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Titan AERO"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING        true
#endif /* TOOLHEAD_Heather_Aero */

/*********************************************** TAZ TOOLHEADS *******************************************/

#if defined(TOOLHEAD_Tilapia_SingleExtruder) || defined(TOOLHEAD_Angelfish_Aero)
    #define LULZBOT_TOOLHEAD_VER                    VERSION_STRING
    #define LULZBOT_UUID                            "845f003c-aebd-4e53-a6b9-7d0984fde609"
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_X_MAX_POS                  300
    #define LULZBOT_X_MIN_POS                  -20
    #define LULZBOT_Y_MAX_POS                  303
    #define LULZBOT_Y_MIN_POS                  -20
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Tilapia_SingleExtruder || TOOLHEAD_Angelfish_Aero */

#if defined(TOOLHEAD_Tilapia_SingleExtruder)
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Single Extruder"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot"
    #define DIGIPOT_MOTOR_CURRENT_E            135,135  // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    false
#endif /* TOOLHEAD_Tilapia_SingleExtruder */

#if defined(TOOLHEAD_Angelfish_Aero)
    // Prototype Aero for TAZ
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Titan AERO"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot AERO"
    #define DIGIPOT_MOTOR_CURRENT_E            160  // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    false
#endif /* TOOLHEAD_Angelfish_Aero */

#if defined(TOOLHEAD_Kanyu_Flexystruder)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING" Flexystruder"
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Flexystruder"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot Flexy"
    #define DIGIPOT_MOTOR_CURRENT_E            67  // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_UUID                       "564bab1c-704c-4225-b329-ac1a093d2638"
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
    #define LULZBOT_X_MAX_POS                  288
    #define LULZBOT_X_MIN_POS                  -27
    #define LULZBOT_Y_MAX_POS                  302
    #define LULZBOT_Y_MIN_POS                  -20
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Kanyu_Flexystruder */

#if defined(TOOLHEAD_Opah_Moarstruder)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING
    #define LULZBOT_LCD_TOOLHEAD_NAME              "MOARstruder"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot MOAR"
    #define LULZBOT_DEFAULT_ACCELERATION       250
    #define DIGIPOT_MOTOR_CURRENT_E            135  // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_UUID                       "d651819d-4a79-4b73-bc5b-ae1fe1aab36b"
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
    #define LULZBOT_X_MAX_POS                  290
    #define LULZBOT_X_MIN_POS                  -20
    #define LULZBOT_Y_MAX_POS                  303
    #define LULZBOT_Y_MIN_POS                  -20
    #define LULZBOT_Moarstruder
#endif /* TOOLHEAD_Opah_Moarstruder */

#if defined(TOOLHEAD_Javelin_DualExtruder) || defined(TOOLHEAD_Longfin_FlexyDually) || defined(TOOLHEAD_Yellowfin_DualExtruder)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING" Dual"
    #define LULZBOT_BUILD_VARIANT              " LulzBot Dual"
    #define LULZBOT_SWAP_FAN_PINS_6_AND_8      // For backwards compatibility
    #define DIGIPOT_MOTOR_CURRENT_E            160, 160  // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_EXTRUDERS                  2
    #define LULZBOT_UUID                       "c5077702-4ecd-4532-beaf-6acf94acc404"
    #define LULZBOT_X_MAX_POS                     288
    #define LULZBOT_X_MIN_POS                     -22
    #define LULZBOT_Y_MAX_POS                     303
    #define LULZBOT_Y_MIN_POS                     -20
    #define LULZBOT_TEMP_SENSOR_1                   5
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Javelin_DualExtruder || TOOLHEAD_Longfin_FlexyDually || TOOLHEAD_Yellowfin_DualExtruder */

#if defined(TOOLHEAD_Javelin_DualExtruder)
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Dual Extruder 2"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #undef  LULZBOT_WIPE_Y2
    #define LULZBOT_WIPE_Y2                    73
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
#endif /* TOOLHEAD_Javelin_DualExtruder */

#if defined(TOOLHEAD_Longfin_FlexyDually)
    #define LULZBOT_LCD_TOOLHEAD_NAME              "FlexyDually v2"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #undef  LULZBOT_WIPE_Y2
    #define LULZBOT_WIPE_Y2                    73
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
    #define LULZBOT_DISTINCT_E_FACTORS
#endif /* TOOLHEAD_Longfin_FlexyDually */


#if defined(TOOLHEAD_Yellowfin_DualExtruder)
    // Prototype Dual v3 for TAZ.
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Dual Extruder 3"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #undef  LULZBOT_AFTER_Z_HOME_Z_RAISE
    #define LULZBOT_AFTER_Z_HOME_Z_RAISE           16
    #undef  LULZBOT_AFTER_Z_HOME_Z_ORIGIN
    #define LULZBOT_AFTER_Z_HOME_Z_ORIGIN          5.5
    #undef  LULZBOT_WIPE_X1
    #undef  LULZBOT_WIPE_X2
    #define LULZBOT_WIPE_X1                       -22
    #define LULZBOT_WIPE_X2                       -22
    #undef  LULZBOT_Z_HOMING_HEIGHT
    #define LULZBOT_Z_HOMING_HEIGHT                10
    #undef  LULZBOT_Z_CLEARANCE_DEPLOY_PROBE
    #define LULZBOT_Z_CLEARANCE_DEPLOY_PROBE       10
    #undef  LULZBOT_Z_CLEARANCE_BETWEEN_PROBES
    #define LULZBOT_Z_CLEARANCE_BETWEEN_PROBES     10
    #undef  LULZBOT_BACK_PROBE_BED_POSITION
    #define LULZBOT_BACK_PROBE_BED_POSITION       293
    #undef  LULZBOT_Z_SAFE_HOMING_X_POINT
    #undef  LULZBOT_Z_SAFE_HOMING_Y_POINT
    #define LULZBOT_Z_SAFE_HOMING_X_POINT        (-22)    // X point for Z homing when homing all axis (G28)
    #define LULZBOT_Z_SAFE_HOMING_Y_POINT        (265)    // Y point for Z homing when homing all axis (G28)
    #undef  LULZBOT_X_MAX_POS
    #define LULZBOT_X_MAX_POS                      290
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING       false
    #undef  LULZBOT_INVERT_E0_DIR
    #define LULZBOT_INVERT_E0_DIR                 false
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Yellowfin_DualExtruder */

/* HOTEND Variants */

#if defined(LULZBOT_Moarstruder)
    // LulzBot MOARstruder (40v)
    #define LULZBOT_DEFAULT_Kp 55.64
    #define LULZBOT_DEFAULT_Ki 6.79
    #define LULZBOT_DEFAULT_Kd 113.94
#endif /* LULZBOT_Moarstruder */

#if defined(LULZBOT_AO_Hexagon)
    // LulzBot AO-Hexagon (24v)
    #define LULZBOT_DEFAULT_Kp 28.79
    #define LULZBOT_DEFAULT_Ki 1.91
    #define LULZBOT_DEFAULT_Kd 108.51
#endif /* LULZBOT_AO_Hexagon */

// Heated bed parameters

//24V 360W silicone heater from NPH on 3mm borosilicate (TAZ 2.2+)
#if defined(LULZBOT_TAZ_BED)
  #define LULZBOT_DEFAULT_bedKp                 162
  #define LULZBOT_DEFAULT_bedKi                 17
  #define LULZBOT_DEFAULT_bedKd                 378

#elif defined(LULZBOT_MINI_BED)
  #define LULZBOT_DEFAULT_bedKp                 294
  #define LULZBOT_DEFAULT_bedKi                 65
  #define LULZBOT_DEFAULT_bedKd                 382
#endif

// Nozzle wiping points (varies by toolhead, as the nozzle position varies)

#define LULZBOT_NOZZLE_CLEAN_START_POINT      {LULZBOT_WIPE_X1, LULZBOT_WIPE_Y1, 1}
#define LULZBOT_NOZZLE_CLEAN_END_POINT        {LULZBOT_WIPE_X2, LULZBOT_WIPE_Y2, 1}

// Acceleration, feedrate, motor steps and motor currents for XYZ vary
// by printer model (steps and motor currents for E vary by toolhead).
// Z values additionally vary depending on whether the Z assembly is
// rod or belt driven.

#if defined(LULZBOT_IS_MINI)
    #define PWM_MOTOR_CURRENT_XY                  1300
    #define LULZBOT_XY_STEPS                      100.5
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {800, 800, 8, 40}      // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,100,10000}

    #define LULZBOT_DEFAULT_XJERK                 12.0
    #define LULZBOT_DEFAULT_YJERK                 12.0
    #define LULZBOT_DEFAULT_ZJERK                  0.4

    #define LULZBOT_DEFAULT_ACCELERATION          2000
    #define LULZBOT_DEFAULT_TRAVEL_ACCELERATION   3000

    #define LULZBOT_Z_MAX_POS                      160
    #define LULZBOT_Z_MIN_POS                      0

    #define LULZBOT_Z_PROBE_OFFSET_FROM_EXTRUDER  -1.43

#elif defined(LULZBOT_IS_TAZ)
    #define DIGIPOT_MOTOR_CURRENT_XY              175
    #define LULZBOT_XY_STEPS                      100.5
    #define LULZBOT_DEFAULT_XJERK                 8.0
    #define LULZBOT_DEFAULT_YJERK                 8.0
    #define LULZBOT_DEFAULT_ZJERK                 0.4
    #if not defined(LULZBOT_DEFAULT_ACCELERATION)
        #define LULZBOT_DEFAULT_ACCELERATION      500
    #endif
    #define LULZBOT_DEFAULT_TRAVEL_ACCELERATION   3000
    #define LULZBOT_Z_MIN_POS                     0

    #define LULZBOT_Z_PROBE_OFFSET_FROM_EXTRUDER -1.5
#endif

#if defined(LULZBOT_Gladiola_Mini) || defined(LULZBOT_Gladiola_GLCD)
    #define PWM_MOTOR_CURRENT_Z                   1630
    #define LULZBOT_Z_STEPS                       1600

#elif defined(LULZBOT_Huerfano_Mini) || defined(LULZBOT_Huerfano_GLCD)
    #define PWM_MOTOR_CURRENT_Z                   1000
    // Prototype Z-Belt Mini
    #define Z_FULL_STEPS_PER_ROTATION             200
    #define Z_MICROSTEPS                          16
    #define Z_BELT_PITCH                          2
    #define Z_PULLEY_TEETH                        24
    #define Z_MOTOR_GEAR_REDUCTION                26.8512396694
    #define LULZBOT_Z_STEPS (Z_FULL_STEPS_PER_ROTATION * Z_MICROSTEPS * Z_MOTOR_GEAR_REDUCTION / double(Z_BELT_PITCH) / double(Z_PULLEY_TEETH))
    #undef  LULZBOT_Z_MAX_POS
    #define LULZBOT_Z_MAX_POS                     186.1

#elif defined(LULZBOT_Oliveoil_TAZ_6)
    #define DIGIPOT_MOTOR_CURRENT_Z               200
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {800, 800, 3, 40}      // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,100,10000}
    #define LULZBOT_Z_STEPS                       1600
    #define LULZBOT_Z_MAX_POS                     270

#elif defined(LULZBOT_Huerfano_TAZ_7)
    #define DIGIPOT_MOTOR_CURRENT_Z               175
    // Prototype Z-belt driven TAZ 7
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {800, 800, 600, 40}   // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,10,10000}
    #define LULZBOT_Z_STEPS                       1790.08264463
    #define LULZBOT_Z_MAX_POS                     290
#endif

#if defined(PWM_MOTOR_CURRENT_XY) && defined(PWM_MOTOR_CURRENT_Z) && defined(PWM_MOTOR_CURRENT_E)
    #define LULZBOT_PWM_MOTOR_CURRENT { \
        PWM_MOTOR_CURRENT_XY, \
        PWM_MOTOR_CURRENT_Z, \
        PWM_MOTOR_CURRENT_E \
    } // Values in milliamps

#elif defined(DIGIPOT_MOTOR_CURRENT_XY) && defined(DIGIPOT_MOTOR_CURRENT_Z) && defined(DIGIPOT_MOTOR_CURRENT_E)
    #define LULZBOT_DIGIPOT_MOTOR_CURRENT { \
        DIGIPOT_MOTOR_CURRENT_XY, \
        DIGIPOT_MOTOR_CURRENT_XY, \
        DIGIPOT_MOTOR_CURRENT_Z, \
        DIGIPOT_MOTOR_CURRENT_E \
    } // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)

#else
    #error Motor currents not defined
#endif

// default steps per unit for LulzBot TAZ.

#if defined(LULZBOT_DISTINCT_E_FACTORS) && LULZBOT_EXTRUDERS == 2
    #define LULZBOT_DEFAULT_AXIS_STEPS_PER_UNIT   {LULZBOT_XY_STEPS,LULZBOT_XY_STEPS,LULZBOT_Z_STEPS,LULZBOT_E_STEPS,LULZBOT_E_STEPS}
#else
    #define LULZBOT_DEFAULT_AXIS_STEPS_PER_UNIT   {LULZBOT_XY_STEPS,LULZBOT_XY_STEPS,LULZBOT_Z_STEPS,LULZBOT_E_STEPS}
#endif

// Gralco's customized Z Offset overlay (also requires dogm_bitmaps_Lulzbot.h)

#define LULZBOT_ZOFFSET_OVERLAY(zprobe_zoffset) \
    static int dir = 0; \
    static float old_zprobe_zoffset = 0; \
    if(zprobe_zoffset != old_zprobe_zoffset) { \
        dir = (zprobe_zoffset > old_zprobe_zoffset) ? 1 : -1; \
        old_zprobe_zoffset = zprobe_zoffset; \
    } \
    const int left   = 5; \
    const int right  = 90; \
    const int nozzle = 60; \
    u8g.drawBitmapP(nozzle + 6, 4 - dir,2,12,nozzle_bmp); \
    u8g.drawBitmapP(nozzle + 0,20,3,1,offset_bedline_bmp); \
    u8g.drawBitmapP(left  + 0, 47, 3, 16, ccw_bmp); \
    u8g.drawBitmapP(right + 0, 47, 3, 16, cw_bmp); \
    u8g.drawBitmapP(right + 20, 48 - dir, 2, 13, up_arrow_bmp); \
    u8g.drawBitmapP(left  + 20, 49 - dir, 2, 13, down_arrow_bmp);

// Customized splash screen
#define LULZBOT_CUSTOM_BOOTSCREEN() \
    u8g.firstPage(); \
    do { \
        u8g.drawBitmapP(0,0,CEILING(CUSTOM_BOOTSCREEN_BMPWIDTH, 8),CUSTOM_BOOTSCREEN_BMPHEIGHT,custom_start_bmp); \
        u8g.setFont(u8g_font_6x13); \
        u8g.drawStr(61,17,LULZBOT_CUSTOM_MACHINE_NAME); \
        u8g.setFont(u8g_font_04b_03); \
        u8g.drawStr(62,28,LULZBOT_LCD_TOOLHEAD_NAME); \
        u8g.setFont(u8g_font_5x8); \
        u8g.drawStr(63,41,"LulzBot.com"); \
        u8g.setFont(u8g_font_5x8); \
        u8g.drawStr(62,62,"v"); \
        u8g.drawStr(67,62,SHORT_BUILD_VERSION LULZBOT_FW_VERSION); \
    } while( u8g.nextPage() );

// Customize version string

#define LULZBOT_DETAILED_BUILD_VERSION SHORT_BUILD_VERSION LULZBOT_FW_VERSION " (LulzBot " LULZBOT_CUSTOM_MACHINE_NAME " " LULZBOT_LCD_TOOLHEAD_NAME ")"
#define LULZBOT_STRING_DISTRIBUTION_DATE __DATE__ __TIME__
#define LULZBOT_SOURCE_CODE_URL "https://code.alephobjects.com/diffusion/MARLIN"

// Bed Probe w/ Rewipe
#define LULZBOT_NUM_REWIPES      1
#define LULZBOT_BED_PROBE_MIN   -3 // Limit on pushing into the bed
#define LULZBOT_BED_PROBE_FAIL  -2 // At what point is a failure detected

#if defined(LULZBOT_USE_LCD_DISPLAY)
    #define LULZBOT_STOP_JOB_CMD card.stopSDPrint();
#else
    #define LULZBOT_STOP_JOB_CMD
#endif

#define LULZBOT_PROBE_Z_WITH_REWIPE(speed) \
    do_probe_move(LULZBOT_BED_PROBE_MIN, speed); /* probe; if we reach limit, the probe failed */ \
    for(int rewipes = 1; current_position[Z_AXIS] < LULZBOT_BED_PROBE_FAIL; rewipes++) { \
        SERIAL_ERRORLNPGM(MSG_REWIPE); \
        LCD_MESSAGEPGM(MSG_REWIPE); \
        do_blocking_move_to_z(10, MMM_TO_MMS(speed)); /* raise nozzle */ \
        Nozzle::clean(0, 2, 0, 0);                    /* wipe nozzle */ \
        do_probe_move(LULZBOT_BED_PROBE_MIN, speed);  /* reprobe */ \
        if(rewipes >= LULZBOT_NUM_REWIPES) {          /* max of tries */ \
            SERIAL_ERRORLNPGM("PROBE FAIL CLEAN NOZZLE"); /* cura listens for this message specifically */ \
            LCD_MESSAGEPGM(MSG_LEVEL_FAIL);           /* use a more friendly message on the LCD */ \
            BUZZ(25, 880); BUZZ(50, 0);               /* play tone */ \
            BUZZ(25, 880); BUZZ(50, 0); \
            BUZZ(25, 880); BUZZ(50, 0); \
            do_blocking_move_to_z(100, MMM_TO_MMS(Z_PROBE_SPEED_FAST)); /* raise head */ \
            LULZBOT_STOP_JOB_CMD;                     /* stop print job */ \
            clear_command_queue(); \
            print_job_timer.stop(); \
            return NAN;                               /* abort the leveling in progress */ \
        } \
    }

#define LULZBOT_G92_Z(z) \
      stepper.synchronize(); \
      current_position[Z_AXIS] = z; \
      SYNC_PLAN_POSITION_KINEMATIC();

#define LULZBOT_G0_Z(z) \
      do_blocking_move_to_z(z);

// On a TAZ, we need to raise the print head after homing to clear the button;
// On the yellowfin we also need to reset the origin to account for the Z home riser.

#if defined(LULZBOT_IS_TAZ)
    #define LULZBOT_AFTER_Z_HOME_ACTION \
        if(home_all || homeZ) { \
          LULZBOT_G92_Z(LULZBOT_AFTER_Z_HOME_Z_ORIGIN); \
          LULZBOT_G0_Z(LULZBOT_AFTER_Z_HOME_Z_RAISE); \
        }
#else
    #define LULZBOT_AFTER_Z_HOME_ACTION
#endif

#endif /* CONDITIONALS_LULZBOT */
