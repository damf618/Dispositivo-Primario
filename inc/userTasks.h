/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/04/16
 * Version: 1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

/** It calls the method to initialize the environment needed for the Monitor
 * System's MEF, it also includes the initialization of the test button.

	@see Primario
	@see AllUpdates
**/
void TaskInit( void* taskParmPtr );

/** It calls the method that contains the MEFs designed for the Monitor system,
 * it still depends of the periodic call of the update method, to work properly.

	@note It must be called after the initialization of both elements.
	@see TaskInit
	@see Primario
**/
void Primario( void* taskParmPtr );

/** It calls the update function of all the MEFs involved, also updates the test
 * button state.

	@note It must be called after the initialization of both elements.
	@see TaskInit
**/
void AllUpdates( void* taskParmPtr );

/** It sends trough the UART PORT assigned, the current state of the Monitor system.

	@note It does not affect the logic of the MEFs.
**/
void CurrentState( void* taskParmPtr );

/** It sends trough the UART PORT assigned, the current test mode of the system
 * selected for the Monitor system. To change the test mode you need to press
 * the specified button in the task Test.

	@note It does not affect the logic of the MEFs.
	@see Test
**/
void CurrentTmode( void* taskParmPtr );

/** It checks the last state of the test button and executes the corresponding
 * action based on the Test mode active. The test mode 1 turns on the led if we are
 * in a state different from PRESTATE. Test mode 2 turns on the led if any UART Code
 * was received (UARTFLAG).

	@note It does not affect the logic of the MEFs. It does not initialize the
	test button.
	@see TaskInit
**/
void Test( void* taskParmPtr );

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __USER_TASKS_H__ */
