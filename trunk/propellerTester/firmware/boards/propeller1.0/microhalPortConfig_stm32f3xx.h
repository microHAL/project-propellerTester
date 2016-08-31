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
#ifndef _MICROHAL_MICROHALPORTCONFIG_STM32F3XX_H_
#define _MICROHAL_MICROHALPORTCONFIG_STM32F3XX_H_

constexpr static const uint32_t hse_value = 16000000;

//***********************************************************************************************//
//                                       configure interfaces //
//***********************************************************************************************//

// #define MICROHAL_USE_SERIAL_PORT1_POLLING
#define MICROHAL_USE_SERIAL_PORT1_INTERRUPT
#define MICROHAL_SERIAL_PORT1_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT1_RX_BUFFER_SIZE 128

#define MICROHAL_USE_SPI2_POLLING
#define MICROHAL_USE_SPI3_POLLING

#endif  // _MICROHAL_MICROHALPORTCONFIG_STM32F3XX_H_
