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
    !defined(LULZBOT_Hibiscus_Mini) && \
    !defined(LULZBOT_Gladiola_GLCD) && \
    !defined(LULZBOT_Hibiscus_GLCD) && \
    !defined(LULZBOT_Juniper_TAZ_5) && \
    !defined(LULZBOT_Oliveoil_TAZ_6) && \
    !defined(LULZBOT_Quiver_TAZ_7) \
) || ( \
    !defined(TOOLHEAD_Gladiola_SingleExtruder) && \
    !defined(TOOLHEAD_Albatross_Flexystruder) && \
    !defined(TOOLHEAD_Finch_Aero) && \
    !defined(TOOLHEAD_Tilapia_SingleExtruder) && \
    !defined(TOOLHEAD_Kanyu_Flexystruder) && \
    !defined(TOOLHEAD_Opah_Moarstruder) && \
    !defined(TOOLHEAD_Javelin_DualExtruder) && \
    !defined(TOOLHEAD_Longfin_FlexyDually) && \
    !defined(TOOLHEAD_Yellowfin_DualExtruder) && \
    !defined(TOOLHEAD_Angelfish_Aero) && \
    !defined(TOOLHEAD_ServoDual) \
)
    #error Must specify model and toolhead. Please see "Configuration_LulzBot.h" for directions.
#endif

#define LULZBOT_FW_VERSION ".32"

// Select options based on printer model

#if defined(LULZBOT_Gladiola_Mini)
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
    #define LULZBOT_USE_AUTOLEVELING
    #define LULZBOT_USE_MAX_ENDSTOPS
    #define LULZBOT_BAUDRATE 115200
#endif

#if defined(LULZBOT_Hibiscus_Mini)
    // Prototype Mini w/ Z-Belt
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini 2"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
    #define LULZBOT_USE_AUTOLEVELING
    #define LULZBOT_USE_MAX_ENDSTOPS
    #define LULZBOT_USE_NORMALLY_CLOSED_ENDSTOPS
    #define LULZBOT_BAUDRATE 250000
    #define LULZBOT_PRINTERCOUNTER
#endif

#if defined(LULZBOT_Gladiola_GLCD)
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini GLCD"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
    #define LULZBOT_USE_LCD_DISPLAY
    #define LULZBOT_USE_AUTOLEVELING
    #define LULZBOT_USE_MAX_ENDSTOPS
    #define LULZBOT_BAUDRATE 115200
#endif

#if defined(LULZBOT_Hibiscus_GLCD)
    // Prototype Mini w/ Z-Belt
    #define LULZBOT_CUSTOM_MACHINE_NAME "Mini 2 GLCD"
    #define LULZBOT_IS_MINI
    #define LULZBOT_MINI_BED
    #define LULZBOT_USE_LCD_DISPLAY
    #define LULZBOT_USE_AUTOLEVELING
    #define LULZBOT_USE_MAX_ENDSTOPS
    #define LULZBOT_USE_NORMALLY_CLOSED_ENDSTOPS
    #define LULZBOT_BAUDRATE 250000
    #define LULZBOT_PRINTERCOUNTER
#endif

#if defined(LULZBOT_Juniper_TAZ_5)
    #define LULZBOT_CUSTOM_MACHINE_NAME "TAZ 5"
    #define LULZBOT_IS_TAZ
    #define LULZBOT_TAZ_BED
    #define LULZBOT_USE_LCD_DISPLAY
    #define LULZBOT_BAUDRATE 250000
#endif

#if defined(LULZBOT_Oliveoil_TAZ_6)
    #define LULZBOT_CUSTOM_MACHINE_NAME "TAZ 6"
    #define LULZBOT_IS_TAZ
    #define LULZBOT_TAZ_BED
    #define LULZBOT_USE_LCD_DISPLAY
    #define LULZBOT_USE_AUTOLEVELING
    #define LULZBOT_USE_MAX_ENDSTOPS
    #define LULZBOT_USE_HOME_BUTTON
    #define LULZBOT_USE_NORMALLY_CLOSED_ENDSTOPS
    #define LULZBOT_BAUDRATE 250000
#endif

#if defined(LULZBOT_Quiver_TAZ_7)
    // Prototype TAZ w/ Z-Belt
    #define LULZBOT_CUSTOM_MACHINE_NAME "TAZ 7"
    #define LULZBOT_IS_TAZ
    #define LULZBOT_TAZ_BED
    #define LULZBOT_USE_LCD_DISPLAY
    #define LULZBOT_USE_AUTOLEVELING
    #define LULZBOT_USE_MAX_ENDSTOPS
    #define LULZBOT_USE_NORMALLY_CLOSED_ENDSTOPS
    #define LULZBOT_BAUDRATE 250000
    #define LULZBOT_PRINTERCOUNTER
