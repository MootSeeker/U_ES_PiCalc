/*
 * ui.c
 *
 * Created: 09.10.2022 11:45:47
 *  Author: kevin
 */ 

#include "main.h"







void ui_handler( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	char dispBuffer[50]; 
	
	/* Init Display */
	vInitDisplay( );
	vDisplayClear();
	vDisplayWriteStringAtPos( 0, 0, "Pi-Calculation" );
	
	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	EventBits_t event; 
	
	for( ;; )
	{
		event = xEventGroupGetBits(xPiState); 
		
		sprintf(dispBuffer, "Eventbits: %d",event);
		vDisplayWriteStringAtPos( 1, 0, dispBuffer ); 
		
		vTaskDelay( 500 / portTICK_RATE_MS ); // Refresh Display Content all 500ms
	}
}