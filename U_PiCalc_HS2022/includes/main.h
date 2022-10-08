/*
 * main.h
 *
 * Created: 08.10.2022 17:34:34
 *  Author: kevin
 */ 


#ifndef MAIN_H_
#define MAIN_H_


// Standard includes
#include <math.h>
#include <stdio.h>
#include <string.h>

//ATMega based includes
#include "avr_compiler.h"
#include "pmic_driver.h"
#include "TC_driver.h"
#include "clksys_driver.h"
#include "sleepConfig.h"
#include "port_driver.h"

//FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "stack_macros.h"

//Private includes
#include "mem_check.h"
#include "init.h"
#include "utils.h"
#include "errorHandler.h"

#include "NHD0420Driver.h"
#include "ButtonHandler.h"




#endif /* MAIN_H_ */