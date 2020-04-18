/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/04/16
 * Version: 1
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"

/*=====[Inclusions of private function dependencies]=========================*/

#include "primario4.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/
dprimario_t prim;

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/


// Task initialization implementation
void TaskInit( void* taskParmPtr )
{
	boardInit();
	primInit(&prim);
}

// Task2 update implementation
void Primario( void* taskParmPtr )
{
   primControl(&prim);
}

// Task1 update implementation
void AllUpdates( void* taskParmPtr )
{
	primUpdates();
}
// Task3 notify the current state to the user
void CurrentState( void* taskParmPtr )
{
	primState(&prim);
}

// Task4 notify the test mode to the user
void CurrentTmode( void* taskParmPtr )
{
	primTmode(&prim);
}


/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

