/**
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief
 *
 * @authors    buleks
 * created on: 19-07-2016
 * last modification: 19-07-2016
 *
 * @copyright Copyright (c) 2016, microHAL
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
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

/* **************************************************************************************************************************************************
 * INCLUDES
 */
#include <bsp_propeller1.0.h>
#include "microhal.h"

using namespace microhal;
using namespace std::literals::chrono_literals;

int main() {
    led.set();
    led.reset();

    Core::SetUSART1ClockSource(Core::UsartClockSource::PCLK);
    debugPort.open(SerialPort::ReadWrite);
    debugPort.setBaudRate(SerialPort::Baud115200);
    debugPort.setDataBits(SerialPort::Data8);
    debugPort.setStopBits(SerialPort::OneStop);
    debugPort.setParity(SerialPort::NoParity);

    debugPort.write("\n\rhello\n\r");

    size_t availableBytes;
    char buffer[100];

    std::this_thread::sleep_for(10s);

    while (1) {
        //        std::this_thread::sleep_for(10ms);
        //        led.toggle();
        availableBytes = debugPort.getAvailableBytes();
        // if some data available
        if (availableBytes != 0) {
            // prevent buffer overflow
            if (availableBytes > sizeof(buffer)) {
                availableBytes = sizeof(buffer);
            }
            // make echo
            debugPort.read(buffer, availableBytes);
            debugPort.write(buffer, availableBytes);
        }
    }
    return 0;
}