#endif

// Shared values
#define LULZBOT_STRING_CONFIG_H_AUTHOR        "(Aleph Objects Inc., LulzBot Diffusion)"
#define LULZBOT_BUFSIZE                       10
#define LULZBOT_EEPROM_SETTINGS
#define LULZBOT_EMERGENCY_PARSER

// Prior branches of the LulzBot firmware used G26
// to reset a probe failed condition. Marlin upstrem
// now redefines that for unified bed leveling. The
// following maps G26 to M999 for equivalent behavior,
// so long as UBL is disabled.
#define LULZBOT_G26_BACKWARDS_COMPATIBILITY

// The following should be kept more or less:
#define LULZBOT_G26_RESET_ACTION \
  Running = true; \
  lcd_reset_alert_level();

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

#if defined(TOOLHEAD_ServoDual)
    #undef LULZBOT_USE_HOME_BUTTON
#endif

#if defined(LULZBOT_IS_MINI)
    #define LULZBOT_MOTHERBOARD                   BOARD_MINIRAMBO
    #define LULZBOT_CONTROLLER_FAN_PIN            FAN1_PIN  // Digital pin 6

#elif defined(LULZBOT_IS_TAZ)
    #define LULZBOT_MOTHERBOARD                   BOARD_RAMBO
    #define LULZBOT_CONTROLLER_FAN_PIN            FAN2_PIN  // Digital pin 2
#endif

#if defined(LULZBOT_USE_HOME_BUTTON)
    #define LULZBOT_Z_MIN_PROBE_ENDSTOP
    #define LULZBOT_Z_MIN_PROBE_PIN               SERVO0_PIN // Digital pin 22
    // On the TAZ 6, the bed washers are on Z_MIN_PROBE while the
    // Z-Home button is on Z_MIN, yet we need both to be disabled
    // when z_probe_enabled is false. We added this special case
    // to "endstops.cpp"
    #define LULZBOT_Z_MIN_USES_Z_PROBE_ENABLED
#else
    // The Mini and TAZ 7+ lack a home button and probe using the Z_MIN pin.
    #define LULZBOT_Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN
#endif

#define LULZBOT_USE_CONTROLLER_FAN
#define LULZBOT_USE_XMIN_PLUG
#define LULZBOT_USE_YMIN_PLUG
#define LULZBOT_USE_ZMIN_PLUG

// Z-Max Endstops were introduced on the Mini and TAZ 6
#if defined(LULZBOT_USE_MAX_ENDSTOPS)
    #define LULZBOT_USE_XMAX_PLUG
    #define LULZBOT_USE_YMAX_PLUG
    #define LULZBOT_USE_ZMAX_PLUG
#endif

#define LULZBOT_ENDSTOPS_ALWAYS_ON_DEFAULT
#define LULZBOT_ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED

// The RAMBO does not support interrupts on all pins
// so leave the ENDSTOP_INTERRUPTS_FEATURE disabled

//#define LULZBOT_ENDSTOP_INTERRUPTS_FEATURE

/* Endstop settings are determined by printer model, except for the
 * X_MAX which varies by toolhead. */

#if defined(LULZBOT_USE_NORMALLY_CLOSED_ENDSTOPS)
    // TAZ 6+ and Huerfano Mini onwards use normally closed endstops.
    // This is safer, as a loose connector or broken wire will halt
    // the axis
    #define LULZBOT_X_MIN_ENDSTOP_INVERTING       false
    #define LULZBOT_Y_MIN_ENDSTOP_INVERTING       false
    #define LULZBOT_Y_MAX_ENDSTOP_INVERTING       false
    #define LULZBOT_Z_MAX_ENDSTOP_INVERTING       false
#else
    #define LULZBOT_X_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Y_MIN_ENDSTOP_INVERTING       true
    #define LULZBOT_Y_MAX_ENDSTOP_INVERTING       true
    #define LULZBOT_Z_MAX_ENDSTOP_INVERTING       true
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
    #define LULZBOT_INVERT_X_HOME_DIR             -1 // Home left
    #define LULZBOT_INVERT_Y_HOME_DIR              1 // Home bed forward
    #define LULZBOT_INVERT_Z_HOME_DIR              1 // Home to top
    #define LULZBOT_QUICKHOME

#elif defined(LULZBOT_Juniper_TAZ_5)
    #define LULZBOT_HOMING_Z_WITH_PROBE           false
    #define LULZBOT_INVERT_X_HOME_DIR             -1 // Home left
    #define LULZBOT_INVERT_Y_HOME_DIR             -1 // Home bed rear
    #define LULZBOT_INVERT_Z_HOME_DIR             -1 // Home towards bed
    #define LULZBOT_QUICKHOME

