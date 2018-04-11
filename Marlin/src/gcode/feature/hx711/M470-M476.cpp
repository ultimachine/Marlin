//FeynmanLight HX711 Load sensor interface Mcodes

#include "../../../inc/MarlinConfig.h"

#if ENABLED(HAVE_HX711)

#include "HX711.h"

#include "../../gcode.h"

HX711 scale;

void hx711_init() { //To be called somewhere in Main.cpp: setup() -TODO
	SERIAL_ECHOLNPGM("hx711 init.");

  #ifdef __SAMG55J19__
    matrix_set_system_io( (1<<7) ); // FeynmanLight - (SYSIO7/PB7/SWCLK) Allow GPIO access to PB7 in CCFG_SYSIO register
  #endif

	scale.begin(HX711_DOUT_PIN, HX711_SWCLK_PIN);

	scale.set_scale();
	scale.tare();  //Reset the scale to 0

  #ifdef HX711_CALIBRATION_FACTOR
	SERIAL_ECHOPGM("hx711_calibration_factor: ");
	SERIAL_ECHOLN(HX711_CALIBRATION_FACTOR);
	scale.set_scale(HX711_CALIBRATION_FACTOR);
  #endif
}

void hx711_manage() { //Periodically print out readings -TODO add to main loop
	static uint32_t next_readtime = 0;
	if( millis() >=  next_readtime) {
		long read_val = scale.read();
		SERIAL_ECHOPGM("scale.read: ");
		SERIAL_ECHOLN(read_val);
		next_readtime = millis() + HX711_CHECKINTERVAL_MILLIS;
	}
}

void GcodeSuite::M470() { //M470 Init HX711
	hx711_init();
}

void GcodeSuite::M471() { //M471 Read
	long read_val = scale.read();
	SERIAL_ECHOPGM("scale.read: ");
	SERIAL_ECHOLN(read_val);
}

void GcodeSuite::M472() { //M472 S<times> Read average
	int times = parser.intval('S',10); //Default 10 times
	long read_avg = scale.read_average(times);
	SERIAL_ECHOPGM("read_average: ");
	SERIAL_ECHOLN(read_avg);
}

void GcodeSuite::M473() { //M473 Tare
	scale.tare();
	SERIAL_ECHOLNPGM("scale.tare done.");
}

void GcodeSuite::M474() { //M474 S<value> Set scale
	int setval = parser.intval('S',1.f);
	scale.set_scale(setval);
	SERIAL_ECHOPGM("set_scale: ");
	SERIAL_ECHOLN(setval);
}

void GcodeSuite::M475() { //M475 Get scale
	float scale_val = scale.get_scale();
	SERIAL_ECHOPGM("get_scale: ");
	SERIAL_ECHOLN(scale_val);
}

void GcodeSuite::M476() { //M476 S<times> Get units
	int times = parser.intval('S',1); //Default 1 times
	float units_val = scale.get_units(times);
	SERIAL_ECHOPGM("get_units: ");
	SERIAL_ECHOLN(units_val);
}

#endif //HAVE_PCA9685