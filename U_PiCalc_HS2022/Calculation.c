/*
 * Calculation.c
 *
 * Created: 09.10.2022 12:10:45
 *  Author: kevin
 */ 

#include "main.h"
#include <math.h>

st_calc gst_calc; 

void calc_leibniz( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	st_calc *pst_calc = &gst_calc; 
	
	float pi_4 = 1.000;
	float pi_calc = 1.000;  
	
	uint32_t i = 3; 
	
	EventBits_t xEventValue; 
	
	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		//Wait until Task is selected
		xEventValue = xEventGroupWaitBits(xPiState, CALC_SEL_LBZ, pdFALSE, pdFALSE, portMAX_DELAY); 
		
		if( xEventGroupGetBits( xPiState ) & STOP_CALC ) //When Stop than check for reset else calculate pi
		{
			if( xEventGroupGetBits( xPiState ) & RESET_CALC )	//Reset Calculation parameter
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

void calc_nilakantha( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	st_calc *pst_calc = &gst_calc; 

   float i = 2;    // Number of iterations and control variable
   int8_t s = 1;   //Signal for the next operation
   float pi = 3;

	EventBits_t xEventValue;

	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		//Wait until Task is selected
		xEventValue = xEventGroupWaitBits(xPiState, CALC_SEL_NLK, pdFALSE, pdFALSE, portMAX_DELAY); 
		
		if( xEventGroupGetBits( xPiState ) & STOP_CALC ) //When Stop than check for reset else calculate pi
		{
			if( xEventGroupGetBits( xPiState ) & RESET_CALC )	//Reset Calculation parameter
			{

				//Clear the result too
				pst_calc->pi = 1.00; 
				
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
	
						pi = pi +  s * (4 / (i * (i + 1) * (i + 2)));
						s = -s;
						i += 2; 
						pst_calc->pi = pi; 
				} while ( !( xEventGroupGetBits( xPiState ) & STOP_CALC ));	//Stop
			}
		}
	}	
}