#elif defined(LULZBOT_IS_TAZ) && !defined(LULZBOT_USE_HOME_BUTTON)
    #define LULZBOT_INVERT_X_HOME_DIR             -1 // Home left
    #define LULZBOT_INVERT_Y_HOME_DIR              1 // Home bed forward
    #define LULZBOT_INVERT_Z_HOME_DIR              1 // Home to top
    #define LULZBOT_QUICKHOME

#elif defined(LULZBOT_IS_TAZ) &&  defined(LULZBOT_USE_HOME_BUTTON)
    #define LULZBOT_INVERT_X_HOME_DIR             -1 // Home left
    #define LULZBOT_INVERT_Y_HOME_DIR              1 // Home bed forward
    #define LULZBOT_INVERT_Z_HOME_DIR             -1 // Home towards bed
    #define LULZBOT_QUICKHOME
#endif

#if defined(LULZBOT_MINI_BED)
    #define LULZBOT_HOMING_FEEDRATE_XY            (30*60) // mm/m
    #define LULZBOT_HOMING_FEEDRATE_Z              (8*60) // mm/m
#elif defined(LULZBOT_Quiver_TAZ_7)
    #define LULZBOT_HOMING_FEEDRATE_XY            (50*60) // mm/m
    #define LULZBOT_HOMING_FEEDRATE_Z             (10*60) // mm/m
#elif defined(LULZBOT_TAZ_BED)
    #define LULZBOT_HOMING_FEEDRATE_XY            (50*60) // mm/m
    #define LULZBOT_HOMING_FEEDRATE_Z             (3*60)  // mm/m
#endif // LULZBOT_TAZ_BED

#if defined(LULZBOT_USE_AUTOLEVELING) && defined(LULZBOT_MINI_BED)
    #define LULZBOT_LEFT_PROBE_BED_POSITION        0
    #define LULZBOT_RIGHT_PROBE_BED_POSITION     164
    #define LULZBOT_BACK_PROBE_BED_POSITION      162
    #define LULZBOT_FRONT_PROBE_BED_POSITION      -6

#elif defined(LULZBOT_USE_AUTOLEVELING) && defined(LULZBOT_TAZ_BED)
    #define LULZBOT_LEFT_PROBE_BED_POSITION       -9
    #define LULZBOT_RIGHT_PROBE_BED_POSITION     288
    #define LULZBOT_BACK_PROBE_BED_POSITION      289
    #define LULZBOT_FRONT_PROBE_BED_POSITION      -9
#endif

// Only the TAZ 6 has a Z-homing button
#if defined(LULZBOT_USE_HOME_BUTTON)
    #define LULZBOT_Z_SAFE_HOMING
    #define LULZBOT_Z_SAFE_HOMING_X_POINT         (-19)
    #define LULZBOT_Z_SAFE_HOMING_Y_POINT         (258)
    #define LULZBOT_Z_HOMING_HEIGHT               5

    #define LULZBOT_AFTER_Z_HOME_Z_RAISE          5
    #define LULZBOT_AFTER_Z_HOME_Z_ORIGIN         0
#elif defined(LULZBOT_Juniper_TAZ_5)
    // Set safe homing position so fan duct does not hit.
    #define LULZBOT_Z_SAFE_HOMING
    #define LULZBOT_Z_SAFE_HOMING_X_POINT         10
    #define LULZBOT_Z_SAFE_HOMING_Y_POINT         10
    #define LULZBOT_Z_HOMING_HEIGHT               5
#else
    #define LULZBOT_Z_HOMING_HEIGHT               0
#endif  // LULZBOT_USE_HOME_BUTTON

#if defined(LULZBOT_USE_AUTOLEVELING)
    #define LULZBOT_NOZZLE_CLEAN_FEATURE
    // Select type of leveling to use:
    //#define LULZBOT_AUTO_BED_LEVELING_BILINEAR
    #define LULZBOT_AUTO_BED_LEVELING_3POINT
#endif

#if defined(LULZBOT_AUTO_BED_LEVELING_3POINT)
  // Experimental three point leveling.
  #define LULZBOT_ABL_PROBE_PT_1_X LULZBOT_LEFT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_1_Y LULZBOT_FRONT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_2_X LULZBOT_RIGHT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_2_Y LULZBOT_FRONT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_3_X LULZBOT_RIGHT_PROBE_BED_POSITION
  #define LULZBOT_ABL_PROBE_PT_3_Y LULZBOT_BACK_PROBE_BED_POSITION
#elif defined(LULZBOT_AUTO_BED_LEVELING_BILINEAR)
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

