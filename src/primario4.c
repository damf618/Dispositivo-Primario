/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/04/12
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "primario4.h"
#include "antirebote.h"
#include "Primario_LEDS.h"
#include "Primario_UART.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/
#define INITIAL_DEFAULT_STATE NORMAL

#define ALARM_BUTTON TEC1
#define FAIL_BUTTON TEC2
#define NORMAL_BUTTON TEC3
#define TEST_BUTTON TEC4

#define TEST_PRINCIPAL_STATE 0
#define TEST_UART_FLAG 1

#define DEF_TIMEOUT 3500			   //Timeout limit between transitions

char count;							   //Counter for the number of cycles for
									   //UART Alarm and Fail code monitoring.

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

antirebote_t boton1,boton2,boton3,boton4;//Buttons with  debounce pattern
uart_prim_t uart1;                     //Uart interface
bool_t UARTFLAG=1;                     //Flag for UART interaction 1 ON, 0 OFF
bool_t TEST_MODE= TEST_PRINCIPAL_STATE;	   //Flag for defining TEST mode

/*=====[Functions, program entry point after power on or reset]==========*/

// Just to check if the Button4 was pressed, if it was pressed, it modifies
// the test mode
static void TEST(){
	if(get_State(&boton4)){			// More info in ButtonCheck
		if(TEST_MODE==TEST_PRINCIPAL_STATE)
			TEST_MODE=TEST_UART_FLAG;
		else if(TEST_MODE==TEST_UART_FLAG)
			TEST_MODE=TEST_PRINCIPAL_STATE;
	}
}

// Testmode1: Turns on Blue LED if an UART code was received
// Testmode0: Turns on BLue LEDif we are on a state different from PRESTATE
static void UARTFlagCheck(bool_t mode,char state){
	if (mode==TEST_UART_FLAG){
		if(UARTFLAG==1)				// If there is any transition made for the
			turnOn(TEST_LIGHT);		// UART console, then the Blue Led turns on.
		else
			turnOff(TEST_LIGHT);
	}
	else if(mode==TEST_PRINCIPAL_STATE){
		if(state==PRESTATE)			// If we are in PRESTATE we turn off the
			turnOff(TEST_LIGHT);	// Blue Led.
		else
			turnOn(TEST_LIGHT);
	}
}

// To turn on or off the LEDs according to the current state
void LEDsON(char x,char y,char z){
	if(x==1)					// if x==1, then the Yellow LED is turned on,
		turnOn(YELLOW_LIGHT);	// is turned off
	else if(x==0)
		turnOff(YELLOW_LIGHT);

	if(y==1)					// if y==1, then the Red LED is turned on,
		turnOn(RED_LIGHT);		// is turned off
	else if(y==0)
		turnOff(RED_LIGHT);

	if(z==1)					// if z==1, then the Green LED is turned on,
		turnOn(GREEN_LIGHT);	// is turned off
	else if(z==0)
		turnOff(GREEN_LIGHT);

}

// Whenever a change of state is made, it resets the transition conditions
static void ResetChange(dprimario_t * prim){
	delayInit( &prim->delay,prim->timeout);  //Reset the timeout transition
	UARTReset(&uart1);						 //Reset the UART Listening Process
	count=0;								 //Reset the count of number of cycles
	UARTFLAG=0;								 //Reset the UART flag
}

// Verify the transition conditions related to pushbuttons
static void ButtonCheck(dprimario_t * prim, char casea, char casef,char casen ){
	if(!delayRead(&prim->delay)){		//Verify if the Timeout transition limit
		if(get_State(&boton1)){			//Button pressed?
			prim->state=casea;			//The New state is the Alarm related state
			ResetChange(prim);
		}
		else if(get_State(&boton2)){	//Button pressed?
			prim->state=casef;			//The New state is the Fail related state
			ResetChange(prim);
		}
		else if(get_State(&boton3)){	//Button pressed?
			prim->state=casen;			//The New state is the Normal related state
			ResetChange(prim);
		}
	}
	else{								//Timeout transition limit reached
		if((!get_State(&boton1))&&(!get_State(&boton2))&&(!get_State(&boton3))){
			if(UARTFLAG==1){			//I got here from an UART request?
				if(prim->state==PRESTATE){ //Am i stuck in PRESTATE?
					prim->state = FAIL;	//to Fail state, COM Failure
					ResetChange(prim);
					UARTFLAG=1;			//The previous Reset resets the UART Flag
				}
			}
			else
				if(prim->state==PRESTATE){ 	//Am i stuck in PRESTATE?
					prim->state = FAIL;		//to Fail state.
					ResetChange(prim);
				}
		}
	}
}

