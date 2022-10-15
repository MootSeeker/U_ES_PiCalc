/*
 * ui.h
 *
 * Created: 09.10.2022 11:45:32
 *  Author: kevin
 */ 


#ifndef UI_H_
#define UI_H_


typedef enum 
{
	MODE_IDLE, 
	MODE_CALC_LBZ, 
	MODE_CALC_BLD, 
	
}enDisplayMode;


void ui_handler( void *pvParameters ); 

#endif /* UI_H_ */