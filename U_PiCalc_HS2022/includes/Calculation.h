/*
 * Calculation.h
 *
 * Created: 09.10.2022 12:10:29
 *  Author: kevin
 */ 


#ifndef CALCULATION_H_
#define CALCULATION_H_

typedef struct 
{
	
}st_calc;

extern st_calc gst_calc; 

void calc_leibniz( void *pvParameters ); 
void calc_bellard( void *pvParameters ); 

#endif /* CALCULATION_H_ */