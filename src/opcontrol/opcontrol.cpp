
#include "main.h"
#include "pros/rtos.hpp"

void movePid(float target) {
  left1.set_zero_position(0);
  float kP = 7;
  float distMoved;
  float error = target;
  float power;

  while (abs(error) > 0) {
    distMoved = encoder.get_value() * 8.64; // cir. wheel
    error = target - distMoved;
    power = error * kP;

    if (error > 50 || power > 127) {
      power = 127;
    }

    leftMotors.move(power);
    rightMotors.move(power);

    controller.clear();
    std::cout << "Error: " << error << "-" << power << std::endl;
    // std::cout << "Power: " << power << std::endl;

    pros::delay(10);
  }
}

void launcherSpeed(float targetSpeed) {
  launcherMotor.move(targetSpeed);
  pros::delay(10000);
  launcherMotor.move(10);

  // left1.move(0);
  // left2.move(0);
  // right1.move(0);
  // right2.move(0);

  // controller.print(0, 0, "Error: %f", error);
}

#include "main.h"
#include "pros/misc.h"
#include <iostream>
#include <ostream>

/**
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

void spinUp() {
  int voltage = 0;

  while (voltage < 128) {
    launcherMotor.move(voltage);
    voltage += 1;
    pros::delay(200);
  }
}

void opcontrol() {

  while (true) {

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      Task spinUpTask(spinUp);
    }

    leftMotors.move(controller.get_analog(ANALOG_LEFT_Y));
    rightMotors.move(controller.get_analog(ANALOG_RIGHT_Y));

    if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      rollerMotor.move(-128);
    } else {
      rollerMotor.move(0);
    }
    std::cout << "encoder value" << encoder.get_value() << std::endl;

    pros::delay(20);
  }
}