// Verify the transition conditions related to uart codes
static void UartCheck(dprimario_t * prim, char casea, char casef,char casen ){
	if(uart1.mode==ALARMS){						//Am I listening to Alarm UART codes?
		if((UARTRead(&uart1)==UART_received)){  //Was an Alarm code received?
			prim->state=casea;					//The New state is the Alarm related state
			ResetChange(prim);
			UARTFLAG=1;							//Set the UART Flag interaction
		}

		else if(UARTRead(&uart1)==UART_timeout){//The UART Listening timeout was reached?
			UARTChange(&uart1,FAILURES);		//Set the UART Listening Process to
		}										//monitor Fail codes
	}
	else if (uart1.mode==FAILURES){					//Am I listening to Fail UART codes?
		if((UARTRead(&uart1)==UART_received)){	//Was an Alarm code received?
			prim->state=casef;					//The New state is the Fail related state
			ResetChange(prim);
			UARTFLAG=1;							//Set the UART Flag interaction
			UARTChange(&uart1,ALARMS);			//Set the UART Listening Process to
		}										//monitor Alarm codes

		else if(UARTRead(&uart1)==UART_timeout){//The UART Listening timeout was reached?
			UARTChange(&uart1,NORMALS);			//Set the UART Listening Process to
		}										//monitor Normal codes
	}
	else if(uart1.mode==NORMALS){
		if((UARTRead(&uart1)==UART_received)){	//Was a Normal code received?
			prim->state=casen;					//The New state is the Normal related state
			ResetChange(prim);
			UARTFLAG=1;							//Set the UART Flag interaction
			UARTChange(&uart1,ALARMS);			//Set the UART Listening Process to ALARMS
		}

		else if(UARTRead(&uart1)==UART_timeout){//The UART Listening timeout was reached?
			count++;							//increase the counter of cycles in 1
			UARTChange(&uart1,ALARMS);			//Set the UART Listening Process to
		}										//monitor Alarm codes
	}
	if (count>=CYCLES){							//If the number specified of cycles were reached
		if(UARTFLAG==1){						//I got here from an UART request?
			if(prim->state==PRESTATE){			//Go to Fail state
				prim->state = FAIL;
				ResetChange(prim);
				UARTFLAG=1;
			}
		}
		else{
			if(prim->state==PRESTATE){ 	//Am i stuck in PRESTATE?
				prim->state = FAIL;		//to Fail state.
				ResetChange(prim);
			}
		}
	}
}

// It sets initial conditions for the entire program
bool_t primInit(dprimario_t * pPrimario)
{

	if(NULL==pPrimario)
		return 0;

	pPrimario->state=INITIAL_DEFAULT_STATE;
	pPrimario->timeout= DEF_TIMEOUT;
	delayInit( &pPrimario->delay,pPrimario->timeout);
	LEDsON(0,0,0);
	fsmInit(&boton1,ALARM_BUTTON);	//Initialize buttons with "antirebote" protocol
	fsmInit(&boton2,FAIL_BUTTON);
	fsmInit(&boton3,NORMAL_BUTTON);
	fsmInit(&boton4,TEST_BUTTON);
	UARTInit( &uart1,ALARMS,UART_USB, pPrimario->timeout); //Initialize uart1 through UART_USB
	UARTReport( &uart1, "\r\nInital process completed successfully \r\n" );
	return 1;
}

//update the MEFSs,
void primUpdates(){

    fsmUpdate(&boton1);			//Update of all the MEFSs involved
	fsmUpdate(&boton2);
	fsmUpdate(&boton3);
	fsmUpdate(&boton4);
	UARTUpdate(&uart1);
	TEST();
}

// The MEFS logic, execute the actions related to the state
// and verifies if there is any possible transition.
bool_t primControl(dprimario_t * pPrimario){

	if(NULL==pPrimario)
		return 0;

	if(pPrimario->state==PRESTATE){					//   PRESTATE
		ButtonCheck (pPrimario,ALARM,FAIL,NORMAL);
		UartCheck(pPrimario,ALARM,FAIL,NORMAL);
		UARTFlagCheck(TEST_MODE,PRESTATE);
	}
	else if(pPrimario->state==NORMAL){			    //   NORMAL
		LEDsON(0,0,1);
		ButtonCheck (pPrimario,PRESTATE,PRESTATE,NORMAL);
		UartCheck(pPrimario,PRESTATE,PRESTATE,NORMAL);
		UARTFlagCheck(TEST_MODE,NORMAL);
	}
	else if(pPrimario->state==ALARM){				//   ALARM
		LEDsON(0,1,0);
		ButtonCheck (pPrimario,ALARM,PRESTATE,PRESTATE);
		UartCheck(pPrimario,ALARM,PRESTATE,PRESTATE);
		UARTFlagCheck(TEST_MODE,ALARM);
	}
	else if(pPrimario->state==FAIL){				//   FAIL
		LEDsON(1,0,0);
		ButtonCheck (pPrimario,PRESTATE,FAIL,PRESTATE);
		UartCheck(pPrimario,PRESTATE,FAIL,PRESTATE);
		UARTFlagCheck(TEST_MODE,FAIL);
	}
	else{
		return 0;
	}
	return 1;
}

//It sends through UART Port the Current State of The System.
void primState(dprimario_t * prim){
	switch( prim->state ) {

		case PRESTATE:
			UARTReport( &uart1,"\r\n CURRENT STATE: PRE STATE \r\n");
			break;
		case NORMAL:
			UARTReport( &uart1,"\r\n CURRENT STATE: NORMAL STATE \r\n");
			break;
		case FAIL:
			UARTReport( &uart1,"\r\n CURRENT STATE: FAIL STATE\r\n");
			break;
		case ALARM:
			UARTReport( &uart1,"\r\n CURRENT STATE: ALARM STATE\r\n");
			break;
		default:
			UARTReport( &uart1,"\r\n CURRENT STATE: PLEASE RESTART\r\n");
	}

}

//It sends through UART Port the Current Test Mode of The System.
void primTmode(dprimario_t * prim){
	switch( TEST_MODE ) {

		case TEST_PRINCIPAL_STATE:
			UARTReport( &uart1,"\r\n TEST-MODE: PRINCIPAL STATES \r\n");
			break;
		case TEST_UART_FLAG:
			UARTReport( &uart1,"\r\n TEST-MODE: UART FLAGS \r\n");
			break;
	}

}
