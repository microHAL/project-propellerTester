/*
 * interface.c
 *
 *  Created on: 8 cze 2016
 *      Author: buleks
 */
#include "escDriver.h"
#include "hx711/hx711.h"
#include "interface.h"
#include "rpm.h"

using namespace microhal::diagnostic;

extern Diagnostic<LogLevel::Debug> appLog;
extern HX711 force;
extern ESCDriver esc_controller;
extern RPM propeller_speed;

void Interface::show_log(uint64_t waitMS)
{
		current_time = SysTickGetTime();
	   	if (current_time - last_time > waitMS)
		{
	   		last_time = SysTickGetTime();
//	   		appLog << lock;
//			appLog << lock << Debug << force.getscaledData() ;
//			appLog << Debug << " Speed: " << (uint32_t) esc_speed ;
//			appLog << Debug << " RPM: "<<propeller_speed.getlast()<< "\n";
//	   	//	appLog << Debug <<propeller_speed.getlast()<< "\n";
//			appLog<< unlock;

	   		appLog << lock;
			appLog << lock << Debug << force.getscaledData() ;
			appLog << Debug << ";" << (uint32_t) esc_speed ;
			appLog << Debug << ";"<<propeller_speed.getlast()<< "\n";
	   	//	appLog << Debug <<propeller_speed.getlast()<< "\n";
			appLog<< unlock;

		}
//	  if (counter > 100000)
//	      {
//		counter = 0;
//		appLog << lock << Debug << "Measured force: " << force.getscaledData ()
//		    << "Raw/64" << endl << unlock;
//	      }

}

void Interface::process()
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
			force.tare();
		}
		else if (cli_char == 'z')
		{
			force.scale(111);
		}
		else if (cli_char == 'r')
		{
			force.reset();
		}
		else if (cli_char == ' ')
		{
			esc_speed = 0;
		}
		esc_speed = esc_controller.setOutput (esc_speed);
	}

}
