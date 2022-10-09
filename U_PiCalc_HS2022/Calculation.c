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
	
	
	for( ;; )
	{
			
			pi_4 = pi_4 - (1.0 / i) + (1.0/(i+2));
			i+=4;  
	
		pi_calc = pi_4 * 4; 
		vTaskDelay( 1 / portTICK_RATE_MS ); // Go back to scheduler
	}
}