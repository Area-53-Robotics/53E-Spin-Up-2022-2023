#include "cmath"
#include "main.h"
#include "subsystems/catapult.hpp"
#include "subsystems/chassis.hpp"

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
//////////////////////////////////////////////////////////////////////////

void opcontrol() {
  int joystick_left_y, joystick_right_y;
  double drive_curve_scale = 0;
  // Set the LED strip to a gradient in HSV color space
  // that displays a full range of hues
  ledStrip.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);

  // Cycle the colors at speed 10
  ledStrip.cycle(*ledStrip, 10);

  while (true) {
    joystick_left_y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    joystick_right_y = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    chassis.tank(joystick_left_y, joystick_right_y);

    /*
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
      drive_curve_scale--;
      controller.rumble(".");
    } else if (controller.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      drive_curve_scale++;
      controller.rumble(".");
    }
    */

    chassis.drive_curve_scale = drive_curve_scale;

    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
      controller.rumble(".");
      chassis.reverse();
    }
    // Toggle Intake
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      intake.set_mode(Intake::Mode::SpinningRoller);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intake.set_mode(Intake::Mode::On);
    } else {
      intake.set_mode(Intake::Mode::Off);
    }
    // Fire cata
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
      controller.rumble(".");
      catapult.fire();
    }
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT) &&
        controller.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
      controller.rumble(".");
      piston.set_value(1);
    }

    std::uint32_t clock = sylib::millis();
    sylib::delay_until(&clock, 20);
  }
}
