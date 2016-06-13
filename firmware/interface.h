/*
 * interface.h
 *
 *  Created on: 8 cze 2016
 *      Author: buleks
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "microhal.h"
#include "microhal_bsp.h"
#include "diagnostic/diagnostic.h"

class Interface
{
private:
	char cli_char;
	ESCDriver::Speed esc_speed;
	ESCDriver::Speed speed_step;

	inline void increase_motor_speed()
	{
		esc_speed += 10;
		if (esc_speed > 2150)
			esc_speed = 2150;
	}
	inline void decrease_motor_speed()
	{
		esc_speed -= 10;
		if (esc_speed > 2500)
			esc_speed = 0;
	}
public:
	Interface()
	{
		esc_speed = 0;
		cli_char = 0;
		speed_step = 10;
	}

	void process(ESCDriver &esc, HX711 &hx);
	void show_data()
	{
//	  if (counter > 100000)
//	      {
//		counter = 0;
//		appLog << lock << Debug << "Measured force: " << force.getscaledData ()
//		    << "Raw/64" << endl << unlock;
//	      }
//	    //std::this_thread::sleep_for(100ms);
//
//		appLog << Debug << "Speed: " << (uint32_t) x << endl;
//				esc.setOutput (esc_speed);
	}
};

#endif /* INTERFACE_H_ */
