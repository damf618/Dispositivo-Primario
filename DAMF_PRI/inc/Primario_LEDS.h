/*
 * Primario_LEDS.h
 *
 *  Created on: Apr 12, 2020
 *      Author: daniel
 */

#ifndef PRIMARIO_LEDS_H_
#define PRIMARIO_LEDS_H_

#include <cstdbool>

#ifdef __cplusplus
extern "C" {
#endif


#define RED_LIGHT 7			// GPIO for the Yellow LED
#define YELLOW_LIGHT 0				// GPIO for the Red LED
#define GREEN_LIGHT 3			// GPIO for the Green LED

#define ALARM_BUTTON 1
#define FAIL_BUTTON 4
#define NORMAL_BUTTON 5

#define TEST_LIGHT 6				// GPIO for the Test LED

/** Configures the GPIO based on wiringPi library.

**/
void gpioSet(void);

/** Is based on the sapi library, made by Eric Pernia. it receives the GPIO number
 * and sets it  as high.

	@param lamp element of type *char* it refers to the GPIO to work on.

**/
void turnOn(char lamp);

/** Is based on the sapi library, made by Eric Pernia. it receives the GPIO number
 * and sets it as low.

	@param lamp element of type *char* it refers to the GPIO to work on.

**/
void turnOff(char lamp);

/** Is based on the sapi library, made by Eric Pernia. it readss the GPIO number
 * returns the digital comparison.

	@param lamp element of type *char* it refers to the GPIO to work on.

**/
bool gpioRead(int lamp);

#ifdef __cplusplus
}
#endif

#endif /* PROGRAMAS_DAMF_PRIMARIO_INC_PRIMARIO_LEDS_H_ */
