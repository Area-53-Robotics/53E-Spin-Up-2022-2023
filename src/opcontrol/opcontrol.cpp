#include "main.h"
#include "pros/rtos.hpp"

/*
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
////////////////////////////////////////////////////////////////////////////

void opcontrol() {
  bool isDriveReversed = false;
  bool intakeOn = false;
  // Set the LED strip to a gradient in HSV color space
  // that displays a full range of hues
  ledStrip.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);

  // Cycle the colors at speed 10
  ledStrip.cycle(*ledStrip, 10);

  while (true) {

    if (controller.get_digital(E_CONTROLLER_DIGITAL_A)) {
     piston.set_value(true);
     delay(5000);
     piston.set_value(false);
    }
    
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) { // roller
      // controller.rumble(".");
      rollerMotor.move(100);
    } else {
      rollerMotor.move(0);
    }

    if (controller.get_digital(E_CONTROLLER_DIGITAL_L1)) { // launcher
      // controller.rumble(".");
      launcherMotor.move(-127);
    } else {
      launcherMotor.move(0);
    }
    // Task launcherMoveTask(launcherMove);

    if (controller.get_digital_new_press(
            E_CONTROLLER_DIGITAL_B)) { // drive switch
      controller.rumble(".");
      isDriveReversed = !isDriveReversed;
    }

    if (isDriveReversed == 1) {
      leftMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) * -1);
      rightMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) * -1);
    } else {
      leftMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
      rightMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    }

    if (controller.get_digital_new_press(
            E_CONTROLLER_DIGITAL_R1)) { // intake + toggle
      controller.rumble(".");

      if (intakeOn == false) {
        rollerMotor.move(-127);
        intakeOn =
            true; //////////////////////////////////////////////////////// tune
      } else if (intakeOn == true) {
        rollerMotor.move(0);
        intakeOn = false;
      }
    }

    std::uint32_t clock = sylib::millis();
    sylib::delay_until(&clock, 20);
    // delay(20);
  }
}