/* Auto-leveling was introduced on the Mini and TAZ 6.
 * Define probe parameters related to bed leveling,
 * e.g. the washers on the bed. These are confusingly
 * named Z_MIN_PROBE in Marlin. The Z-Home switch
 * is called Z_MIN_ENDSTOP
 */
#if defined(LULZBOT_USE_AUTOLEVELING)
    #define LULZBOT_FIX_MOUNTED_PROBE
#endif // LULZBOT_USE_AUTOLEVELING

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
 *   Z_MIN_PROBE_PIN are the bed washers.
 */
#if defined(LULZBOT_USE_AUTOLEVELING) && defined(LULZBOT_MINI_BED)
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

#elif defined(LULZBOT_USE_AUTOLEVELING) && defined(LULZBOT_USE_HOME_BUTTON)
    #define LULZBOT_ENABLE_PROBE_PINS(enable) { \
        if(enable) { \
            /* Set both as inputs with pull-up resistor */ \
            SET_INPUT(LULZBOT_Z_MIN_PROBE_PIN); \
            WRITE(LULZBOT_Z_MIN_PROBE_PIN, HIGH); \
            SET_INPUT(Z_MIN_PIN); \
            WRITE(Z_MIN_PIN, HIGH); \
            /* The following is required since Marlin would \
             * not normally deploy the probe for Z-Min */ \
            endstops.enable_z_probe(true); \
        } else { \
            /* Ground both pins to prevent EMI */ \
            SET_OUTPUT(LULZBOT_Z_MIN_PROBE_PIN); \
            WRITE(LULZBOT_Z_MIN_PROBE_PIN, LOW); \
            SET_OUTPUT(Z_MIN_PIN); \
            WRITE(Z_MIN_PIN, LOW); \
            endstops.enable_z_probe(false); \
        } \
    }
#else
    #define LULZBOT_ENABLE_PROBE_PINS(enable)
#endif

/* Make it so M42 S<state> controls the state of the
/* probe lines. This is useful for troubleshooting. */
#define LULZBOT_M42_TOGGLES_PROBE_PINS \
    if (!parser.seenval('P')) { \
      LULZBOT_ENABLE_PROBE_PINS(pin_status); \
      return; \
    }

#define LULZBOT_FAN_KICKSTART_TIME          100
#define LULZBOT_FAN_MIN_PWM                  70
#define LULZBOT_HOST_KEEPALIVE_FEATURE_DISABLED

#if defined(LULZBOT_USE_LCD_DISPLAY)
    #define LULZBOT_REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
    #define LULZBOT_SDSUPPORT
    #define LULZBOT_XYZ_HOLLOW_FRAME_DISABLE
    #define LULZBOT_MENU_HOLLOW_FRAME_DISABLE
    #define LULZBOT_USE_SMALL_INFOFONT
    #if defined(LULZBOT_USE_AUTOLEVELING)
        #define LULZBOT_BABYSTEPPING
        #define LULZBOT_BABYSTEP_ZPROBE_OFFSET
        #define LULZBOT_MENU_BED_LEVELING_GCODE "G28 XY\nM109 S175\nG28 Z\nM109 R145\nG12\nG29\nM104 S0"
    #endif
    #define LULZBOT_SHOW_CUSTOM_BOOTSCREEN
    #define LULZBOT_ENCODER_PULSES_PER_STEP 2
    #define LULZBOT_ENCODER_STEPS_PER_MENU_ITEM 1
    #define LULZBOT_COOLING_MESSAGES
    #if defined(LULZBOT_Gladiola_GLCD) || defined(LULZBOT_Hibiscus_GLCD)
        // In the experimental Gladiola_GLCD, the encoder direction is reversed.
        #define LULZBOT_REVERSE_ENCODER_DIRECTION
    #endif
    /* Marlin shows three extruders on a dual:
     *   Extruder    - The active nozzle (varies)
     *   Extruder 1  - The primary extruder
     *   Extruder 2  - The secondary extruder
     *
     * The following causes the active nozzle to be
     * hidden as seeing three nozzles may be
     * confusing to users.
     */
    #define LULZBOT_HIDE_ACTIVE_NOZZLE_IN_LCD
    #define LULZBOT_HIDE_PID_CONFIG_IN_LCD
#endif

/*********************************************** COMMON TOOLHEADS PARAMETERS *****************************/

#define LULZBOT_DEFAULT_EJERK                10.0
#if defined(LULZBOT_IS_TAZ)
    #define LULZBOT_E_STEPS                  830
#elif defined(LULZBOT_IS_MINI)
    #define LULZBOT_E_STEPS                  833
#endif

/*********************************************** MINI TOOLHEADS *******************************************/

