/*
 * Primario_LEDS.h
 *
 *  Created on: Apr 12, 2020
 *      Author: daniel
 */

#ifndef PROGRAMAS_DAMF_PRIMARIO_INC_PRIMARIO_LEDS_H_
#define PROGRAMAS_DAMF_PRIMARIO_INC_PRIMARIO_LEDS_H_

#include <sapi.h>

#define YELLOW_LIGHT LED1			// GPIO for the Yellow LED
#define RED_LIGHT LED2				// GPIO for the Red LED
#define GREEN_LIGHT LED3			// GPIO for the Green LED

#define TEST_LIGHT LEDB				// GPIO for the Test LED

/** Is based on the sapi library, made by Eric Pernia. it receives the GPIO number
 * and sets it  as high.

	@param lamp element of type *gpioMap_t* it refers to the GPIO to work on.

**/
void turnOn(gpioMap_t lamp);

/** Is based on the sapi library, made by Eric Pernia. it receives the GPIO number
 * and sets it as low.

	@param lamp element of type *gpioMap_t* it refers to the GPIO to work on.

**/
void turnOff(gpioMap_t lamp);

#endif /* PROGRAMAS_DAMF_PRIMARIO_INC_PRIMARIO_LEDS_H_ */
