/**
 * @file   main.h
 *
 * @brief  Brief description of the content of template.h
 * @author Kevin Perillo, Juventus Techniker Schule
 * @date   08.10.2022 - first implementation
 * @version 1.0.0
 * 
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright (c) 2022 Juventus Techniker Schule
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
#include "calc_time.h"


/*--- System Configuration ---------------------------------------------------
 * - Task Stack and Priority
 */

/* Task Stack Sizes
 * NOTE: Stack sizes in WORDs, Heap in BYTEs! */
#define TASK_STACK_CTL		( configMINIMAL_STACK_SIZE )
#define TASK_STACK_UI		( configMINIMAL_STACK_SIZE + 100 )
#define TASK_STACK_CALC		( configMINIMAL_STACK_SIZE + 100 )		// Global calculation stack size
#define TASK_STACK_TIME		( configMINIMAL_STACK_SIZE )
#define TASK_STACK_LED		( configMINIMAL_STACK_SIZE )

/* Task Priorities */
#define TASK_PRIORITY_CTL	( 3 )
#define TASK_PRIORITY_UI	( 2 )
#define TASK_PRIORITY_CALC	( 1 )		// Global calculation priority
#define TASK_PRIORITY_TIME	( 1 )
#define TASK_PRIORITY_LED	( 1 )

/* Task Handles */
#define CTL_TASK_HANDLE			( 0 )
#define UI_TASK_HANDLE			( 1 )
#define CALC_LBZ_TASK_HANDLE	( 2 )
#define CALC_NLK_TASK_HANDLE	( 3 )
#define CALC_TIME_HANDLE		( 4 )
#define LED_TASK_HANDLE			( 5 )

/*--- Event Group -------------------------------------------------------------- */
EventGroupHandle_t xPiState;

/*--- Event Bits --------------------------------------------------------------- */
#define START_CALC		( 1U << 0UL )	// Start Calculation
#define STOP_CALC		( 1U << 1UL )	// Stop Calculation
#define RESET_CALC		( 1U << 2UL )	// Reset Calculation task  
#define CALC_SEL_LBZ	( 1U << 3UL )	// Select Calculation algorithm
#define CALC_SEL_NLK	( 1U << 4UL )	// Select Calculation algorithm
#define BIT5			( 1U << 5UL )	// unused
#define LBZ_STATE		( 1U << 6UL )	// Leibnitz Task state
#define NLK_STATE		( 1U << 7UL )	// Nilakantha Task state

#endif /* MAIN_H_ */