/**
 * Ultimachine Archim-Rambo 2.0
 */
#if !defined(__SAM3X8E__) || !defined(ARDUINO_SAM_ARCHIM)
  #error "Oops!  Make sure you have 'Archim' selected from the 'Tools -> Boards' menu."
#endif
 
#define BOARD_NAME         "Archim v2.0"
 
//
// Limit Switches
//
#define X_MIN_PIN          14 //PD4 MIN ES1
#define X_MAX_PIN          32 //PD10 MAX ES1
#define Y_MIN_PIN          29 //PD6 MIN ES2
#define Y_MAX_PIN          15 //PD5 MAX ES2
#define Z_MIN_PIN          31 //PA7 MIN ES3
#define Z_MAX_PIN          30 //PD9 MAX ES3

//
// Enable use of TMC2130
//
#define HAVE_TMC2130
#define X_IS_TMC2130
#define Y_IS_TMC2130
#define Z_IS_TMC2130
#define E0_IS_TMC2130
#define R_SENSE           0.22
#ifndef E0_CURRENT
  #define E0_CURRENT        1000
#endif
#ifndef E0_MICROSTEPS
  #define E0_MICROSTEPS       32
#endif

//#define TMC2130_USES_SW_SPI
//#define TMC_SWSPI_MISO_PIN 26 //PD1 MISO
//#define TMC_SWSPI_SCK_PIN  27 //PD2 SCK
//#define TMC_SWSPI_MOSI_PIN 28 //PD3 MOSI

//
// Stepper Chip Select Pins
//
#define X_CS_PIN           39 //PC7 X_nCS
#define Y_CS_PIN           50 //PC13 Y_nCS
#define Z_CS_PIN           45 //PC18 Z_nCS
#define E0_CS_PIN         104 //PC20 E1_nCS -AddOns *
#define E1_CS_PIN          19 //PA10 E2_nCS

//
// Stepper Diag Pins
//
#define X_DIAG_PIN         59 //PA4 X_DIAG
#define Y_DIAG_PIN         48 //PC15 Y_DIAG
#define Z_DIAG_PIN         36 //PC4 Z_DIAG
#define E0_DIAG_PIN        78 //PB23 E1_DIAG
#define E1_DIAG_PIN        25 //PD0 E2_DIAG

//
// Steppers
//
#define X_STEP_PIN         38 //PC6 X-STEP *
#define X_DIR_PIN          37 //PC5 X-DIR *
#define X_ENABLE_PIN       41 //PC9 X-EN

#define Y_STEP_PIN         51 //PC12 Y-STEP *
#define Y_DIR_PIN          92 //PC11 Y-DIR -AddOns *
#define Y_ENABLE_PIN       49 //PC14 Y-EN *

#define Z_STEP_PIN         46 //PC17 Z-STEP *
#define Z_DIR_PIN          47 //PC16 Z-DIR *
#define Z_ENABLE_PIN       44 //PC19 Z-EN *

#define E0_STEP_PIN       107 //PB10 E1-STEP -AddOns *
#define E0_DIR_PIN         96 //PC10 E1-DIR -AddOns *
#define E0_ENABLE_PIN     105 //PB22 E1-EN -AddOns *

#define E1_STEP_PIN        22 //PB26 E2_STEP *
#define E1_DIR_PIN         97 //PB24 E2_DIR -AddOns *
#define E1_ENABLE_PIN      18 //PA11 E2-EN

#define E2_STEP_PIN        -1
#define E2_DIR_PIN         -1
#define E2_ENABLE_PIN      -1

//
// Stepper Voltage Reference Pins
//
#define MOTOR_CURRENT_PWM_X_PIN   58 //PA6   X-REF TIOB2
#define MOTOR_CURRENT_PWM_Y_PIN   12 //PD8   Y-REF TIOB8
#define MOTOR_CURRENT_PWM_Z_PIN   10 //PC29  Z-REF TIOB7
#define MOTOR_CURRENT_PWM_E0_PIN   3 //PC28 E1-REF TIOA7
#define MOTOR_CURRENT_PWM_E1_PIN  11 //PD7  E2-REF TIOA8

#define MOTOR_CURRENT_PWM_RANGE 2750 // 3.3 volts * (100 kOhm / (100 kOhm + 20 kOhm) ) = 2.75 max voltage out
#define DEFAULT_PWM_MOTOR_CURRENT  {1000, 1000, 1000, 1000, 1000} //X Y Z E0 E1, 1000 = 1000mAh

//
// Temperature Sensors
//
#define TEMP_0_PIN         10 // D10 PB19 THERM AN1
#define TEMP_1_PIN          9 // D9 PB18 THERM AN2
#define TEMP_2_PIN          8 // D8 PB17 THERM AN4
#define TEMP_BED_PIN       11 // D11 PB20 THERM AN3

//
// Heaters / Fans
//
#define HEATER_0_PIN         6 // D6 PC24 FET_PWM3
#define HEATER_1_PIN         7 // D7 PC23 FET_PWM4
#define HEATER_2_PIN         8 // D8 PC22 FET_PWM5
#define HEATER_BED_PIN       9 // D9 PC21 BED_PWM

#define FAN_PIN              4 // D4 PC26 FET_PWM1
#define FAN1_PIN             5 // D5 PC25 FET_PWM2

//
// Misc. Functions
//
#define SDSS                4
#define LED_PIN            13
//#define SPI_EEPROM

//
// LCD / Controller
//
#if ENABLED(ULTRA_LCD)
  #if ENABLED(NEWPANEL)
    #define LCD_PINS_RS     17 //D17 PA12_RXD1
    #define LCD_PINS_ENABLE 24 //D23 PA14_RTS1
    #define LCD_PINS_D4     69 //D69 PA0_CANTX0
    #define LCD_PINS_D5     54 //D54 PA16_SCK1
    #define LCD_PINS_D6     68 //D68 PA1_CANRX0
    #define LCD_PINS_D7     34 //D34 PC2_PWML0
    
    #define BEEPER          23 //D24 PA15_CTS1

    #define BTN_EN1         60 //D60 PA3_TIOB1
    #define BTN_EN2         13 //D13 PB27_TIOB0
    #define BTN_ENC         16 //D16 PA13_TXD1 // the click
	
    #define SDCARDDETECT     2 //D2  PB25_TIOA0
    #define SDSS            87 //D87 PA29 CS
  #endif
#endif // ULTRA_LCD
