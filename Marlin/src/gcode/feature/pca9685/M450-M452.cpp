//FeynmanLight LED Driver Mcodes

#include "../../../inc/MarlinConfig.h"

#if ENABLED(HAVE_PCA9685)

#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"

#include "../../gcode.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_I2C_ADDR); //7bit address

void pca9685_init() {
	//LED driver disabled initially
	pinMode(PCA9685_ENABLE_PIN,OUTPUT);
	digitalWrite(PCA9685_ENABLE_PIN,HIGH);

	SERIAL_ECHOLNPGM("LED driver init");
	pwm.begin();
	pwm.setPWMFreq(1526);  // This is the maximum PWM frequency
	  for(int i=1;i<=11;i++) //Cycle through channels 1-11
		pwm.setPin(i, 0, 0);
}

void GcodeSuite::M450() { //M450 Initialize LED Driver with zero duty cycle on all the used channels.
	pca9685_init();
}
void GcodeSuite::M451() { //M451 S<frequency> Set LED Driver PWM Frequency
  if(parser.seen('S')) {
	int freq = parser.value_int();
	SERIAL_ECHOPGM("setPWMFreq: ");
	SERIAL_ECHOLN(freq);
	pwm.setPWMFreq(freq);
  }
}

void GcodeSuite::M452() { //M452 P<channel> S<dutycycle>  // Set LED Driver duty cycle. If channel not specified then it will update all channels.
	int dutycycle = parser.intval('S',0);
	SERIAL_ECHOPGM("dutycycle: ");
	SERIAL_ECHOLN(dutycycle);

	if(parser.seen('P')) {
	  int channel = parser.value_byte();
	  pwm.setPin(channel, dutycycle, 0);
	} else {
	  for(int i=1;i<=11;i++) //Cycle through channels 1-11
		pwm.setPin(i, dutycycle, 0);
	}
}

void GcodeSuite::M453() { //M453 LED Driver On (Controls LED Enable Pin)
	SERIAL_ECHOLNPGM("LED driver enabled.");
	pinMode(PCA9685_ENABLE_PIN,OUTPUT);
	digitalWrite(PCA9685_ENABLE_PIN,LOW);
}

void GcodeSuite::M454() { //M454 LED Driver Off (Controls LED Enable Pin)
	SERIAL_ECHOLNPGM("LED driver disabled.");
	pinMode(PCA9685_ENABLE_PIN,OUTPUT);
	digitalWrite(PCA9685_ENABLE_PIN,HIGH);
}

#endif //HAVE_PCA9685