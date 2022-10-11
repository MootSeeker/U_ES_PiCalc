/*
 * Calculation.c
 *
 * Created: 09.10.2022 12:10:45
 *  Author: kevin
 */ 

#include "main.h"

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
		if( xEventGroupGetBits( xPiState ) == BIT0 )
		{
			while( xEventGroupGetBits( xPiState ) != BIT1 ) 
			{
				pi_4 = pi_4 - ( 1.0 / i ) + ( 1.0 / ( i + 2 ));
				i += 4;			
				pi_calc = pi_4 * 4;
			} 
		}
	}
}