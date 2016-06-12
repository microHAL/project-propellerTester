/**
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief      ESC driver
 *
 * @authors    Pawel Okas
 * created on: 11-04-2016
 * last modification: <DD-MM-YYYY>
 *
 * @copyright Copyright (c) 2016, microHAL
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this
 *        software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "escDriver.h"
#include "microhal.h"
#include "ports/STMicroelectronics/STM32F4xx/hdr/hdr_rcc.h"
#include "ports/STMicroelectronics/STM32F4xx/hdr/hdr_gpio.h"

ESCDriver::ESCDriver() {
    //    static void system_init(void) {
    //        NVIC_SetPriorityGrouping(3);
           // RCC->AHB1ENR |= /*RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN
             //       | RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOHEN | RCC_AHB1ENR_GPIOIEN;*/
            RCC_AHB1ENR_CRCEN_bb = 1;
            RCC_APB1ENR_TIM4EN_bb = 1;
    //        SysTick_Config(120000000 / 1000);

            GPIOB->MODER |= GPIO_MODER_ALT_value << (2 * 7);
            *((uint64_t*) GPIOB->AFR) |= GPIO_AFRx_AF2_value << (4 * 7);
            TIM4->PSC = 84-1;
            TIM4->ARR = 20000-1;
            TIM4->CCR2 = 0;
            TIM4->CCMR1 = TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
            TIM4->CCER = TIM_CCER_CC2E;
            //TIM4->BDTR = TIM_BDTR_MOE;
            TIM4->CR1 = TIM_CR1_CEN;

    //    }
}

ESCDriver::~ESCDriver() {

}

void ESCDriver::setOutput(Speed speed) {
	if(speed < 500)
	{
		speed = 500;
	}else
	if(speed > 2500)
	{
		speed = 2500;
	}
    TIM4->CCR2 = speed;
}
