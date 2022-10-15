/*
 * Calculation.c
 *
 * Created: 09.10.2022 12:10:45
 *  Author: kevin
 */ 

#include "main.h"
#include <math.h>

void calc_leibniz( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	float pi_4 = 1.0;
	float pi_calc = 1.0;  
	
	uint32_t i = 3; 
	
	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{ 
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		if( xEventGroupGetBits( xPiState ) != CALC_SEL )
		{
			if( xEventGroupGetBits( xPiState ) == START_CALC )
			{
				do 
				{
					pi_4 = pi_4 - ( 1.0 / i ) + ( 1.0 / ( i + 2 ));
					i += 4;			
					pi_calc = pi_4 * 4;
				} while( xEventGroupGetBits( xPiState ) != STOP_CALC ); 
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

	while( xPiState == NULL)					// Wait for EventGroup to be initialized in other task
	{
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
	
	for( ;; )
	{
		if( xEventGroupGetBits( xPiState ) == CALC_SEL )	// Bellard Selected
		{
			if( xEventGroupGetBits( xPiState ) == START_CALC )	// Start 
			{
				do 
				{
					sum1 = ( pow(-1, n) / (( 2 * n + 1 ) * pow( 4, n ))); 
					sum2 = (1/64) * (pow(-1, n)/pow(1024, n)) * ((32/(4*n+1)) + (8/(4*n+2)) + (1/(4*n+3))); 
					
					pi_calc = sum1 - sum2; 
					n++; 
				} while ( xEventGroupGetBits( xPiState ) != STOP_CALC );	//Stop
			}
		}
	}	
}