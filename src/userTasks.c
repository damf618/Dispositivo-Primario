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
#include "antirebote.h"

/*=====[Definition macros of private constants]==============================*/
#define TEST_BUTTON TEC4

#define TEST_PRINCIPAL_STATE 0
#define TEST_UART_FLAG 1

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/
dprimario_t prim;
antirebote_t boton4;
bool_t TEST_MODE = TEST_PRINCIPAL_STATE ;
/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

// Task initialization implementation
void TaskInit( void* taskParmPtr )
{
	primInit(&prim);
	fsmInit(&boton4,TEST_BUTTON);
}

// Task1 update implementation
void AllUpdates( void* taskParmPtr )
{
	primUpdates(&prim);
	fsmUpdate(&boton4);
}

// Task2 MEF's Logic implementation
void Primario( void* taskParmPtr )
{
   primControl(&prim);
}

// Task3 It sends through UART Port the Current State of The System.
void CurrentState( void* taskParmPtr )
{
	switch( prim.state ) {

		case PRENORMAL:
			UARTReport( &prim.uart1,"\r\n CURRENT STATE: PRE-NORMAL \r\n");
			break;
		case PREALARM:
			UARTReport( &prim.uart1,"\r\n CURRENT STATE: PRE-ALARM \r\n");
			break;
		case PREFAIL:
			UARTReport( &prim.uart1,"\r\n CURRENT STATE: PRE-FAIL \r\n");
			break;
		case NORMAL:
			UARTReport( &prim.uart1,"\r\n CURRENT STATE: NORMAL \r\n");
			break;
		case FAIL:
			UARTReport( &prim.uart1,"\r\n CURRENT STATE: FAIL\r\n");
			break;
		case ALARM:
			UARTReport( &prim.uart1,"\r\n CURRENT STATE: ALARM\r\n");
			break;
		default:
			UARTReport( &prim.uart1,"\r\n CURRENT STATE: PLEASE RESTART\r\n");
	}
}

// Task4 It sends through UART Port the Current Test Mode of The System.
void CurrentTmode( void* taskParmPtr )
{
	switch( TEST_MODE ) {
		case TEST_PRINCIPAL_STATE:
			UARTReport( &prim.uart1,"\r\n TEST-MODE: PRINCIPAL STATES \r\n");
			break;
		case TEST_UART_FLAG:
			UARTReport( &prim.uart1,"\r\n TEST-MODE: UART FLAGS \r\n");
			break;
	}
}

// Task5 Just to check if the Button4 was pressed, if it was pressed, it modifies
// the test mode, Testmode1: Turns on Blue LED if an UART code was received
// Testmode0: Turns on BLue LEDif we are on a state different from PRESTATE
void Test( void* taskParmPtr )
{
	if(get_State(&boton4)){			// More info in ButtonCheck
		if(TEST_MODE==TEST_PRINCIPAL_STATE)
			TEST_MODE=TEST_UART_FLAG;
		else if(TEST_MODE==TEST_UART_FLAG)
			TEST_MODE=TEST_PRINCIPAL_STATE;
	}

	if (TEST_MODE==TEST_UART_FLAG){
		if(prim.UARTFLAG==1)		// If there is any transition made for the
			turnOn(TEST_LIGHT);		// UART console, then the Blue Led turns on.
		else
			turnOff(TEST_LIGHT);
	}
	else if(TEST_MODE==TEST_PRINCIPAL_STATE){
		if((prim.state==PREALARM)||
			(prim.state==PREFAIL)||
			(prim.state==PRENORMAL))	// If we are in PRE-STATE we turn off the
			turnOff(TEST_LIGHT);	// Blue Led.
		else
			turnOn(TEST_LIGHT);
	}
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

