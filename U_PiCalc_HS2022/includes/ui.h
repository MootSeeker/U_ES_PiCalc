/**
 * @file   ui.h
 *
 * @brief  Brief description of the content of template.h
 * @author Kevin Perillo, Juventus Techniker Schule
 * @date   09.10.2022 - first implementation
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


#ifndef UI_H_
#define UI_H_

//...........................................................................................................
/**
 * @brief  Enumeration of different fine state machine modes
 */
typedef enum 
{
	MODE_IDLE, 
	MODE_CALC_LBZ, 
	MODE_CALC_NLK, 
	
}enDisplayMode;

//...........................................................................................................
/**
 * @brief   Ui Handler - Controlling Display
 * @param   void *pvParameters
 * @retval  none
 */
void ui_handler( void *pvParameters ); 

//...........................................................................................................
/**
 * @brief   Led Handler - Controlling onboard LED
 * @param   void *pvParameters
 * @retval  none
 */
void led_handler( void *pvParameters ); 

#endif /* UI_H_ */