#if defined(TOOLHEAD_Gladiola_SingleExtruder) || defined(TOOLHEAD_Albatross_Flexystruder) || defined(TOOLHEAD_Finch_Aero)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING
    #define LULZBOT_UUID                       "351487b6-ca9a-4c1a-8765-d668b1da6585"
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_TOOLHEAD_X_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_X_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Y_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Y_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ       0
    #define LULZBOT_AO_Hexagon
    #define PWM_MOTOR_CURRENT_E               1250
#endif /* TOOLHEAD_Gladiola_SingleExtruder || TOOLHEAD_Albatross_Flexystruder || TOOLHEAD_Finch_Aero */

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

#if defined(TOOLHEAD_Finch_Aero)
    // Prototype Aero toolhead for Mini
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Titan AERO"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING        true
#endif /* TOOLHEAD_Finch_Aero */

/*********************************************** TAZ TOOLHEADS *******************************************/

#if defined(TOOLHEAD_Tilapia_SingleExtruder) || defined(TOOLHEAD_Angelfish_Aero)
    #define LULZBOT_TOOLHEAD_VER                    VERSION_STRING
    #define LULZBOT_UUID                            "845f003c-aebd-4e53-a6b9-7d0984fde609"
    #define LULZBOT_EXTRUDERS                  1
    #define LULZBOT_TOOLHEAD_X_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_X_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Y_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Y_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ       0
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
    #define LULZBOT_TOOLHEAD_X_MAX_ADJ         12
    #define LULZBOT_TOOLHEAD_X_MIN_ADJ         7
    #define LULZBOT_TOOLHEAD_Y_MAX_ADJ         1
    #define LULZBOT_TOOLHEAD_Y_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ       0
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
    #define LULZBOT_TOOLHEAD_X_MAX_ADJ         10
    #define LULZBOT_TOOLHEAD_X_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Y_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Y_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ       0
    #define LULZBOT_Moarstruder
#endif /* TOOLHEAD_Opah_Moarstruder */

#if defined(TOOLHEAD_Javelin_DualExtruder) || defined(TOOLHEAD_Longfin_FlexyDually) || defined(TOOLHEAD_Yellowfin_DualExtruder) || defined(TOOLHEAD_ServoDual)
    #define LULZBOT_TOOLHEAD_VER               VERSION_STRING" Dual"
    #define LULZBOT_BUILD_VARIANT              " LulzBot Dual"
    #define LULZBOT_EXTRUDER_FAN_ON_PIN_6      // For backwards compatibility with TAZ 4
    #define DIGIPOT_MOTOR_CURRENT_E            160, 160  // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
    #define LULZBOT_EXTRUDERS                  2
    #define LULZBOT_UUID                       "c5077702-4ecd-4532-beaf-6acf94acc404"
    #define LULZBOT_TOOLHEAD_X_MAX_ADJ         12
    #define LULZBOT_TOOLHEAD_X_MIN_ADJ         2
    #define LULZBOT_TOOLHEAD_Y_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Y_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MAX_ADJ         0
    #define LULZBOT_TOOLHEAD_Z_MIN_ADJ         0
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ       0
    #define LULZBOT_TEMP_SENSOR_1              5
    #define LULZBOT_AO_Hexagon
    #define LULZBOT_NO_MOVE_ON_TOOLHEAD_CHANGE
#endif /* TOOLHEAD_Javelin_DualExtruder || TOOLHEAD_Longfin_FlexyDually || TOOLHEAD_Yellowfin_DualExtruder */

#if defined(TOOLHEAD_Javelin_DualExtruder)
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Dual Extruder 2"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ      48
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
#endif /* TOOLHEAD_Javelin_DualExtruder */

#if defined(TOOLHEAD_Longfin_FlexyDually)
    #define LULZBOT_LCD_TOOLHEAD_NAME              "FlexyDually v2"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ       0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ      48
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING    true
    #define LULZBOT_DISTINCT_E_FACTORS
#endif /* TOOLHEAD_Longfin_FlexyDually */

#if defined(TOOLHEAD_Yellowfin_DualExtruder)
    // Prototype Dual v3 for TAZ.
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Dual Extruder 3"
//          16 chars max                            ^^^^^^^^^^^^^^^
#endif /* TOOLHEAD_Yellowfin_DualExtruder */

#if defined(TOOLHEAD_ServoDual)
    // Experimental dual nozzle using a servo
    #define LULZBOT_LCD_TOOLHEAD_NAME              "Servo McStruder"
//          16 chars max                            ^^^^^^^^^^^^^^^
    #define LULZBOT_NUM_SERVOS                     1
    #define LULZBOT_SWITCHING_NOZZLE
#endif /* TOOLHEAD_ServoDual */

