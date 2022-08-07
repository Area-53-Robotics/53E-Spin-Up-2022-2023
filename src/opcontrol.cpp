#include "main.h"

<<<<<<< HEAD

void opcontrol() {
=======
void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	pros::Motor left1(10,E_MOTOR_GEARSET_36,true);
	pros::Motor right1(5,E_MOTOR_GEARSET_36);
	pros::Motor left2(8,E_MOTOR_GEARSET_36,true);
	pros::Motor right2(11,E_MOTOR_GEARSET_36);


	
>>>>>>> 542002a (added multi-file system)

	while (true) {
		left1.move(controller.get_analog(ANALOG_LEFT_Y));
		left2.move(controller.get_analog(ANALOG_LEFT_Y));
		right1.move(controller.get_analog(ANALOG_RIGHT_Y));
		right2.move(controller.get_analog(ANALOG_RIGHT_Y));
<<<<<<< HEAD
		left3.move(controller.get_analog(ANALOG_LEFT_Y));
		right3.move(controller.get_analog(ANALOG_RIGHT_Y));

=======
>>>>>>> 542002a (added multi-file system)

		pros::delay(20); 
		
	}
}
