/*
 * main.c
 *
 * Created: 08.10.2022 18:25:05
 * Author : MootSeeker
 */ 

#include "main.h"

void controllerTask(void* pvParameters);

/* Task handles for heap overflow monitoring. */
#define TASK_STATES_MAX ( 5 )

typedef struct
{
	TaskHandle_t handle;
	BaseType_t stack_high_water_mark;
} st_task_state_t;

st_task_state_t task_state[ TASK_STATES_MAX ];


int main( void )
{
	BaseType_t task_status;
	
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
	configASSERT( task_status == pdPASS );								// Check if task created correct
		
	/* Controll Task --------------------------------------------------------------------------- */
	task_status = xTaskCreate( controllerTask,
							   (const char *) "ctlTask",
							   TASK_STACK_CTL, 
				               NULL,
				               TASK_PRIORITY_CTL,
				               &task_state[ CTL_TASK_HANDLE ].handle );
	configASSERT( task_status == pdPASS );				

	/* Calculate Leibniz Task ------------------------------------------------------------------ */
	task_status = xTaskCreate( calc_leibniz,
							   (const char *) "clcLbz",
							   TASK_STACK_CALC,
							   NULL,
							   TASK_STACK_CALC,
							   &task_state[ CALC_LBZ_TASK_HANDLE ].handle );
	configASSERT( task_status == pdPASS );
	
	/* Start the scheduler */
	vTaskStartScheduler( );
	
	return 0;
}

void controllerTask( void* pvParameters ) 
{
	initButtons( );
	
	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; ) 
	{
		updateButtons( );
		
		if( getButtonPress( BUTTON1 ) == SHORT_PRESSED ) 
		{
			char pistring[ 12 ];
			sprintf( &pistring[0], "PI: %.8f", M_PI );
			vDisplayWriteStringAtPos( 1, 0, "%s", pistring );
		}
		if( getButtonPress( BUTTON2 ) == SHORT_PRESSED ) 
		{
			xEventGroupSetBits( xPiState, BIT0 ); 
			xEventGroupClearBits( xPiState, BIT1 ); 
		}
		if( getButtonPress( BUTTON3 ) == SHORT_PRESSED ) 
		{
			
		}
		if( getButtonPress(BUTTON4) == SHORT_PRESSED ) 
		{
			
		}
		if( getButtonPress( BUTTON1 ) == LONG_PRESSED ) 
		{
			
		}
		if( getButtonPress( BUTTON2 ) == LONG_PRESSED ) 
		{
			xEventGroupSetBits( xPiState, BIT1 );
			xEventGroupClearBits( xPiState, BIT0 ); 
		}
		if( getButtonPress( BUTTON3 ) == LONG_PRESSED ) 
		{
			
		}
		if( getButtonPress( BUTTON4 ) == LONG_PRESSED ) 
		{
			
		}
		vTaskDelay(10/portTICK_RATE_MS);
	}
}