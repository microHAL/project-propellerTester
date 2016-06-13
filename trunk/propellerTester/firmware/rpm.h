/*
 * rpm.h
 *
 *  Created on: 8 cze 2016
 *      Author: buleks
 */

#ifndef RPM_H_
#define RPM_H_

#include "microhal.h"
#include "ports/STMicroelectronics/STM32F4xx/hdr/hdr_rcc.h"
#include "ports/STMicroelectronics/STM32F4xx/hdr/hdr_gpio.h"


class RPM
{
private:
	static const int buffer_size = 10;
	float buffer[buffer_size];
	int32_t buffer_index;


	inline void Init56khzoutput()
	{
		//PE5 - 56khz output
		//tim9_ch1
		RCC_AHB1ENR_GPIOEEN_bb = 1;
		RCC_APB2ENR_TIM9EN_bb = 1;
		GPIOE->MODER |= GPIO_MODER_ALT_value << (2 * 5);
		GPIOE->AFR[0] |= GPIO_AFRx_AF3_value << (4*5);
		TIM9->PSC = 42-1;
		TIM9->ARR = 72 -1;
		TIM9->CCR1 =(72-1)/2;
		TIM9->CCMR1 = TIM_CCMR1_OC1M_1| TIM_CCMR1_OC1M_2;
		TIM9->CCER = TIM_CCER_CC1E;
		TIM9->CR1 = TIM_CR1_CEN;
	}

	inline void InitInputCapture()
	{
		  RCC_APB1ENR_TIM12EN_bb = 1;
		  GPIOB->MODER |= GPIO_MODER_ALT_value << (2 * 14);//PB14
		  GPIOB->AFR[1] |= GPIO_AFRx_AF9_value <<(4*(14-8)); //TIM12_CH1
		  TIM12->PSC = 1;
		  TIM12->ARR=65535;
		  //CC1S=01
		  //ICF1=0 to disable input filter
		  //ICPS=0 to divide by 1
		  TIM12->CCMR1 = ((TIM9->CCMR1 & (~TIM_CCMR1_IC1F))&(~TIM_CCMR1_IC1PSC))| 0x01 ;

		  TIM12->CCER = TIM_CCER_CC1P&(0<<1);//rising edge
		  TIM12->CCER = TIM_CCER_CC1P&(1<<1);//falling edge
		  TIM12->CCER |= TIM_CCER_CC1E;
		  //TIM12->DIER |= TIM_DIER_CC1IE;
		  TIM12->DIER |= TIM_DIER_UIE;
		  //select polarity for TI1FP1(CC1P/CC1NP)

		  //result in
		  //;


		 // TIM_SR_CC1OF; // jesli capture wystapi w przerwaniu, kasowane tlyko poprzez zapis 0
		  NVIC_ClearPendingIRQ(TIM8_BRK_TIM12_IRQn);
		  NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 0x00);
		  NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);

		  TIM12->CR1 = TIM_CR1_CEN;

	}
	void add_result()
	{

	}
public:
	RPM() {buffer_index = 0; }
	inline void Init()
	{
		Init56khzoutput();
		InitInputCapture();
	}
	float getlast();
	float getaverage();

};



#endif /* RPM_H_ */
