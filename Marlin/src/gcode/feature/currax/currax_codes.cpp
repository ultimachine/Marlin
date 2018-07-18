//Additional Custom Mcodes for Currax

#include "../../gcode.h"
#include "../../../module/temperature.h"

#if ENABLED(HAVE_CURRAX)

void currax_init_endstops() {
  pinMode(ENDSTOP0_PIN, INPUT_PULLUP);
  pinMode(ENDSTOP1_PIN, INPUT_PULLUP);
  pinMode(ENDSTOP2_PIN, INPUT_PULLUP);
  pinMode(ENDSTOP3_PIN, INPUT_PULLUP);
  pinMode(RESIN_SW_PIN, INPUT_PULLUP);
}

/**
 * M480: Read temperature adc data
 */
void GcodeSuite::M480() {

  /*
    # CURRAX_COOLANT_TEMP_PIN
    # CURRAX_LCD_TEMP_PIN
    # CURRAX_RESIN_TEMP_PIN
    # CURRAX_PUMP_TEMP_PIN
    # CURRAX_CASE_TEMP_PIN
  */
  SERIAL_ECHOPGM("coolant_temp_adc: ");
  SERIAL_ECHOLN(analogRead(CURRAX_COOLANT_TEMP_PIN));

  SERIAL_ECHOPGM("lcd_temp_adc: ");
  SERIAL_ECHOLN(analogRead(CURRAX_LCD_TEMP_PIN));

  SERIAL_ECHOPGM("resin_temp_adc: ");
  SERIAL_ECHOLN(analogRead(CURRAX_RESIN_TEMP_PIN));

  SERIAL_ECHOPGM("pump_temp_adc: ");
  SERIAL_ECHOLN(analogRead(CURRAX_PUMP_TEMP_PIN));

  SERIAL_ECHOPGM("case_temp_adc: ");
  SERIAL_ECHOLN(analogRead(CURRAX_CASE_TEMP_PIN));
}

/**
 * M480: Read currax endstop status
 */
void GcodeSuite::M481() {

  /*
    # ENDSTOP0_PIN
    # ENDSTOP1_PIN
    # ENDSTOP2_PIN
    # ENDSTOP3_PIN
    # RESIN_SW_PIN
  */

  SERIAL_ECHOPGM("endstop0: ");
  SERIAL_ECHOLN(digitalRead(ENDSTOP0_PIN));

  SERIAL_ECHOPGM("endstop1: ");
  SERIAL_ECHOLN(digitalRead(ENDSTOP1_PIN));

  SERIAL_ECHOPGM("endstop2: ");
  SERIAL_ECHOLN(digitalRead(ENDSTOP2_PIN));

  SERIAL_ECHOPGM("endstop3: ");
  SERIAL_ECHOLN(digitalRead(ENDSTOP3_PIN));

  SERIAL_ECHOPGM("resin_sw: ");
  SERIAL_ECHOLN(digitalRead(RESIN_SW_PIN));

}

/**
 * M482: Read temperature data in Celsius
 */
void GcodeSuite::M482() {

  /*
    # CURRAX_COOLANT_TEMP_PIN
    # CURRAX_LCD_TEMP_PIN
    # CURRAX_RESIN_TEMP_PIN
    # CURRAX_PUMP_TEMP_PIN
    # CURRAX_CASE_TEMP_PIN
  */
  SERIAL_ECHOPGM("coolant_temp: ");
  SERIAL_ECHOLN( thermalManager.analog2temp(OVERSAMPLENR * analogRead(CURRAX_COOLANT_TEMP_PIN),0) );

  SERIAL_ECHOPGM("lcd_temp: ");
  SERIAL_ECHOLN( thermalManager.analog2temp(OVERSAMPLENR * analogRead(CURRAX_LCD_TEMP_PIN),0) );

  SERIAL_ECHOPGM("resin_temp: ");
  SERIAL_ECHOLN( thermalManager.analog2temp(OVERSAMPLENR * analogRead(CURRAX_RESIN_TEMP_PIN),0) );

  SERIAL_ECHOPGM("pump_temp: ");
  SERIAL_ECHOLN( thermalManager.analog2temp(OVERSAMPLENR * analogRead(CURRAX_PUMP_TEMP_PIN),0) );

  SERIAL_ECHOPGM("case_temp: ");
  SERIAL_ECHOLN( thermalManager.analog2temp(OVERSAMPLENR * analogRead(CURRAX_CASE_TEMP_PIN),0) );
}

void GcodeSuite::M483() {
  constant_moving_stepper = parser.boolval('S',false);
}

#endif //HAVE_CURRAX