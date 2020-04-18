/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/04/12
 * Version: 1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __PRIMARIO_H__
#define __PRIMARIO_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include <sapi.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

// Possible states for the MEFs
typedef enum{ NORMAL , ALARM, PRESTATE, FAIL} dprim_state_t;

// Structure with the different data types to generate an independent Monitor
typedef struct{
	tick_t timeout;
	delay_t delay;
	dprim_state_t state;
}dprimario_t;


/*=====[Prototypes (declarations) of public functions]=======================*/
/** It sets initial conditions for the entire program, it establish the default values
 *  of timeout and #cycles for Alarm and Fail UART code verification.

	@param pPrimario element of type *dprimario_t* with the Monitor data types needed
	@note It must be called before primControl.
	@see primControl.

**/
bool_t primInit(dprimario_t * pPrimario);

/** It identifies the state we are currently and generates the corresponding
 *  outputs verifying if for the current state exists any possible transition.

	@param pPrimario element of type *dprimario_t* with the Monitor data types needed
	@note If the current state is not define it returns FALSE.
	@see primInit.

**/
bool_t primControl(dprimario_t * pPrimario);

/** It updates the state of all the existent MEFs and also checks the TESTMODE.

	@note Must be called after primInit.
	@see primInit.

**/
void primUpdates();


/** It sends trough the UART PORT assigned, the current state of the Monitor system.

	@param pPrimario element of type *dprimario_t* with the Monitor data types needed
	@note It does not affect the logic of the MEFs.
**/
void primState(dprimario_t * prim);


/** It sends trough the UART PORT assigned, the current test mode selectec of the Monitor system.

	@param pPrimario element of type *dprimario_t* with the Monitor data types needed
	@note It does not affect the logic of the MEFs.
**/
void primTmode(dprimario_t * prim);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __PRIMARIO_H__ */
