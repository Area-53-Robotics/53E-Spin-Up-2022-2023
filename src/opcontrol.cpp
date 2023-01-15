#include "main.h"
#include "pros/rtos.hpp"
#include "subsystems/catapult.hpp"
#include "cmath"

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

float driveCurve(float joystickPosition) {
  float a = 39.0873;
  float b = 1.01146;
  float c = -a;

  float driveVoltage = (a * pow(b, fabs(joystickPosition)) + c) * fabs(joystickPosition)/joystickPosition;
  printf("voltage = %f \n", driveVoltage);
  //controller.set_text("Voltage = %f \n", driveVoltage);
  return driveVoltage;
 }

void opcontrol() {
  //float cataTorque = catapultMotor.get_voltage();
  //printf("torque %f \n", cataTorque);


  // Catapult cata;

  bool isDriveReversed = false;
  bool intakeOn = false;
  // Set the LED strip to a gradient in HSV color space
  // that displays a full range of hues
  ledStrip.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);

  // Cycle the colors at speed 10
  ledStrip.cycle(*ledStrip, 10);
  // ledStrip.pulse(0xFF0000, 20, 10, 1, true, 20);
  // ledStrip.pulse(0xFF0000, 20, 10, 21, false, 40);

  while (true) {
    // Move drivetrain
    // TODO: run chassis in task
    printf("EncoderValue %i \n", leftEncoder.get_value());

    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT) && 
    controller.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) { 
      piston.set_value(1);}

    if (isDriveReversed == true) {

      leftMotors.move(driveCurve(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) * -1);
      rightMotors.move(driveCurve(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) * -1);

    } else {
      leftMotors.move(driveCurve(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)));
      rightMotors.move(driveCurve(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)));
    }

    if (controller.get_digital_new_press(
            E_CONTROLLER_DIGITAL_B)) { // drive switch
      controller.rumble(".");
      isDriveReversed = !isDriveReversed;
    }
    // Toggle Intake
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      intake.set_mode(Intake::Mode::SpinningRoller);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intake.set_mode(Intake::Mode::On);
    } else {
      intake.set_mode(Intake::Mode::Off);
    }

    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) { // launcher
      controller.rumble(".");
      catapult.fire();
    }
  }

  std::uint32_t clock = sylib::millis();
  sylib::delay_until(&clock, 20);
}
