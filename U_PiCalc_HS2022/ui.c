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
	
	st_calc *pst_calc = &gst_calc; 
	
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
	
	for( ;; )
	{
		// Draw tilte on every page same :)
		vDisplayClear(); //Clear Display before rewriting it
		vDisplayWriteStringAtPos(0,0,"Pi Calculation V1.0 PEK"); 
						
		switch( mode )
		{
			case MODE_IDLE:
				vDisplayClear();
				vDisplayWriteStringAtPos(1,0,"Mode: Idle");
				
				if( xEventGroupGetBits( xPiState ) & CALC_SEL_NLK )
				{
					vDisplayWriteStringAtPos(2,0,"Selection: NLK"); //Show selection but not change mode
					if( xEventGroupGetBits( xPiState ) & START_CALC ) mode = MODE_CALC_NLK; 
				}
				
				if( xEventGroupGetBits( xPiState ) & CALC_SEL_LBZ )
				{
					vDisplayWriteStringAtPos(2,0,"Selection: LBZ"); //Show selection but not change mode
					if( xEventGroupGetBits( xPiState ) & START_CALC ) mode = MODE_CALC_LBZ; 
				}
					 	
			break;  
				
			case MODE_CALC_LBZ:
			vDisplayClear();
				vDisplayWriteStringAtPos(1,0,"Mode: Calc Leibniz");
				
				//Display pi calculation on row three
				sprintf(dispBuffer, "Pi: %0.8f", pst_calc->pi);
				vDisplayWriteStringAtPos(2,0,dispBuffer);
				
				//Go back to idle when stop
				if( xEventGroupGetBits( xPiState ) & STOP_CALC ) mode = MODE_IDLE; 
			break; 
				 
			case MODE_CALC_NLK:
			vDisplayClear();
				vDisplayWriteStringAtPos(1,0,"Mode:Calc Nilakantha");
				
				//Display pi calculation on row three
				sprintf(dispBuffer, "Pi: %0.8f", pst_calc->pi); 
				vDisplayWriteStringAtPos(2,0,dispBuffer);
				
				//Go back to idle when stop
				if( xEventGroupGetBits( xPiState ) & STOP_CALC ) mode = MODE_IDLE;
			break; 
				
			default: 
			vDisplayClear();
				error( ERR_TEST ); //Wrong mode should not go to here, when yet -> reset system
			break;  
		}
		
		// Button name -> same for every mode
		vDisplayWriteStringAtPos(3,0,"st|sp|rst|tgl"); // Start | Stop | Reset | Toggle
		
		vTaskDelay( 500 / portTICK_RATE_MS ); // Refresh Display Content all 500ms
	}
}