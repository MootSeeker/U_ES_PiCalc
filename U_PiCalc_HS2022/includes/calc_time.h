/**
 * @file   calc_time.h
 *
 * @brief  Brief description of the content of template.h
 * @author Kevin Perillo, Juventus Techniker Schule
 * @date   22.10.2022 - first implementation
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


#ifndef CALC_TIME_H_
#define CALC_TIME_H_

//...........................................................................................................
/**
 * @brief   Structure to save measured time
 */
typedef struct  
{
	uint32_t calc_time;
	uint32_t start_time;
	uint32_t stop_time;
}st_calc_time;

//...........................................................................................................
/**
 * @brief  Extern definition of the global structure "gst_calc_time" 
 */
extern st_calc_time gst_calc_time; 

//...........................................................................................................
/**
 * @brief   Calculation task of pi with Leibniz
 * @param   void *pvParameters
 * @retval  none
 */
void calcTimeHandlerTask( void *pvParameters ); 

#endif /* CALC_TIME_H_ */