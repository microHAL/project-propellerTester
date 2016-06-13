/**
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief      propeller tester main file
 *
 * @authors    Pawel Okas
 * created on: 30-01-2016
 * last modification: <DD-MM-YYYY>
 *
 * @copyright Copyright (c) 2014, microHAL
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

#include "microhal.h"
#include "microhal_bsp.h"
#include "diagnostic/diagnostic.h"

#include "hx711/hx711.h"
#include "lis2dh12/lis2dh12.h"
#include "escDriver.h"
#include "rpm.h"
#include "interface.h"

using namespace microhal;
using namespace microhal::diagnostic;
using namespace std::literals::chrono_literals;


// lets create application diagnostic Channel
Diagnostic<LogLevel::Debug> appLog("APP: ", debugPort, EnableTimestamp | EnableFileName | EnableLevelName);

//currently used pins
//PB7-PPM out
//PA6- HX data
//PA7-HX CLK
//PE5- 56khz
//PA5-SPI
//PA6-SPI
//PA7-SPI
//PB10-SCL
//PB11-SDA
//PD8-TX
//PD9-RX
//PB14 - input capture TIM12 - propeller speed
int main() {
    debugPort.open(IODevice::ReadWrite);

    debugPort.write("\n\r------------------- Propeller tester -------------------------\n\r");

    appLog << lock << Debug  << "log " << unlock;

    HX711 force(hx711_SPI, miso_pin);
    force.setChannel(HX711::Channel::A_Gain_64);

  //  LIS2DH12 accelerometer(sensorI2C, LIS2DH12::I2C_ADDRESS_0);

    ESCDriver esc_controller;
    //RPM propeller_speed;
    Interface interface;

//    propeller_speed.Init();

    uint64_t hx_last = SysTickGetTime();
    uint64_t start;
    while (1)
    {
    	start = SysTickGetTime();
    	interface.process(esc_controller,force);
    	if(start-hx_last > 200)
    	{
    		hx_last = SysTickGetTime();
    		appLog << lock << Debug << force.getrawData ()<<"\n";
    	}


    }

    return 0;
}