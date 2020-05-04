/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/04/12
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Primario_LEDS.h"
#include <wiringPi.h>
#include <cstdbool>

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
//Configures the corresponding modes for each GPIO
void gpioSet(void){
	wiringPiSetup () ;
	pinMode (RED_LIGHT, OUTPUT) ;
	pinMode (YELLOW_LIGHT, OUTPUT) ;
	pinMode (GREEN_LIGHT, OUTPUT) ;
	
	pinMode (ALARM_BUTTON, INPUT) ;
    pullUpDnControl (ALARM_BUTTON, PUD_UP) ;
    pinMode (FAIL_BUTTON, INPUT) ;
    pullUpDnControl (FAIL_BUTTON, PUD_UP) ;
    pinMode (NORMAL_BUTTON, INPUT) ;
    pullUpDnControl (NORMAL_BUTTON, PUD_UP) ;
}

// Sets the GPIO indicated as lamp, HIGH.
void turnOn(char lamp){
	digitalWrite(lamp , HIGH );
}

// Sets the GPIO indicated as lamp, LOW.
void turnOff(char lamp){
	digitalWrite(lamp, LOW );
}

// Reads the GPIO digital status.
bool gpioRead(int lamp){
	return digitalRead (lamp);
}
