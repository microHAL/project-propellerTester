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
#include "bsp.h"
#include "microhal.h"
#include "hx711.h"

using namespace microhal;
using namespace diagnostic;
using namespace std::literals::chrono_literals;

int main() {
    bsp::debugPort.open(SerialPort::ReadWrite);
    bsp::debugPort.setBaudRate(SerialPort::Baud115200);
    bsp::debugPort.setDataBits(SerialPort::Data8);
    bsp::debugPort.setStopBits(SerialPort::OneStop);
    bsp::debugPort.setParity(SerialPort::NoParity);

    bsp::debugPort.write("\n\r------------------- Propeller Tester v0.1.0 -------------------------\n\r");

    diagChannel.setOutputDevice(bsp::debugPort);

	ExternalInterrupt::init();

	HX711 hx711(bsp::hx711::spi, bsp::hx711::miso);
	hx711.setChannel(HX711::Channel::A_Gain_64);

    while (1) {
    	diagChannel << lock << Debug << "HX711: " << hx711.getrawData() << endl <<unlock;
    	std::this_thread::sleep_for(1s);
    }
    return 0;
}
