/*
 * rpm.c
 *
 *  Created on: 8 cze 2016
 *      Author: buleks
 */

#include "rpm.h"
#include "microhal_bsp.h"

extern RPM propeller_speed;

extern "C" void TIM8_BRK_TIM12_IRQHandler()
{
static	volatile uint32_t update_counter=0;
static	volatile uint32_t last;

	if(TIM12->SR&TIM_SR_UIF)
	{
		TIM12->SR &= ~TIM_SR_UIF;
		update_counter++;
	}
	else if(TIM12->SR&TIM_SR_CC1IF)//automatically cleared by read CCR1
	{
		uint32_t current;
		current = TIM12->CCR1;
		if(TIM12->SR&TIM_SR_CC1OF)
		{
			TIM12->SR&=~TIM_SR_CC1OF;
			debugPort.write("\n\r-------------------Overcapture error -------------------------\n\r");
		}
		current = current + update_counter*0xffff;
		propeller_speed.add_result(current-last);
		last=current;

	}

}
