/**
 * @file   main.c
 *
 * @brief  Brief description of the content of template.c
 * @author Kevin Perillo, Juventus Techniker Schule
 * @date   08.10.2022 - first implementation
 * @version 1.0.0
 * 
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright (c) 2022 Juventus Techniker Schule
 */

 //...........................................................................................................
 /**
 * @brief  Includes
 *
 * Section for module-specific include files
 * If all include files are inserted in main.h, only the file main.h must be included here
 */
#include "main.h"

//...........................................................................................................
/**
 * @brief   Controll Task 
 * @param   void *pvParameters
 * @retval  none
 */
static void controllerTask(void* pvParameters);


/* Task handles for heap overflow monitoring. */
#define TASK_STATES_MAX ( 7 )

typedef struct
{
	TaskHandle_t handle;
	BaseType_t stack_high_water_mark;
} st_task_state_t;

st_task_state_t task_state[ TASK_STATES_MAX ];


//...........................................................................................................
/**
 * @brief   Main Loop
 * @param   none
 * @retval  none
 */
int main( void )
{
	BaseType_t task_status;
	
	//Init Clock
	vInitClock( );
	
	/* Create Event Group --------------------------------------------------------------------- */
	xPiState = xEventGroupCreate( ); 
	
	/* UI-Task -------------------------------------------------------------------------------- */ 
	task_status = xTaskCreate( ui_handler,								// Task function
							   (const char *) "uiTask",					// Task name
							   TASK_STACK_UI,							// Task stack size
							   NULL,									//
							   TASK_PRIORITY_UI,						// Task Priority
							   &task_state[ UI_TASK_HANDLE ].handle );	// Task Handle
	//configASSERT( task_status == pdPASS );								// Check if task created correct
		
	/* Controll Task --------------------------------------------------------------------------- */
	task_status = xTaskCreate( controllerTask,
							   (const char *) "ctlTask",
							   TASK_STACK_CTL, 
				               NULL,
				               TASK_PRIORITY_CTL,
				               &task_state[ CTL_TASK_HANDLE ].handle );
	//configASSERT( task_status == pdPASS );				

	/* Calculate Leibniz Task ------------------------------------------------------------------ */
	task_status = xTaskCreate( calc_leibniz,
							   (const char *) "clcLbz",
							   TASK_STACK_CALC,
							   NULL,
							   TASK_PRIORITY_CALC,
							   &task_state[ CALC_LBZ_TASK_HANDLE ].handle );
	//configASSERT( task_status == pdPASS );
	
	/* Calculate nilakantha Task ------------------------------------------------------------------ */
	task_status = xTaskCreate( calc_nilakantha,
							   (const char *) "clcNlk",
							   TASK_STACK_CALC,
							   NULL,
							   TASK_PRIORITY_CALC,
							   &task_state[ CALC_NLK_TASK_HANDLE ].handle );
	//configASSERT( task_status == pdPASS );
	
	/* Measure time of calculation Task -------------------------------------------------------- */
	task_status = xTaskCreate( calcTimeHandlerTask,
							   (const char *) "clcTim",
 							   TASK_STACK_TIME,
 							   NULL,
							   TASK_PRIORITY_TIME,
							   &task_state[ CALC_TIME_HANDLE ].handle );
	//configASSERT( task_status == pdPASS );
	
	/* LED handler Task ------------------------------------------------------------------------ */
	task_status = xTaskCreate( led_handler, 
							   (const char *) "ledHdl", 
							   TASK_STACK_LED, 
							   NULL, 
							   TASK_PRIORITY_LED, 
							   &task_state[ LED_TASK_HANDLE ].handle ); 
	//configASSERT( task_status == pdPASS ); 
	
	/* Start the scheduler */
	vTaskStartScheduler( );
	
	return 0;
}

//...........................................................................................................
/**
 * @brief   Controll Task 
 * @param   none
 * @retval  none
 */
static void controllerTask( void* pvParameters ) 
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	//Init Button function
	initButtons( );
	
	//Static Variable to save state
	static uint8_t calc_tgl = 0;
		
	while( xPiState == NULL)	// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; ) 
	{
		updateButtons( );
		
		if( getButtonPress( BUTTON1 ) == SHORT_PRESSED ) // Set Start Bit / Clear Stop Bit
		{
			xEventGroupSetBits( xPiState, START_CALC ); 
			xEventGroupClearBits(xPiState, STOP_CALC);
		}
		if( getButtonPress( BUTTON2 ) == SHORT_PRESSED ) // Set Stop Bit / Clear Start Bit
		{
			xEventGroupSetBits( xPiState, STOP_CALC );
			xEventGroupClearBits(xPiState, START_CALC);
		}
		if( getButtonPress( BUTTON3 ) == SHORT_PRESSED ) // Set Reset Bit
		{
			xEventGroupSetBits(xPiState, RESET_CALC);
		}
		if( getButtonPress(BUTTON4) == SHORT_PRESSED ) // Toggle between Calculation Tasks
		{
			if(calc_tgl) 
			{
				xEventGroupSetBits(xPiState, CALC_SEL_NLK); 
				xEventGroupClearBits(xPiState, CALC_SEL_LBZ); 
				calc_tgl = 0; 
			}
			else 
			{
				xEventGroupSetBits(xPiState, CALC_SEL_LBZ );
				xEventGroupClearBits(xPiState, CALC_SEL_NLK );
				calc_tgl = 1; 
			}
		}

		/* Long Press function is not used at the time */
		
		vTaskDelay(10/portTICK_RATE_MS);
	}
}

