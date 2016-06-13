/*
 * rpm.c
 *
 *  Created on: 8 cze 2016
 *      Author: buleks
 */

#include "rpm.h"

volatile uint32_t update_counter;
volatile uint16_t captured;

extern "C" void TIM8_BRK_TIM12_IRQHandler()
{
	if(TIM12->SR&TIM_SR_UIF)
	{
		TIM12->SR &= ~TIM_SR_UIF;
		update_counter++;
	}
	else if(TIM12->SR&TIM_SR_CC1IF)//automatically cleared by read CCR1
	{
		captured = TIM12->CCR1;
	}

}
