/*
 * interface.h
 *
 *  Created on: 8 cze 2016
 *      Author: buleks
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <bsp_propeller1.0.h>
#include "microhal.h"
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
		last_time = SysTickGetTime();
		current_time = SysTickGetTime();
	}

	void process();

private:
	uint64_t current_time;
	uint64_t last_time;
public:
	void show_log(uint64_t waitMS);
};

#endif /* INTERFACE_H_ */
