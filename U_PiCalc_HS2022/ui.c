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
	
	st_calc_time *pst_time = &gst_calc_time; 
	st_calc *pst_calc = &gst_calc; 
	
	// Local variables
	char dispBuffer[25]; 
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
				
				//xEventGroupSetBits(xPiState, BIT5); //Clear accurate LED 
				
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
				sprintf(dispBuffer, "Pi: %0.6f |T:%lds", pst_calc->pi, (pst_time->calc_time/1000));
				vDisplayWriteStringAtPos(2,0,dispBuffer);
				
				//Go back to idle when stop
				if( xEventGroupGetBits( xPiState ) & STOP_CALC ) mode = MODE_IDLE; 
			break; 
				 
			case MODE_CALC_NLK:
			vDisplayClear();
				vDisplayWriteStringAtPos(1,0,"Mode:Calc Nilakantha");
				
				//Display pi calculation on row three
				sprintf(dispBuffer, "Pi: %0.6f |T:%ldms", pst_calc->pi, pst_time->calc_time); 
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
		vDisplayWriteStringAtPos(3,0,"start|stop|reset|tgl"); // Start | Stop | Reset | Toggle
				
		vTaskDelay( 500 / portTICK_RATE_MS ); // Refresh Display Content all 500ms
	}
}





void led_handler( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
		
	EventBits_t xEventValue;
	
	//Init LED
	PORTF.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm; /*Initialize LED1-LED4*/
	PORTF.OUTSET = 0x0F; //Initial State of LEDs: Off
	
	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );

	}
	
	for( ;; )
	{
		xEventValue = xEventGroupWaitBits(xPiState, ( LBZ_STATE | NLK_STATE ), pdFALSE, pdFALSE, portMAX_DELAY ); //Wait until calculation is accurate
		
		if( xEventValue & LBZ_STATE )
		{
			PORTF.OUTCLR = 0x01; //Turn LED On
			xEventGroupClearBits( xPiState, LBZ_STATE ); 
		}
		else if( xEventValue & NLK_STATE )
		{
			PORTF.OUTCLR = 0x02; //Turn LED On
			xEventGroupClearBits( xPiState, NLK_STATE ); 
		}
	
		xEventValue = xEventGroupWaitBits(xPiState, ( RESET_CALC ), pdFALSE, pdFALSE, portMAX_DELAY ); //Wait until LED can be cleared
		if(xEventValue & RESET_CALC) PORTF.OUTSET = 0x0F; //Initial State of LEDs: Off
	}
}