#include "main.h"
#include "encoder.cpp"

void opcontrol() {

	while (true) {
		left1.move(controller.get_analog(ANALOG_LEFT_Y));
		left2.move(controller.get_analog(ANALOG_LEFT_Y));
		right1.move(controller.get_analog(ANALOG_RIGHT_Y));
		right2.move(controller.get_analog(ANALOG_RIGHT_Y));
		left3.move(controller.get_analog(ANALOG_LEFT_Y));
		right3.move(controller.get_analog(ANALOG_RIGHT_Y));


		pros::delay(20); 
		
	}
}
