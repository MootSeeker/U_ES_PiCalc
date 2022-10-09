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
	
	// UI-Task 
	task_status = xTaskCreate( ui_handler,
							   (const char *) "uiTask",
							   TASK_STACK_UI,
							   NULL,
							   TASK_PRIORITY_UI,
							   &task_state[ UI_TASK_HANDLE ].handle );
	configASSERT( task_status == pdPASS );								// Prüfen ob der Task korrekt erstellt wurde
		
	// Controll Task
	task_status = xTaskCreate( controllerTask,
							   (const char *) "control_tsk",
							   configMINIMAL_STACK_SIZE+150, 
				               NULL,
				               3,
				               NULL );
	configASSERT( task_status == pdPASS );				// Prüfen ob der Task korrekt erstellt wurde

	/* Start the scheduler */
	vTaskStartScheduler( );
	
	return 0;
}

void controllerTask( void* pvParameters ) 
{
	initButtons( );
	
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