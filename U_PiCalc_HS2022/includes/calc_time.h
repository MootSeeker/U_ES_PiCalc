/*
 * calc_time.h
 *
 * Created: 22.10.2022 10:27:54
 *  Author: kevin
 */ 


#ifndef CALC_TIME_H_
#define CALC_TIME_H_


typedef struct  
{
	uint32_t calc_time;
	uint32_t start_time;
	uint32_t stop_time;
}st_calc_time;

extern st_calc_time gst_calc_time; 

void calcTimeHandlerTask( void *pvParameters ); 

#endif /* CALC_TIME_H_ */