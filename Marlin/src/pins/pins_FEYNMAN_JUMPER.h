/****************************************************************************************
* FeynmanRambo pin assignment (pins_FEYNMANRAMBO.h)
*
****************************************************************************************/
#if MOTHERBOARD == BOARD_FEYNMAN_JUMPER
#ifndef __SAMG55J19__
 #error Oops!  Make sure you have 'Feynman' selected from the 'Tools -> Boards' menu.
#endif

#define BOARD_NAME         "Einsy Rambo"

//
// TMC2130 Configuration_adv defaults for EinsyRambo
//
#if DISABLED(HAVE_TMC2130)
  #error "You must enable TMC2130 support in Configuration_adv.h for EinsyRambo."
#elif DISABLED(X_IS_TMC2130) || DISABLED(Y_IS_TMC2130) || DISABLED(Z_IS_TMC2130) || DISABLED(E0_IS_TMC2130)
  #error "You must enable ([XYZ]|E0)_IS_TMC2130 in Configuration_adv.h for EinsyRambo."
#endif

// MUX Pins
#define MOTORS_EN_PIN       42 //PB10 EN_DRV
#define TMC_MUX_DIAG_PIN    35 //PB3 TMC_DIAG

//
// Limit Switches
//
// Only use Diag Pins when SENSORLESS_HOMING is enabled for the TMC2130 drivers.
// Otherwise use a physical endstop based configuration.
//
// SERVO0_PIN and Z_MIN_PIN configuration for BLTOUCH sensor when combined with SENSORLESS_HOMING.
//

#if DISABLED(SENSORLESS_HOMING)

  #define X_STOP_PIN       2 //PA2 X_MIN
  #define Y_STOP_PIN       41 //PB9 Y_MIN
  #define Z_STOP_PIN       20 //PA20 Z_MIN

#else

  #define X_STOP_PIN       TMC_MUX_DIAG_PIN
  #define Y_STOP_PIN       TMC_MUX_DIAG_PIN

  #if ENABLED(BLTOUCH)
    #define Z_STOP_PIN     41 //PB9 Y_MIN
    #define SERVO0_PIN     20 //PA20 Z_MIN
  #else
    #define Z_STOP_PIN     20 //PA20 Z_MIN
  #endif

#endif

#define X_STEP_PIN          44 //PB12 X-STEP
#define X_DIR_PIN           31 //PA31 X-DIR
#define X_ENABLE_PIN        -1
#define X_CS_PIN            46 //PB14 X-CS_DRV

#define Y_STEP_PIN          15 //PA15 Y-STEP
#define Y_DIR_PIN           30 //PA30 Y-DIR
#define Y_ENABLE_PIN        -1
#define Y_CS_PIN            47 //PB15 Y-CS_DRV

#define Z_STEP_PIN          19 //PA19 Z-STEP
#define Z_DIR_PIN           29 //PA29 Z-DIR
#define Z_ENABLE_PIN        -1
#define Z_CS_PIN            43 //PB11 Z-CS_DRV

#define E0_STEP_PIN         27 //PA27 E0-STEP
#define E0_DIR_PIN          28 //PA28 E0-DIR
#define E0_ENABLE_PIN       -1
#define E0_CS_PIN           45 //PB13 E0-CS_DRV

#define E1_STEP_PIN        -1
#define E1_DIR_PIN         -1
#define E1_ENABLE_PIN      -1

#define E2_STEP_PIN        -1
#define E2_DIR_PIN         -1
#define E2_ENABLE_PIN      -1

#define Y2_STEP_PIN        -1
#define Y2_DIR_PIN         -1
#define Y2_ENABLE_PIN      -1

#define Z2_STEP_PIN        -1
#define Z2_DIR_PIN         -1
#define Z2_ENABLE_PIN      -1
#define Z2_CS_PIN          -1

#define SDPOWER            -1


//#define SDSS             -1

#define LED_PIN            -1
#define PS_ON_PIN          -1
//#define Z_PROBE_PIN      -1
//#define CONTROLLERFAN_PIN  -1 //Marlin1
#define CONTROLLER_FAN_PIN -1 //Marlin2.0

#define FAN_PIN             1 //15 //PA15 S_FAN_12V //"You cannot set E0_AUTO_FAN_PIN equal to FAN_PIN."
#define FAN2_PIN            16

#define HEATER_0_PIN        23 //PA23 HEAT-0
#define HEATER_1_PIN        -1
#define HEATER_2_PIN        -1
#define HEATER_BED_PIN       0 //PA0 BED-HEAT



#define TEMP_0_PIN          17
#define TEMP_1_PIN          -1
#define TEMP_BED_PIN        18
#define TEMP_2_PIN          -1

#ifdef Z_PROBE_SLED
  #define SLED_PIN         -1
#endif

#ifdef ULTRA_LCD
  #define KILL_PIN           -1 //Button is connected directly to NRST Hardware Reset Pin on SAM3X
  #ifdef NEWPANEL
    #define BEEPER          -1 //arduino pin which triggers an piezzo beeper
    #define LCD_PINS_RS     -1
    #define LCD_PINS_ENABLE -1
    #define LCD_PINS_D4     -1
    #define LCD_PINS_D5     -1
    #define LCD_PINS_D6     -1
    #define LCD_PINS_D7     -1
    
    #define SDCARDDETECT    -1
    #define SDSS            -1
    
    //buttons are directly attached using AUX-2
    #define BTN_EN1         -1
    #define BTN_EN2         -1
    #define BTN_ENC         -1

    #define BLEN_C 2
    #define BLEN_B 1
    #define BLEN_A 0

    //encoder rotation values
    #define encrot0 0
    #define encrot1 2
    #define encrot2 3
    #define encrot3 1
  #endif  //NEWPANEL
#else
  #define SDSS            87 //only defined to prevent compile errors
#endif //ULTRA_LCD

//#ifndef SDSUPPORT
  // these pins are defined in the SD library if building with SD support
  //#define SCK_PIN          76
  //#define MISO_PIN         74
  //#define MOSI_PIN         75
//#endif

#endif /* TIGERSHARK */

