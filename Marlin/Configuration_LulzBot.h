#ifndef CONFIGURATION_LULZBOT
#define CONFIGURATION_LULZBOT

// Change printer model and toolhead here

#define LULZBOT_Oliveoil_TAZ_6
#define TOOLHEAD_Angelfish_Aero

/* We define the LULZBOT_ values based on which print head or printer variants we are compiling for,
 * these constants are then placed where appropriate in the following files:
 *
 *    - Configuration.h
 *    - Configuration_adv.h
 *    - pins.h
 *    - Default_Version.h
 *
 * Using our own set of constants make it easier to keep track of changes from upstream.
 * All values are prefixed with LULZBOT_ so that it is easy to see what was changed and where.
 * If a setting is commented out, we define a LULZBOT_{SETTING}_DISABLED here, just so
 * we have a record of things that got disabled.
 */

#if ( \
    !defined(LULZBOT_Gladiola_Mini) && \
    !defined(LULZBOT_Huerfano_Mini) && \
    !defined(LULZBOT_Oliveoil_TAZ_6) && \
    !defined(LULZBOT_Huerfano_TAZ_7) \
) || ( \
    !defined(TOOLHEAD_Gladiola_SingleExtruder) && \
    !defined(TOOLHEAD_Oliveoil_SingleExtruder) && \
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
#error   Model Choices:
#error      Gladiola_Mini    // Lulzbot Mini  (Gladiola)
#error      Huerfano_Mini    // Lulzbot Mini  (Huerfano)
#error      Oliveoil_TAZ_6   // Lulzbot TAZ 6 (Olive Oil)
#error      Huerfano_TAZ_7   // Lulzbot TAZ 7 (Huerfano)
#error
#error   Toolhead Choices:
#error      Gladiola_SingleExtruder  // Standard Single Extruder (Gladiola)
#error      Oliveoil_SingleExtruder  // Standard Single Extruder (TAZ Olive)
#error      Kanyu_Flexystruder       // Flexystruder (Kanyu)
#error      Opah_Moarstruder         // Moarstruder (Opah)
#error      Javelin_DualExtruder     // Dual Extruder v2 (Javelin)
#error      Longfin_FlexyDually      // FlexyDually (Longfin)
#error      Yellowfin_DualExtruder   // Dual Extruder v3 (Yellowfin)
#error      Angelfish_Aero           // Titan AERO (Angelfish)
#endif

#define LULZBOT_FW_VERSION ".1"

// Select options based on printer model

#if defined(LULZBOT_Gladiola_Mini)
#define LULZBOT_CUSTOM_MACHINE_NAME "Mini"
    #define LULZBOT_MINI_BED
#endif

#if defined(LULZBOT_Huerfano_Mini)
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini Too"
    #define LULZBOT_MINI_Z_BELT
    #define LULZBOT_MINI_BED
#endif

#if defined(LULZBOT_Oliveoil_TAZ_6)
    #define LULZBOT_CUSTOM_MACHINE_NAME "TAZ 6"
    #define LULZBOT_TAZ_BED
#endif

#if defined(LULZBOT_Huerfano_TAZ_7)
    #define LULZBOT_CUSTOM_MACHINE_NAME "TAZ 7"
    #define LULZBOT_TAZ_Z_BELT
    #define LULZBOT_TAZ_BED
#endif

// Shared values
#define LULZBOT_STRING_CONFIG_H_AUTHOR        "(Aleph Objects Inc., LulzBot Default)"
#define LULZBOT_BUFSIZE                       10

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

#if defined(LULZBOT_Gladiola_Mini) || defined(LULZBOT_Huerfano_Mini)
    #define LULZBOT_MOTHERBOARD                   BOARD_MINIRAMBO
    #define LULZBOT_CONTROLLER_FAN_PIN            FAN_1_PIN  // Digital pin 6
    #define LULZBOT_Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN

#elif defined(LULZBOT_Oliveoil_TAZ_6) || defined(LULZBOT_Huerfano_TAZ_7)
    #define LULZBOT_MOTHERBOARD                   BOARD_RAMBO
    #define LULZBOT_CONTROLLER_FAN_PIN            FAN_2_PIN  // Digital pin 2
    #define LULZBOT_Z_MIN_PROBE_ENDSTOP
    #define LULZBOT_Z_MIN_PROBE_PIN               SERVO0_PIN // Digital pin 22
#endif

#define LULZBOT_USE_XMIN_PLUG
#define LULZBOT_USE_YMIN_PLUG
#define LULZBOT_USE_ZMIN_PLUG
#define LULZBOT_USE_XMAX_PLUG
#define LULZBOT_USE_YMAX_PLUG
#define LULZBOT_USE_ZMAX_PLUG

#if defined(LULZBOT_Gladiola_Mini) || defined(LULZBOT_Huerfano_Mini)
    #define LULZBOT_X_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Y_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Z_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Z_MIN_PROBE_ENDSTOP_INVERTING true
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING       true
    #define LULZBOT_Y_MAX_ENDSTOP_INVERTING       true
    #define LULZBOT_Z_MAX_ENDSTOP_INVERTING       true

#elif defined(LULZBOT_Oliveoil_TAZ_6) || defined(LULZBOT_Huerfano_TAZ_7)
    #define LULZBOT_X_MIN_ENDSTOP_INVERTING       false
    #define LULZBOT_Y_MIN_ENDSTOP_INVERTING       false
    #define LULZBOT_Z_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Z_MIN_PROBE_ENDSTOP_INVERTING true
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING       false
    #define LULZBOT_Y_MAX_ENDSTOP_INVERTING       false
    #define LULZBOT_Z_MAX_ENDSTOP_INVERTING       false
#endif

#define LULZBOT_INVERT_X_DIR                  false
#define LULZBOT_INVERT_Y_DIR                  true
#define LULZBOT_INVERT_Z_DIR                  false
#define LULZBOT_INVERT_E0_DIR                 true
#define LULZBOT_INVERT_E1_DIR                 true

#if defined(LULZBOT_Gladiola_Mini) || defined(LULZBOT_Huerfano_Mini)
    #define LULZBOT_HOMING_Z_WITH_PROBE           false
    #define LULZBOT_INVERT_X_HOME_DIR             -1
    #define LULZBOT_INVERT_Y_HOME_DIR              1
    #define LULZBOT_INVERT_Z_HOME_DIR              1
    #define LULZBOT_QUICKHOME

#elif defined(LULZBOT_Oliveoil_TAZ_6) || defined(LULZBOT_Huerfano_TAZ_7)
    #define LULZBOT_HOMING_Z_WITH_PROBE           true
    #define LULZBOT_INVERT_X_HOME_DIR             -1
    #define LULZBOT_INVERT_Y_HOME_DIR              1
    #define LULZBOT_INVERT_Z_HOME_DIR             -1
    #define LULZBOT_QUICKHOME
#endif

#if defined(LULZBOT_MINI_BED)
    #define LULZBOT_LEFT_PROBE_BED_POSITION        0
    #define LULZBOT_RIGHT_PROBE_BED_POSITION     164
    #define LULZBOT_FRONT_PROBE_BED_POSITION      -6
    #define LULZBOT_BACK_PROBE_BED_POSITION      162

    #define LULZBOT_HOMING_FEEDRATE_XY            (30*60)
    #define LULZBOT_HOMING_FEEDRATE_Z             (12*60)

#elif defined(LULZBOT_TAZ_BED)
    #define LULZBOT_LEFT_PROBE_BED_POSITION       -9
    #define LULZBOT_RIGHT_PROBE_BED_POSITION     288
    #define LULZBOT_BACK_PROBE_BED_POSITION      289
    #define LULZBOT_FRONT_PROBE_BED_POSITION      -9

    #define LULZBOT_HOMING_FEEDRATE_XY            (50*60)
    #define LULZBOT_HOMING_FEEDRATE_Z             (8*60)

    #define LULZBOT_Z_SAFE_HOMING
    #define LULZBOT_Z_SAFE_HOMING_X_POINT         (-19)
    #define LULZBOT_Z_SAFE_HOMING_Y_POINT         (258)
    #define LULZBOT_Z_HOMING_HEIGHT               5
    #define LULZBOT_RAISE_AFTER_HOME // Not in upstream Marlin.
#endif

#elif defined(LULZBOT_MINI_BED)
    #define LULZBOT_WIPE_X1                       115
    #define LULZBOT_WIPE_X2                       45
    #define LULZBOT_WIPE_Y1                       173
    #define LULZBOT_WIPE_Y2                       173

#else defined(LULZBOT_TAZ_BED)
    #define LULZBOT_WIPE_X1                      -16
    #define LULZBOT_WIPE_X2                      -16
    #define LULZBOT_WIPE_Y1                       95
    #define LULZBOT_WIPE_Y2                       25
#endif

#define LULZBOT_NOZZLE_CLEAN_FEATURE

#define LULZBOT_AUTO_BED_LEVELING_3POINT
#define LULZBOT_ABL_PROBE_PT_1_X LULZBOT_LEFT_PROBE_BED_POSITION
#define LULZBOT_ABL_PROBE_PT_1_Y LULZBOT_FRONT_PROBE_BED_POSITION
#define LULZBOT_ABL_PROBE_PT_2_X LULZBOT_RIGHT_PROBE_BED_POSITION
#define LULZBOT_ABL_PROBE_PT_2_Y LULZBOT_FRONT_PROBE_BED_POSITION
#define LULZBOT_ABL_PROBE_PT_3_X LULZBOT_RIGHT_PROBE_BED_POSITION
#define LULZBOT_ABL_PROBE_PT_3_Y LULZBOT_BACK_PROBE_BED_POSITION

/* Define probe parameters related to bed leveling,
 * e.g. the washers on the bed. These are confusingly
 * named Z_MIN_PROBE in Marlin. The Z-Home switch
 * is called Z_MIN_ENDSTOP
 */
#define LULZBOT_FIX_MOUNTED_PROBE
#define LULZBOT_PROBE_DOUBLE_TOUCH
#define LULZBOT_X_PROBE_OFFSET_FROM_EXTRUDER  0
#define LULZBOT_Y_PROBE_OFFSET_FROM_EXTRUDER  0
#define LULZBOT_Z_PROBE_OFFSET_FROM_EXTRUDER  -1.5
#define LULZBOT_Z_PROBE_OFFSET_RANGE_MIN      -2
#define LULZBOT_Z_PROBE_OFFSET_RANGE_MAX      5
#define LULZBOT_XY_PROBE_SPEED                6000
#define LULZBOT_Z_PROBE_SPEED_SLOW           (1*60)
#define LULZBOT_Z_PROBE_SPEED_FAST           (8*60)
#define LULZBOT_Z_CLEARANCE_DEPLOY_PROBE      5
#define LULZBOT_Z_CLEARANCE_BETWEEN_PROBES    5

/* Enable the probe pins only only when homing/probing.
 *   Z_MIN_PIN corresponds to the Z-Home push button.
 *   LULZBOT_Z_MIN_PROBE_PIN are the bed washers.
 */
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

#define LULZBOT_FAN_KICKSTART_TIME          100
#define LULZBOT_FAN_MIN_PWM                  70

#define LULZBOT_REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
#define LULZBOT_SDSUPPORT
#define LULZBOT_XYZ_HOLLOW_FRAME_DISABLE
#define LULZBOT_MENU_HOLLOW_FRAME_DISABLE
#define LULZBOT_USE_SMALL_INFOFONT
#define LULZBOT_BABYSTEPPING
#define LULZBOT_BABYSTEP_ZPROBE_OFFSET
#define LULZBOT_SHOW_CUSTOM_BOOTSCREEN
#define LULZBOT_HOST_KEEPALIVE_FEATURE_DISABLED
#define LULZBOT_MENU_BED_LEVELING_GCODE       "G28 XY\nM109 S175\nG28 Z\nM109 R145\nG12\nG29\nM104 S0"

#if defined(TOOLHEAD_Gladiola_SingleExtruder)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING
    #define LULZBOT_UUID                       "351487b6-ca9a-4c1a-8765-d668b1da6585"
    #define LULZBOT_PWM_MOTOR_CURRENT          {1300, 1630, 1250} // Values in milliamps
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    false
    #define LULZBOT_X_MAX_POS                  175
    #define LULZBOT_X_MIN_POS                    0
    #define LULZBOT_Y_MAX_POS                  191
    #define LULZBOT_Y_MIN_POS                  -10
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Gladiola_SingleExtruder */

#if defined(TOOLHEAD_Oliveoil_SingleExtruder) || defined(TOOLHEAD_Angelfish_Aero)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING
    #define LULZBOT_UUID                       "845f003c-aebd-4e53-a6b9-7d0984fde609"
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    false
    #define LULZBOT_X_MAX_POS                  300
    #define LULZBOT_X_MIN_POS                  -20
    #define LULZBOT_Y_MAX_POS                  303
    #define LULZBOT_Y_MIN_POS                  -20
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Oliveoil_SingleExtruder || TOOLHEAD_Angelfish_Aero */

#if defined(TOOLHEAD_Oliveoil_SingleExtruder)
    #define LULZBOT_TOOLHEAD_NAME              "Single Extruder"
//          16 chars max                        ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot"
    #define LULZBOT_DIGIPOT_MOTOR_CURRENT      {175,175,200,135,135} // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
#endif /* TOOLHEAD_Oliveoil_SingleExtruder */

#if defined(TOOLHEAD_Angelfish_Aero)
    #define LULZBOT_TOOLHEAD_NAME              "Titan AERO"
//          16 chars max                        ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot AERO"
    #define LULZBOT_DIGIPOT_MOTOR_CURRENT      {175,175,200,160,160} // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
#endif /* TOOLHEAD_Angelfish_Aero */

#if defined(TOOLHEAD_Kanyu_Flexystruder)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING" Flexystruder"
    #define LULZBOT_TOOLHEAD_NAME              "Flexystruder"
//          16 chars max                        ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot Flexy"
    #define LULZBOT_DIGIPOT_MOTOR_CURRENT      {175,175,200,67,135}
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_UUID                       "564bab1c-704c-4225-b329-ac1a093d2638"
    #undef  LULZBOT_X_MAX_ENDSTOP_INVERTING
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
    #define LULZBOT_X_MAX_POS                  288
    #define LULZBOT_X_MIN_POS                  -27
    #define LULZBOT_Y_MAX_POS                  302
    #define LULZBOT_Y_MIN_POS                  -20
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Kanyu_Flexystruder */

#if defined(TOOLHEAD_Opah_Moarstruder)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING
    #define LULZBOT_TOOLHEAD_NAME              "MOARstruder"
//          16 chars max                        ^^^^^^^^^^^^^^^
    #define LULZBOT_BUILD_VARIANT              " LulzBot MOAR"
    #undef  LULZBOT_DEFAULT_ACCELERATION
    #define LULZBOT_DEFAULT_ACCELERATION       250
    #define LULZBOT_DIGIPOT_MOTOR_CURRENT      {175,175,200,135,135} // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_UUID                       "d651819d-4a79-4b73-bc5b-ae1fe1aab36b"
    #undef  LULZBOT_X_MAX_ENDSTOP_INVERTING
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
    #define LULZBOT_SWAP_FAN_PINS_6_AND_8
    #define LULZBOT_DIGIPOT_MOTOR_CURRENT      {175,175,200,160,160} // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_EXTRUDERS                  2
    #define LULZBOT_UUID                       "c5077702-4ecd-4532-beaf-6acf94acc404"
    #undef  LULZBOT_X_MAX_ENDSTOP_INVERTING
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
    #define LULZBOT_X_MAX_POS                     288
    #define LULZBOT_X_MIN_POS                     -22
    #define LULZBOT_Y_MAX_POS                     303
    #define LULZBOT_Y_MIN_POS                     -20
    #define LULZBOT_TEMP_SENSOR_1                   5
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Javelin_DualExtruder || TOOLHEAD_Longfin_FlexyDually || TOOLHEAD_Yellowfin_DualExtruder */

#if defined(TOOLHEAD_Javelin_DualExtruder)
    #define LULZBOT_TOOLHEAD_NAME              "Dual Extruder 2"
//          16 chars max                        ^^^^^^^^^^^^^^^
    #undef  LULZBOT_WIPE_Y2
    #define LULZBOT_WIPE_Y2                    73
#endif /* TOOLHEAD_Javelin_DualExtruder */

#if defined(TOOLHEAD_Longfin_FlexyDually)
    #define LULZBOT_TOOLHEAD_NAME              "FlexyDually v2"
//          16 chars max                        ^^^^^^^^^^^^^^^
    #undef  LULZBOT_WIPE_Y2
    #define LULZBOT_WIPE_Y2                    73
#endif /* TOOLHEAD_Longfin_FlexyDually */


#if defined(TOOLHEAD_Yellowfin_DualExtruder)
    #define LULZBOT_TOOLHEAD_NAME              "Dual Extruder 3"
//          16 chars max                        ^^^^^^^^^^^^^^^
    #define LULZBOT_AFTER_Z_PROBE_CMD               "G92 Z15.5" // Correction for raised homing button
    #undef  LULZBOT_WIPE_X1
    #undef  LULZBOT_WIPE_X2
    #define LULZBOT_WIPE_X1                       -22
    #define LULZBOT_WIPE_X2                       -22
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING     false   // Yellowfin toolhead has a normally closed endstop
    #undef  LULZBOT_Z_HOMING_HEIGHT
    #define LULZBOT_Z_HOMING_HEIGHT                10
    #undef  LULZBOT_Z_SAFE_HOMING_X_POINT
    #undef  LULZBOT_Z_SAFE_HOMING_Y_POINT
    #define LULZBOT_Z_SAFE_HOMING_X_POINT        (-22)    // X point for Z homing when homing all axis (G28)
    #define LULZBOT_Z_SAFE_HOMING_Y_POINT        (260)    // Y point for Z homing when homing all axis (G28)
    #undef  LULZBOT_X_MAX_POS
    #define LULZBOT_X_MAX_POS                      290
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

// Acceleration, feedrate and E-Steps

#ifdef defined(LULZBOT_Huerfano_TAZ_7)
    // Z-belt driven TAZ 7
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {800, 800, 600, 40}   // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,10,10000}
    #define LULZBOT_XY_STEPS                      100.5
    #define LULZBOT_Z_STEPS                       1790.08264463
    #define LULZBOT_E_STEPS                       760
    #define LULZBOT_DEFAULT_ACCELERATION          500
    #define LULZBOT_DEFAULT_TRAVEL_ACCELERATION   3000
    #define LULZBOT_DEFAULT_XJERK                 8.0
    #define LULZBOT_DEFAULT_YJERK                 8.0
    #define LULZBOT_DEFAULT_ZJERK                 0.4
    #define LULZBOT_DEFAULT_EJERK                10.0

    #define LULZBOT_Z_MAX_POS                     290
    #define LULZBOT_Z_MIN_POS                       0

#elif defined(LULZBOT_Gladiola_Mini)
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {800, 800, 8, 40}      // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,100,10000}
    #define LULZBOT_XY_STEPS                      100.5
    #define LULZBOT_Z_STEPS                       1600
    #define LULZBOT_E_STEPS                       833
    #define LULZBOT_DEFAULT_ACCELERATION          2000
    #define LULZBOT_DEFAULT_TRAVEL_ACCELERATION   3000
    #define LULZBOT_DEFAULT_XJERK                 12.0
    #define LULZBOT_DEFAULT_YJERK                 12.0
    #define LULZBOT_DEFAULT_ZJERK                  0.4
    #define LULZBOT_DEFAULT_EJERK                 10.0

    #define LULZBOT_Z_MAX_POS                      159
    #define LULZBOT_Z_MIN_POS                       -2

#elif defined(LULZBOT_Oliveoil_TAZ_6)
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {800, 800, 3, 40}      // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,100,10000}
    #define LULZBOT_XY_STEPS                      100.5
    #define LULZBOT_Z_STEPS                       1600
    #define LULZBOT_E_STEPS                       830
    #define LULZBOT_DEFAULT_ACCELERATION          500
    #define LULZBOT_DEFAULT_TRAVEL_ACCELERATION   3000
    #define LULZBOT_DEFAULT_XJERK                 8.0
    #define LULZBOT_DEFAULT_YJERK                 8.0
    #define LULZBOT_DEFAULT_ZJERK                 0.4
    #define LULZBOT_DEFAULT_EJERK                10.0

    #define LULZBOT_Z_MAX_POS                     270
    #define LULZBOT_Z_MIN_POS                       0
#endif

// default steps per unit for LulzBot TAZ

#if LULZBOT_EXTRUDERS == 1
    #define LULZBOT_DEFAULT_AXIS_STEPS_PER_UNIT   {LULZBOT_XY_STEPS,LULZBOT_XY_STEPS,LULZBOT_Z_STEPS,LULZBOT_E_STEPS}
#elif LULZBOT_EXTRUDERS == 2
    #define LULZBOT_DEFAULT_AXIS_STEPS_PER_UNIT   {LULZBOT_XY_STEPS,LULZBOT_XY_STEPS,LULZBOT_Z_STEPS,LULZBOT_E_STEPS,LULZBOT_E_STEPS}
#elif LULZBOT_EXTRUDERS == 3
    #define LULZBOT_DEFAULT_AXIS_STEPS_PER_UNIT   {LULZBOT_XY_STEPS,LULZBOT_XY_STEPS,LULZBOT_Z_STEPS,LULZBOT_E_STEPS,LULZBOT_E_STEPS,LULZBOT_E_STEPS}
#elif LULZBOT_EXTRUDERS == 4
    #define LULZBOT_DEFAULT_AXIS_STEPS_PER_UNIT   {LULZBOT_XY_STEPS,LULZBOT_XY_STEPS,LULZBOT_Z_STEPS,LULZBOT_E_STEPS,LULZBOT_E_STEPS,830,LULZBOT_E_STEPS}
#endif

// Nozzle wiping points

#define LULZBOT_NOZZLE_CLEAN_START_POINT      {LULZBOT_WIPE_X1, LULZBOT_WIPE_Y1, 1}
#define LULZBOT_NOZZLE_CLEAN_END_POINT        {LULZBOT_WIPE_X2, LULZBOT_WIPE_Y2, 1}

// Gralco's customized Z Offset overlay (also requires dogm_bitmaps_Lulzbot.h)

#define LULZBOT_ZOFFSET_OVERLAY(zprobe_zoffset) \
    static float old_zprobe_zoffset = 0; \
    static bool up_arrow; \
    if(zprobe_zoffset != old_zprobe_zoffset) { \
        up_arrow = zprobe_zoffset > old_zprobe_zoffset; \
    } \
    old_zprobe_zoffset = zprobe_zoffset; \
    uint8_t noz_pos = -6*zprobe_zoffset; \
    u8g.drawBitmapP(66,noz_pos,2,12,nozzle_bmp); \
    u8g.drawBitmapP(60,24,3,1,offset_bedline_bmp); \
    u8g.drawBitmapP(0,47,3,16,ccw_bmp); \
    u8g.drawStr(27,60,"Z"); \
    u8g.drawBitmapP(34,49,2,10,down_arrow_bmp); \
    u8g.drawBitmapP(85,47,3,16,cw_bmp); \
    u8g.drawStr(107,60,"Z"); \
    u8g.drawBitmapP(113,51,2,10,up_arrow_bmp); \
    if (up_arrow) { \
        u8g.setColorIndex(0); \
        u8g.drawBox(113,46,16,13); \
        u8g.setColorIndex(1); \
        u8g.drawBitmapP(113,48,2,13,longup_arrow_bmp); \
    } else { \
        u8g.setColorIndex(0); \
        u8g.drawBox(34,49,16,13); \
        u8g.setColorIndex(1); \
        u8g.drawBitmapP(34,49,2,13,longdown_arrow_bmp); \
    }

// Customized splash screen
#define LULZBOT_CUSTOM_BOOTSCREEN() \
    u8g.firstPage(); \
    do { \
        u8g.drawBitmapP(0,0,CEILING(CUSTOM_BOOTSCREEN_BMPWIDTH, 8),CUSTOM_BOOTSCREEN_BMPHEIGHT,custom_start_bmp); \
        u8g.setFont(u8g_font_6x13); \
        u8g.drawStr(61,17,LULZBOT_CUSTOM_MACHINE_NAME); \
        u8g.setFont(u8g_font_04b_03); \
        u8g.drawStr(62,28,LULZBOT_TOOLHEAD_NAME); \
        u8g.setFont(u8g_font_5x8); \
        u8g.drawStr(63,41,"LulzBot.com"); \
        u8g.setFont(u8g_font_5x8); \
        u8g.drawStr(62,62,"v"); \
        u8g.drawStr(67,62,SHORT_BUILD_VERSION LULZBOT_FW_VERSION); \
    } while( u8g.nextPage() );

#endif /* CONFIGURATION_LULZBOT */