#if defined(TOOLHEAD_Yellowfin_DualExtruder) || defined(TOOLHEAD_ServoDual)
    #undef  LULZBOT_AFTER_Z_HOME_Z_RAISE
    #define LULZBOT_AFTER_Z_HOME_Z_RAISE           16
    #undef  LULZBOT_AFTER_Z_HOME_Z_ORIGIN
    #define LULZBOT_AFTER_Z_HOME_Z_ORIGIN          5.5
    #define LULZBOT_TOOLHEAD_WIPE_X1_ADJ          -6
    #define LULZBOT_TOOLHEAD_WIPE_X2_ADJ          -6
    #define LULZBOT_TOOLHEAD_WIPE_Y1_ADJ           0
    #define LULZBOT_TOOLHEAD_WIPE_Y2_ADJ           0
    #undef  LULZBOT_Z_HOMING_HEIGHT
    #define LULZBOT_Z_HOMING_HEIGHT                10
    #undef  LULZBOT_Z_CLEARANCE_DEPLOY_PROBE
    #define LULZBOT_Z_CLEARANCE_DEPLOY_PROBE       10
    #undef  LULZBOT_Z_CLEARANCE_BETWEEN_PROBES
    #define LULZBOT_Z_CLEARANCE_BETWEEN_PROBES     10
    #undef  LULZBOT_BACK_PROBE_BED_POSITION
    #define LULZBOT_BACK_PROBE_BED_POSITION       293
    #if defined(LULZBOT_USE_HOME_BUTTON)
        #undef  LULZBOT_Z_SAFE_HOMING_X_POINT
        #undef  LULZBOT_Z_SAFE_HOMING_Y_POINT
        #define LULZBOT_Z_SAFE_HOMING_X_POINT        (-22)    // X point for Z homing when homing all axis (G28)
        #define LULZBOT_Z_SAFE_HOMING_Y_POINT        (265)    // Y point for Z homing when homing all axis (G28)
    #endif /* LULZBOT_USE_HOME_BUTTON */
    #undef  LULZBOT_TOOLHEAD_X_MAX_ADJ
    #define LULZBOT_TOOLHEAD_X_MAX_ADJ             10
    #define LULZBOT_X_MAX_ENDSTOP_INVERTING       false
    #define LULZBOT_SWAP_EXTRUDERS
    #undef  LULZBOT_INVERT_E1_DIR
    #define LULZBOT_INVERT_E1_DIR                 false
    #undef  LULZBOT_E_STEPS
    #define LULZBOT_E_STEPS                        760
    #define LULZBOT_AO_Hexagon
#endif /* TOOLHEAD_Yellowfin_DualExtruder */

/*********************************** AXIS TRAVEL LIMITS *******************************************/

/* Define min and max travel limits based on the printer model using a standard
 * toolhead, then define adjustments from the standard for alternative toolheads.
 * This allows us to accomodate toolheads that might be wider or taller than the
 * standard.
 */

#if defined(LULZBOT_IS_MINI)
    #define LULZBOT_STANDARD_X_MAX_POS         175
    #define LULZBOT_STANDARD_X_MIN_POS           0
    #define LULZBOT_STANDARD_Y_MAX_POS         191
    #define LULZBOT_STANDARD_Y_MIN_POS         -10

#elif defined(LULZBOT_Juniper_TAZ_5)
    #define LULZBOT_STANDARD_X_MAX_POS         298
    #define LULZBOT_STANDARD_X_MIN_POS           0
    #define LULZBOT_STANDARD_Y_MAX_POS         275
    #define LULZBOT_STANDARD_Y_MIN_POS           0

#elif defined(LULZBOT_IS_TAZ)
    #define LULZBOT_STANDARD_X_MAX_POS         300
    #define LULZBOT_STANDARD_X_MIN_POS         -20
    #define LULZBOT_STANDARD_Y_MAX_POS         303
    #define LULZBOT_STANDARD_Y_MIN_POS         -20
#endif

#if defined(LULZBOT_Gladiola_Mini) || defined(LULZBOT_Gladiola_GLCD)
    #define LULZBOT_STANDARD_Z_MIN_POS           0
    #define LULZBOT_STANDARD_Z_MAX_POS         160

#elif defined(LULZBOT_Hibiscus_Mini) || defined(LULZBOT_Hibiscus_GLCD)
    #define LULZBOT_STANDARD_Z_MIN_POS           0
    #define LULZBOT_STANDARD_Z_MAX_POS         178

#elif defined(LULZBOT_Juniper_TAZ_5)
    #define LULZBOT_STANDARD_Z_MIN_POS           0
    #define LULZBOT_STANDARD_Z_MAX_POS         250

#elif defined(LULZBOT_Oliveoil_TAZ_6)
    #define LULZBOT_STANDARD_Z_MIN_POS           0
    #define LULZBOT_STANDARD_Z_MAX_POS         270

