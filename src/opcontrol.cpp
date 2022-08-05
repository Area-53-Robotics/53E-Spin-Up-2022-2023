#include "main.h"

void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	pros::Motor left1(1,E_MOTOR_GEARSET_36);
	pros::Motor right1(2,E_MOTOR_GEARSET_36);
	pros::Motor left2(3,E_MOTOR_GEARSET_36);
	pros::Motor right2(4,E_MOTOR_GEARSET_36);


	

	while (true) {
		left1.move(controller.get_analog(ANALOG_LEFT_Y));
		left2.move(controller.get_analog(ANALOG_LEFT_Y));
		right1.move(controller.get_analog(ANALOG_RIGHT_Y));
		right2.move(controller.get_analog(ANALOG_RIGHT_Y));

		pros::delay(20); 
		
	}
}
