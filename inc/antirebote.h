/*
 * antirebote.h
 *
 *  Created on: Apr 1, 2020
 *      Author: daniel
 */

#ifndef PROGRAMAS_DAMF_SEMAFORO_INC_ANTIREBOTE1_H_
#define PROGRAMAS_DAMF_SEMAFORO_INC_ANTIREBOTE1_H_




#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*Implementation of the Debounce pattern as an MEF*/
/*	It does not have a PRESSED flag yet.
 *
 * */

//States of the Debounce MEF
typedef enum{
   INIT,
   UP,
   FALLING,
   DOWN,
   RISING
} fsmState_t;

typedef struct{
	bool_t flag;
	delay_t delay;
	gpioMap_t button;
	fsmState_t fsmState;
} antirebote_t;


/** It sets initial conditions for the MEF and associates the GPIO to apply the
 *  debounce pattern on.

	@param pbutton element of type *antirebote_t* a structure to make an independent Button
	@param boton GPIO to apply the debounce pattern on.
	@note It must be called before fsmUpdate.
**/
void fsmInit( antirebote_t * pbutton, gpioMap_t boton );

/** It updates the outputs and states for the MEF, verifies the transition
 *  conditions on every call.

	@param pbutton element of type *antirebote_t* a structure to make an independent Button
	@note It must be called after fsmInit.
**/
void fsmUpdate( antirebote_t * pbutton );

/** It returns the state of released button event.

	@param pbutton element of type *antirebote_t* a structure to make an independent Button
	@note It returns 1 if the button was released, else itreturns 0.
**/
bool_t get_State( antirebote_t * pbutton );

#endif /* PROGRAMAS_DAMF_SEMAFORO_INC_ANTIREBOTE1_H_ */
