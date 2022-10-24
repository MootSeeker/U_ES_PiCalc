/**
 * @file   Calculation.c
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
#include <math.h>

//...........................................................................................................
/**
 * @brief  Definition of the global structure "gst_calc" => global access to elements of a "st_calc"
 */
st_calc gst_calc; 


//...........................................................................................................
/**
 * @brief   Calculation task of pi with Leibniz
 * @param   void *pvParameters
 * @retval  none
 */
void calc_leibniz( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	// Define structure pointers
	st_calc *pst_calc = &gst_calc; 
	
	// Local variables
	float pi_4 = 1.00;
	float pi_calc = 1.00;  
	uint32_t i = 3; 
	
	//define Event bit variable
	EventBits_t xEventValue; 
	
	while( xPiState == NULL)			// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		//Wait until Task is selected
		xEventValue = xEventGroupWaitBits(xPiState, CALC_SEL_LBZ, pdFALSE, pdFALSE, portMAX_DELAY); 
		
		//When Stop than check for reset else calculate pi
		if( xEventGroupGetBits( xPiState ) & STOP_CALC ) 
		{
			//Reset Calculation parameter
			if( xEventGroupGetBits( xPiState ) & RESET_CALC )	
			{
				pi_calc = 1.0;
				pi_4 = 1.0;  
				i = 3; 
				
				//Clear the result too
				pst_calc->pi = 1.00;
				
				//Clear Reset flag
				xEventGroupClearBits(xPiState, RESET_CALC ); 
			}
		}
		else
		{
			if(  xEventGroupGetBits( xPiState ) & START_CALC )
			{
				do
				{
					pi_4 = pi_4 - ( 1.0 / i ) + ( 1.0 / ( i + 2 ));
					i += 4;			
					pi_calc = pi_4 * 4;
					pst_calc->pi = pi_calc;  
				} while( !(xEventGroupGetBits( xPiState ) & STOP_CALC) );
			}
		}
	}
}

//...........................................................................................................
/**
 * @brief   Calculation task of pi with Nilakantha
 * @param   void *pvParameters
 * @retval  none
 */
void calc_nilakantha( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	// Define structure pointers
	st_calc *pst_calc = &gst_calc; 

	// Local variables
    float i = 2;    // Number of iterations and control variable
    int8_t s = 1;   //Signal for the next operation
    float pi = 3;

	//define Event bit variable
	EventBits_t xEventValue;

	while( xPiState == NULL)		// Wait for EventGroup to be initialized in other task
	{
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		//Wait until Task is selected
		xEventValue = xEventGroupWaitBits(xPiState, CALC_SEL_NLK, pdFALSE, pdFALSE, portMAX_DELAY); 
		
		//When Stop than check for reset else calculate pi
		if( xEventGroupGetBits( xPiState ) & STOP_CALC ) 
		{
			//Reset calculation parameter
			if( xEventGroupGetBits( xPiState ) & RESET_CALC )	
			{

				//Clear the result too
				pst_calc->pi = 1.00; 
				
				i = 2;    // Number of iterations and control variable
				s = 1;    // Signal for the next operation
				pi = 3;	  // Start value of calculation	

				//Clear Reset flag
				xEventGroupClearBits(xPiState, RESET_CALC );
			}
		}
		else
		{
			if( xEventGroupGetBits( xPiState ) & START_CALC )
			{
				do // Approximation of the number PI through the sequence of the Nilakantha's series
				{
					pi = pi + (s * (4 / ((i) * (i + 1) * (i + 2))));
					s = s * (-1);
					i += 2; 
					pst_calc->pi = pi; 
				} while ( !( xEventGroupGetBits( xPiState ) & STOP_CALC ));	//Stop
			}
		}
	}	
}