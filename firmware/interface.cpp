/*
 * interface.c
 *
 *  Created on: 8 cze 2016
 *      Author: buleks
 */
#include "interface.h"

void Interface::process(ESCDriver &esc, HX711 &hx)
{
	if (debugPort.read(&cli_char, 1))
	{
		if (cli_char == 'q')
		{
			increase_motor_speed();
		}
		else if (cli_char == 'a')
		{
			decrease_motor_speed();

		}
		else if (cli_char == 's')
		{
			esc_speed = 0;
		}
		else if (cli_char == 't')
		{
			hx.tare();
		}
		else if (cli_char == 'z')
		{
			hx.scale(111);
		}
		else if (cli_char == 'r')
		{
			hx.reset();
		}
		else if (cli_char == ' ')
		{
			esc_speed = 0;
		}

	}

}
