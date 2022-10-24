/**
 * @file   calc_time.c
 *
 * @brief  Brief description of the content of template.c
 * @author Kevin Perillo, Juventus Techniker Schule
 * @date   22.10.2022 - first implementation
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
 * @brief  Definition of the global structure "gst_calc_time" => global access to elements of a "st_calc_time"
 */
st_calc_time gst_calc_time; 

//...........................................................................................................
/**
 * @brief   Calculation task of pi with Leibniz
 * @param   void *pvParameters
 * @retval  none
 */
void calcTimeHandlerTask( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	// Define structure pointers
	st_calc_time *pst_time = &gst_calc_time; 
	st_calc *pst_calc = &gst_calc; 

	// Local variables
	uint32_t uint_pi;
	
	// Clear times	
	pst_time->calc_time = 0;
	pst_time->start_time = 0;
	pst_time->stop_time = 0;
	
	//define Event bit variable
	EventBits_t xEventValue;
	
	while( xPiState == NULL)	// Wait for EventGroup to be initialized in other task
	{
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		//Wait until Start Calculation is selected
		xEventValue = xEventGroupWaitBits(xPiState, START_CALC, pdFALSE, pdFALSE, portMAX_DELAY);
		
		//At first time get start time
		if( !pst_time->start_time ) pst_time->start_time = xTaskGetTickCount( );
		
		//Get the actual value of pi
		uint_pi = pst_calc->pi * 100000;
		
		//Check if pi is accurate enougth
		if( uint_pi == 314159 )	//Wait until Pi is accurate
		{
			if( !pst_time->stop_time )	// Stop new measurement
			{
				pst_time->stop_time = xTaskGetTickCount( );
				pst_time->calc_time = pst_time->stop_time - pst_time->start_time;
			}
			
			//Set accurate calculation Event-Bit
			if( xEventGroupGetBits(xPiState) & CALC_SEL_LBZ )
			{
				xEventGroupSetBits(xPiState, LBZ_STATE);
			}
			else if( xEventGroupGetBits(xPiState) & CALC_SEL_NLK)
			{
				xEventGroupSetBits(xPiState, NLK_STATE);
			}
		}
		
		// Wait for Reset
		xEventValue = xEventGroupWaitBits(xPiState, ( RESET_CALC ), pdFALSE, pdFALSE, (10 / portTICK_RATE_MS) ); //Wait for 10ms to check if values could be cleared
		if(xEventValue & RESET_CALC) 
		{
			pst_time->calc_time = 0; 
			pst_time->start_time = 0; 
			pst_time->stop_time = 0; 
		}
	}
}