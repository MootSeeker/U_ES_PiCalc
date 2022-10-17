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

//Module Includes
#include "ui.h"
#include "Calculation.h"


/*--- System Configuration ---------------------------------------------------
 * - Task Stack and Priority
 */

/* Task Stack Sizes
 * NOTE: Stack sizes in WORDs, Heap in BYTEs! */
#define TASK_STACK_CTL		( configMINIMAL_STACK_SIZE )
#define TASK_STACK_UI		( configMINIMAL_STACK_SIZE + 200 )
#define TASK_STACK_CALC		( configMINIMAL_STACK_SIZE )		// Global calculation stack size

/* Task Priorities */
#define TASK_PRIORITY_CTL	( 3 )
#define TASK_PRIORITY_UI	( 2 )
#define TASK_PRIORITY_CALC	( 1 )		// Global calculation priority

/* Task Handles */
#define CTL_TASK_HANDLE			( 0 )
#define UI_TASK_HANDLE			( 1 )
#define CALC_LBZ_TASK_HANDLE	( 2 )
#define CALC_BLD_TASK_HANDLE	( 3 )

/*--- Event Group -------------------------------------------------------------- */
EventGroupHandle_t xPiState;

/*--- Event Bits --------------------------------------------------------------- */
#define START_CALC		( 1U << 0UL )	// Start Calculation
#define STOP_CALC		( 1U << 1UL )	// Stop Calculation
#define RESET_CALC		( 1U << 2UL )	// Reset Calculation task  
#define CALC_SEL_LBZ	( 1U << 3UL )	// Select Calculation algorithm
#define CALC_SEL_BLD	( 1U << 4UL )	// Select Calculation algorithm
#define BIT5			( 1U << 5UL )	// unused
#define LBZ_STATE		( 1U << 6UL )	// Leibnitz Task state
#define BLD_STATE		( 1U << 7UL )	// Bellard Task state

#endif /* MAIN_H_ */