#elif defined(LULZBOT_Quiver_TAZ_7)
    #define LULZBOT_STANDARD_Z_MIN_POS           0
    #define LULZBOT_STANDARD_Z_MAX_POS         290
#endif

#define LULZBOT_X_MAX_POS (LULZBOT_STANDARD_X_MAX_POS - LULZBOT_TOOLHEAD_X_MAX_ADJ)
#define LULZBOT_X_MIN_POS (LULZBOT_STANDARD_X_MIN_POS - LULZBOT_TOOLHEAD_X_MIN_ADJ)
#define LULZBOT_Y_MAX_POS (LULZBOT_STANDARD_Y_MAX_POS - LULZBOT_TOOLHEAD_Y_MAX_ADJ)
#define LULZBOT_Y_MIN_POS (LULZBOT_STANDARD_Y_MIN_POS - LULZBOT_TOOLHEAD_Y_MIN_ADJ)
#define LULZBOT_Z_MAX_POS (LULZBOT_STANDARD_Z_MAX_POS - LULZBOT_TOOLHEAD_Z_MAX_ADJ)
#define LULZBOT_Z_MIN_POS (LULZBOT_STANDARD_Z_MIN_POS - LULZBOT_TOOLHEAD_Z_MIN_ADJ)

/*********************************** WIPER PAD **********************************/

// Nozzle wiping points (varies by toolhead, as the nozzle position varies)

#if defined(LULZBOT_USE_AUTOLEVELING) && defined(LULZBOT_MINI_BED)
    // Mini has a horizontal wiping pad on the back of the bed
    #define LULZBOT_STANDARD_WIPE_X1                       115
    #define LULZBOT_STANDARD_WIPE_X2                       45
    #define LULZBOT_STANDARD_WIPE_Y1                       173
    #define LULZBOT_STANDARD_WIPE_Y2                       173

#elif defined(LULZBOT_USE_AUTOLEVELING) && defined(LULZBOT_TAZ_BED)
    // TAZ has a vertical wiping pad on the left side of the bed
    #define LULZBOT_STANDARD_WIPE_X1                      -16
    #define LULZBOT_STANDARD_WIPE_X2                      -16
    #define LULZBOT_STANDARD_WIPE_Y1                       95
    #define LULZBOT_STANDARD_WIPE_Y2                       25
#endif

#define LULZBOT_NOZZLE_CLEAN_START_POINT { \
    LULZBOT_STANDARD_WIPE_X1 + LULZBOT_TOOLHEAD_WIPE_X1_ADJ, \
    LULZBOT_STANDARD_WIPE_Y1 + LULZBOT_TOOLHEAD_WIPE_Y1_ADJ, \
    1 \
}

#define LULZBOT_NOZZLE_CLEAN_END_POINT   { \
    LULZBOT_STANDARD_WIPE_X2 + LULZBOT_TOOLHEAD_WIPE_X2_ADJ, \
    LULZBOT_STANDARD_WIPE_Y2 + LULZBOT_TOOLHEAD_WIPE_Y2_ADJ, \
    1 \
}

/*********************************** HEATING ELEMENTS ****************************/

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

// Acceleration, feedrate, motor steps and motor currents for XYZ vary
// by printer model (steps and motor currents for E vary by toolhead).

#if defined(LULZBOT_IS_MINI)
    #define PWM_MOTOR_CURRENT_XY                  1300
    #define LULZBOT_XY_STEPS                      100.5
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {300, 300, 8, 40}      // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,100,10000}

    #define LULZBOT_DEFAULT_XJERK                 12.0
    #define LULZBOT_DEFAULT_YJERK                 12.0
    #define LULZBOT_DEFAULT_ZJERK                  0.4

    #define LULZBOT_DEFAULT_ACCELERATION          2000
    #define LULZBOT_DEFAULT_TRAVEL_ACCELERATION   3000

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
    #define LULZBOT_Z_PROBE_OFFSET_FROM_EXTRUDER -1.5
#endif

#if defined(LULZBOT_Gladiola_Mini) || defined(LULZBOT_Gladiola_GLCD)
    #define PWM_MOTOR_CURRENT_Z                   1630
    #define LULZBOT_Z_STEPS                       1600

#elif defined(LULZBOT_Hibiscus_Mini) || defined(LULZBOT_Hibiscus_GLCD)
    #define PWM_MOTOR_CURRENT_Z                   1000
    // Prototype Z-Belt Mini
    #define Z_FULL_STEPS_PER_ROTATION             200
    #define Z_MICROSTEPS                          16
    #define Z_BELT_PITCH                          2
    #define Z_PULLEY_TEETH                        24
    #define Z_MOTOR_GEAR_REDUCTION                26.8512396694
    #define LULZBOT_Z_STEPS (Z_FULL_STEPS_PER_ROTATION * Z_MICROSTEPS * Z_MOTOR_GEAR_REDUCTION / double(Z_BELT_PITCH) / double(Z_PULLEY_TEETH))

    #undef  LULZBOT_DEFAULT_MAX_FEEDRATE
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {300, 300, 16, 25}      // (mm/sec)

