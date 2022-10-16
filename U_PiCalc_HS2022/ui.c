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
		
		// Draw tilte on every page same :)
		vDisplayClear(); //Clear Display before rewriting it
		vDisplayWriteStringAtPos(0,0,"Pi Calculation V1.0 PEK"); 
						
		switch( mode )
		{
			case MODE_IDLE:

				vDisplayWriteStringAtPos(1,0,"Mode: Idle");
				
				if( (xEventGroupGetBits( xPiState ) == CALC_SEL ) && (xEventGroupGetBits( xPiState ) == START_CALC) )
				{
					vDisplayWriteStringAtPos(2,0,"Selection: BLD");
					mode = MODE_CALC_BLD; 
				}
				else if( (xEventGroupGetBits( xPiState ) != CALC_SEL) && (xEventGroupGetBits( xPiState ) == START_CALC))
				{
					vDisplayWriteStringAtPos(2,0,"Selection: LBZ");
					mode = MODE_CALC_LBZ; 
				}
				else if( (xEventGroupGetBits( xPiState ) == CALC_SEL) && (xEventGroupGetBits( xPiState ) != START_CALC))
				{
					vDisplayWriteStringAtPos(2,0,"Selection: BLD"); //Show selection but not change mode
				}
				else
				{
					vDisplayWriteStringAtPos(2,0,"Selection: LBZ"); //Show selection but not change mode
				}
					 	
			break;  
				
			case MODE_CALC_LBZ:
				vDisplayWriteStringAtPos(1,0,"Mode: Calc Leibniz");
				
				//Display pi calculation on row three
				
				//Go back to idle when stop
				if(xEventGroupGetBits( xPiState ) == STOP_CALC)mode = MODE_IDLE; 
			break; 
				 
			case MODE_CALC_BLD:
				vDisplayWriteStringAtPos(1,0,"Mode: Calc Bellard");
				
				//Display pi calculation on row three
				
				//Go back to idle when stop
				if(xEventGroupGetBits( xPiState ) == STOP_CALC)mode = MODE_IDLE;
			break; 
				
			default: 
				error( ERR_TEST ); //Wrong mode should not go to here, when yet -> reset system
			break;  
		}
		
		// Button name -> same for every mode
		vDisplayWriteStringAtPos(3,0,"st|sp|rst|tgl"); // Start | Stop | Reset | Toggle
		
		vTaskDelay( 500 / portTICK_RATE_MS ); // Refresh Display Content all 500ms
	}
}