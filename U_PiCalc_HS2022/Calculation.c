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
	
	float64_t pi_4 = f_sd(1.000);
	float64_t pi_calc = f_sd(1.000);  
	
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
					pi_4 = f_sub(pi_4, f_sd(( 1.0 / i ) + ( 1.0 / ( i + 2 ))));
					i += 4;
					pi_calc = f_mult(pi_4, f_sd(4.000));
				} while( !(xEventGroupGetBits( xPiState ) & STOP_CALC) );
			}
		}
	}
}

void calc_bellard( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	

	float pi_calc = 1.0;  
	float sum1 = 1.0;
	float sum2 = 1.0;
	
	uint32_t n = 0; 

	EventBits_t xEventValue;

	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		//Wait until Task is selected
		xEventValue = xEventGroupWaitBits(xPiState, CALC_SEL_BLD, pdFALSE, pdFALSE, portMAX_DELAY); 
		
		if( xEventGroupGetBits( xPiState ) & STOP_CALC ) //When Stop than check for reset else calculate pi
		{
			if( xEventGroupGetBits( xPiState ) & RESET_CALC )	//Reset Calculation parameter
			{
				pi_calc = 1.0;
				sum1 = 1.0;
				sum2 = 1.0;
				n = 0;
				
				//Clear Reset flag
				xEventGroupClearBits(xPiState, RESET_CALC );
			}
		}
		else
		{
			if( xEventGroupGetBits( xPiState ) & START_CALC )
			{
				do
				{
					sum1 = ( pow(-1, n) / (( 2 * n + 1 ) * pow( 4, n )));
					sum2 = (1/64) * (pow(-1, n)/pow(1024, n)) * ((32/(4*n+1)) + (8/(4*n+2)) + (1/(4*n+3)));
						
					pi_calc = sum1 - sum2;
					n++;
				} while ( !( xEventGroupGetBits( xPiState ) & STOP_CALC ));	//Stop
			}
		}
	}	
}