/**
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief
 *
 * @authors buleks
 * created on: <18-07-2016>
 * last modification: <DD-MM-YYYY>
 *
 * @copyright Copyright (c) 2015, microHAL
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *        2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 *           documentation and/or other materials provided with the
 * distribution.
 *     3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 *        software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "bsp_propeller1.0.h"

using namespace microhal;
// using namespace stm32f3xx;

static const uint32_t hse_value = 16000000;

GPIO led(led_pin, GPIO::Direction::Output);

static void inline clockDefault(void) {
    /* Reset the RCC clock configuration to the default reset state ------------*/
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset CFGR register */
    RCC->CFGR &= 0xF87FC00C;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;

    /* Reset PREDIV1[3:0] bits */
    RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

    /* Reset USARTSW[1:0], I2CSW and TIMs bits */
    RCC->CFGR3 &= (uint32_t)0xFF00FCCC;

    /* Disable all interrupts */
    RCC->CIR = 0x00000000;
}

static void inline clockConfig(void) {
    // AHB  72MHZ
    // APB1 36mhz
    // APB2 72MHZ

    uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != 10));

    // hse can not start
    if (RCC->CR & RCC_CR_HSERDY == 0) {
        led.set();
        while (1) {
        }
    } else {
        /* Enable Prefetch Buffer and set Flash Latency */
        FLASH->ACR = FLASH_ACR_PRFTBE | (uint32_t)FLASH_ACR_LATENCY_2;

        // AHB prescaler
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

        // APB2
        /* PCLK2 = HCLK / 1 */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

        // APB1
        /* PCLK1 = HCLK / 2 */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

        /* PLL configuration */
        RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        // RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL16);
        // RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR_PLLXTPRE_HSE_PREDIV_DIV1 | RCC_CFGR_PLLMUL9);
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR_PLLXTPRE_HSE_PREDIV_DIV1 | RCC_CFGR_PLLMUL3);
        // RCC->CFGR2 |= RCC_CFGR2_PREDIV_DIV4;
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL) {
        }
    }
}
void hardwareConfig(void) {
    // Core::pll_start(8000000, 168000000);
    Core::fpu_enable();
    clockDefault();
    clockConfig();

    SCB->VTOR = 0x00000000;  // offset for vector table

    stm32f3xx::IOManager::routeSerial<1, Txd, stm32f3xx::GPIO::PortA, 9>();
    stm32f3xx::IOManager::routeSerial<1, Rxd, stm32f3xx::GPIO::PortA, 10>();

    SysTick_Config(168000000 / 1000);
}

volatile uint64_t SysTick_time = 0;

extern "C" void SysTick_Handler(void) {
    SysTick_time++;
}

uint64_t SysTickGetTime(void) {
    return SysTick_time;
}
