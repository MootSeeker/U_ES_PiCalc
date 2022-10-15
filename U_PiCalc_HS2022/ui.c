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
	
	// Local variables
	char dispBuffer[50]; 
	uint8_t mode = MODE_IDLE; 
	
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
		
		switch( mode )
		{
			case MODE_IDLE:
				vDisplayClear(); //Clear Display before rewriting it
				vDisplayWriteStringAtPos(0,0,"Pi Calculation V1.0"); //Draw Title
				vDisplayWriteStringAtPos(1,0,"Mode Idle");
				
				if( event == CALC_SEL )
				{
					vDisplayWriteStringAtPos(2,0,"Selection: LBZ");
				}
				else
				{
					vDisplayWriteStringAtPos(2,0,"Selection: BLD");	
				}
			break;  
				
			case MODE_CALC_LBZ:
				
			break; 
				 
			case MODE_CALC_BLD:
				
			break; 
				
			default: 
				
			break;  
		}
		
		vTaskDelay( 500 / portTICK_RATE_MS ); // Refresh Display Content all 500ms
	}
}