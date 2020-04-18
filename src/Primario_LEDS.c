/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/04/12
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Primario_LEDS.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

// Sets the GPIO indicated as lamp, HIGH.
void turnOn(gpioMap_t lamp){
	gpioWrite(lamp , ON );
}

// Sets the GPIO indicated as lamp, LOW.
void turnOff(gpioMap_t lamp){
	gpioWrite(lamp, OFF );
}