#elif defined(LULZBOT_Juniper_TAZ_5)
    #define DIGIPOT_MOTOR_CURRENT_Z               240
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {300, 300, 3, 25}      // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,100,10000}
    #define LULZBOT_Z_STEPS                       1600

#elif defined(LULZBOT_Oliveoil_TAZ_6)
    #define DIGIPOT_MOTOR_CURRENT_Z               200
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {300, 300, 3, 25}      // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,100,10000}
    #define LULZBOT_Z_STEPS                       1600

#elif defined(LULZBOT_Quiver_TAZ_7)
    #define DIGIPOT_MOTOR_CURRENT_Z               175
    // Prototype Z-belt driven TAZ 7
    #define LULZBOT_DEFAULT_MAX_FEEDRATE          {300, 300, 10, 25}   // (mm/sec)
    #define LULZBOT_DEFAULT_MAX_ACCELERATION      {9000,9000,10,10000}
    #define LULZBOT_Z_STEPS                       1790.08264463
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
            stop();                                   /* stop print job */ \
            LCD_MESSAGEPGM(MSG_LEVEL_FAIL);           /* stop changes the message... */ \
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

#if defined(LULZBOT_USE_HOME_BUTTON)
    #define LULZBOT_AFTER_Z_HOME_ACTION \
        if(home_all || homeZ) { \
          LULZBOT_G92_Z(LULZBOT_AFTER_Z_HOME_Z_ORIGIN); \
          LULZBOT_G0_Z(LULZBOT_AFTER_Z_HOME_Z_RAISE); \
        }
#else
    #define LULZBOT_AFTER_Z_HOME_ACTION
#endif

/* Historically, the Lulzbot firmware would save the Z-Offset into the EEPROM
 * each time it is changed. The latest Marlin made this more difficult since they
 * added a CRC to the EEPROM. We work around this by bracketing the EEPROM_READ
 * and EEPROM_WRITE routines such that the CRC ignores the Z-Offset value. That
 * code also captures the eeprom_index so we can write only that value later.
 */

/* The following goes in "configuration_store.cpp", before and after
 * "EEPROM_WRITE(zprobe_zoffset)" and "EEPROM_READ(zprobe_zoffset)"
 */
#if defined(LULZBOT_USE_AUTOLEVELING)
    #define LULZBOT_EEPROM_BEFORE_ZOFFSET \
        const uint16_t eeprom_saved_crc = working_crc; \
        eeprom_zoffset_index = eeprom_index;

    #define LULZBOT_EEPROM_AFTER_ZOFFSET \
        working_crc = eeprom_saved_crc;

    /* The following goes in "configuration_store.h" */
    #define LULZBOT_SAVE_ZOFFSET_TO_EEPROM_DECL \
        static int eeprom_zoffset_index; \
        static void store_zoffset();

    /* The following goes in "configuration_store.cpp" */
    #define LULZBOT_SAVE_ZOFFSET_TO_EEPROM_IMPL \
        int MarlinSettings::eeprom_zoffset_index = -1; \
        void MarlinSettings::store_zoffset() { \
            if(eeprom_zoffset_index > 0) { \
                uint16_t working_crc; \
                int eeprom_index = eeprom_zoffset_index; \
                EEPROM_WRITE(zprobe_zoffset); \
                SERIAL_ECHO_START(); \
                SERIAL_ECHOPAIR("Updating zoffset in EEPROM: ", zprobe_zoffset); \
                SERIAL_ECHOPAIR("; EEPROM Index: ", eeprom_zoffset_index); \
                SERIAL_ECHOLNPGM(""); \
            } \
        }

    /* The following goes in "ultralcd.cpp" in "lcd_babystep_zoffset" */
    #define LULZBOT_SAVE_ZOFFSET_TO_EEPROM settings.store_zoffset();
#else
    #define LULZBOT_EEPROM_BEFORE_ZOFFSET
    #define LULZBOT_EEPROM_AFTER_ZOFFSET
    #define LULZBOT_SAVE_ZOFFSET_TO_EEPROM_DECL
    #define LULZBOT_SAVE_ZOFFSET_TO_EEPROM_IMPL
    #define LULZBOT_SAVE_ZOFFSET_TO_EEPROM
#endif

#endif /* CONDITIONALS_LULZBOT */
