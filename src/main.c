/*=============================================================================
 * Copyright (c) 2020, DANIEL MARQUEZ <DAMF618@GMAIL.COM>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/04/16
 * Version: 1
 *===========================================================================*/

/*=====[Definition macros of private constants]==============================*/

// The maximum number of tasks required at any one time during the execution
// of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCHEDULER_MAX_TASKS   (10)

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "seos_pont.h"
#include "userTasks.h"

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   boardInit();
   
   // Initialize myTask   
   TaskInit( 0 ); // Parameter passed into the task init.

   // Initialize scheduler
   schedulerInit();

   // Add Task1 to the Scheduler
   schedulerAddTask( Primario, // Function that implements the Logic of the device.
              	  	  0,            // Parameter passed.
                      1,            // Execution offset in ticks.
                     10				// Periodicity of task execution in ticks.
                   );
   // Add Task2 to the Scheduler
   schedulerAddTask( AllUpdates, // Function that implements all the updates.
                 	  0,			// Parameter passed.
                      0,			// Execution offset in ticks.
                      5				// Periodicity of task execution in ticks.
                    );
   // Add Task3 to the Scheduler
   schedulerAddTask( CurrentState, // Function that notifies the user of the current state.
                  	  0,			// Parameter passed.
                      2,			// Execution offset in ticks.
                   1000				// Periodicity of task execution in ticks.
                    );
   // Add Task4 to the Scheduler
   schedulerAddTask( CurrentTmode, // Function that notifies the user of the current testing mode.
                  	  0,			// Parameter passed.
                      3,			// Execution offset in ticks.
                   5000				// Periodicity of task execution in ticks.
                    );
   // Add Task5 to the Scheduler
   schedulerAddTask( Test, // Function that notifies the user of the current testing mode.
                      0,			// Parameter passed.
                      4,			// Execution offset in ticks.
                      50				// Periodicity of task execution in ticks.
                    );

   // Initialize task scheduler each 1ms.
   schedulerStart( 1 );

   while( true ){
      // Dispatch (execute) tasks that are mark to be execute by scheduler.
      schedulerDispatchTasks();
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
