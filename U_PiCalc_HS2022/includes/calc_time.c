/*
 * calc_time.c
 *
 * Created: 22.10.2022 10:28:08
 *  Author: kevin
 */ 

#include "main.h"

st_calc_time gst_calc_time; 


void calcTimeHandlerTask( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	
	st_calc_time *pst_time = &gst_calc_time; 
	st_calc *pst_calc = &gst_calc; 
	
	pst_time->calc_time = 0;
	pst_time->start_time = 0;
	pst_time->stop_time = 0;
	
	uint32_t uint_pi;
	
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
			if( !pst_time->stop_time )
			{
				pst_time->stop_time = xTaskGetTickCount( );
				pst_time->calc_time = pst_time->stop_time - pst_time->start_time;
			}
			
			
			if( xEventGroupGetBits(xPiState) & CALC_SEL_LBZ )
			{
				xEventGroupSetBits(xPiState, LBZ_STATE);
			}
			else if( xEventGroupGetBits(xPiState) & CALC_SEL_NLK)
			{
				xEventGroupSetBits(xPiState, NLK_STATE);
			}
		}
		
		xEventValue = xEventGroupWaitBits(xPiState, ( RESET_CALC ), pdFALSE, pdFALSE, (10 / portTICK_RATE_MS) ); //Wait for 10ms to check if values could be cleared
		if(xEventValue & RESET_CALC) 
		{
			pst_time->calc_time = 0; 
			pst_time->start_time = 0; 
			pst_time->stop_time = 0; 
		}
	}
}