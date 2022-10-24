/**
 * @file   ui.c
 *
 * @brief  Brief description of the content of template.c
 * @author Kevin Perillo, Juventus Techniker Schule
 * @date   09.10.2022 - first implementation
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
 * @brief   Ui Handler - Controlling Display
 * @param   void *pvParameters
 * @retval  none
 */
void ui_handler( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	// Define structure pointers
	st_calc_time *pst_time = &gst_calc_time; 
	st_calc *pst_calc = &gst_calc; 
	
	// Local variables
	char dispBuffer[25]; 
	uint8_t mode = MODE_IDLE; 
	
	/* Init Display */
	vInitDisplay( );
	vDisplayClear();
	vDisplayWriteStringAtPos( 0, 0, "Pi-Calculation" );
	
	while( xPiState == NULL)		// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		// Draw tilte on every page same :)
		vDisplayClear(); //Clear Display before rewriting it
		vDisplayWriteStringAtPos(0,0,"Pi Calc V1.0 PEK"); 
						
		switch( mode )
		{
			case MODE_IDLE:
				// Clear Display and draw new Title
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
				// Clear Display and draw new Title
				vDisplayClear();
				vDisplayWriteStringAtPos(1,0,"Mode: Calc Leibniz");
				
				//Display pi calculation on row three
				sprintf(dispBuffer, "Pi: %0.6f |T:%lds", pst_calc->pi, (pst_time->calc_time/1000));
				vDisplayWriteStringAtPos(2,0,dispBuffer);
				
				//Go back to idle when stop
				if( xEventGroupGetBits( xPiState ) & STOP_CALC ) mode = MODE_IDLE; 
			break; 
				 
			case MODE_CALC_NLK:
				// Clear Display and draw new Title
				vDisplayClear();
				vDisplayWriteStringAtPos(1,0,"Mode:Calc Nilakantha");
				
				//Display pi calculation on row three
				sprintf(dispBuffer, "Pi: %0.6f |T:%ldms", pst_calc->pi, pst_time->calc_time/1000); 
				vDisplayWriteStringAtPos(2,0,dispBuffer);
				
				//Go back to idle when stop
				if( xEventGroupGetBits( xPiState ) & STOP_CALC ) mode = MODE_IDLE;
			break; 
				
			default: 
				// Clear Display
				vDisplayClear();
				error( ERR_TEST ); //Wrong mode should not go to here, when yet -> reset system
			break;  
		}
		
		// Button name -> same for every mode
		vDisplayWriteStringAtPos(3,0,"start|stop|reset|tgl"); // Start | Stop | Reset | Toggle
				
		vTaskDelay( 500 / portTICK_RATE_MS ); // Refresh Display Content all 500ms
	}
}


//...........................................................................................................
/**
 * @brief   Led Handler - Controlling onboard LED
 * @param   void *pvParameters
 * @retval  none
 */
void led_handler( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
		
	//define Event bit variable
	EventBits_t xEventValue;
	
	//Init LED
	PORTF.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm; /*Initialize LED1-LED4*/
	PORTF.OUTSET = 0x0F; //Initial State of LEDs: Off
	
	while( xPiState == NULL)			// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );

	}
	
	for( ;; )
	{
		// Wait until calculation is accurate
		xEventValue = xEventGroupWaitBits(xPiState, ( LBZ_STATE | NLK_STATE ), pdFALSE, pdFALSE, portMAX_DELAY ); 
		
		if( xEventValue & LBZ_STATE )	// Leibniz is accurate
		{
			PORTF.OUTCLR = 0x01; //Turn LED On
			xEventGroupClearBits( xPiState, LBZ_STATE ); 
		}
		else if( xEventValue & NLK_STATE )	// Nilakantha is accurate
		{
			PORTF.OUTCLR = 0x02; //Turn LED On
			xEventGroupClearBits( xPiState, NLK_STATE ); 
		}
	
		// Wait until LED can be cleared
		xEventValue = xEventGroupWaitBits(xPiState, ( RESET_CALC ), pdFALSE, pdFALSE, portMAX_DELAY ); 
		if(xEventValue & RESET_CALC) PORTF.OUTSET = 0x0F; //Initial State of LEDs: Off
	}
}