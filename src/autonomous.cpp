/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
#include "devices.h"
#include "main.h"
#include "pros/llemu.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "subsystems/chassis.hpp"
#include "utils/auton.hpp"

void autonomous() {
  printf("Started Auton\n");
  // Set the LED strip to a gradient in HSV color space
  // that displays a full range of hues
  ledStrip.gradient(0x30d15b, 0xFF0005, 0, 0, false, true);

  // Cycle the colors at speed 10
  ledStrip.cycle(*ledStrip, 10);

  Auton current_auton = Auton::FarSide;

  ///////////////////////////////////////////////////////////

  if (current_auton == Auton::Testing) {
    chassis.move(-20);
    delay(1000);
    chassis.move(0);
    intake.set_mode(Intake::Mode::Reverse);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(2000);
    chassis.move(20);
    delay(1300);
    chassis.turn_pid(90, 2);
    delay(1000);
    chassis.move_pid(-35, 3);
    // chassis.turn_pid(-15,2);
    catapult.fire();
    delay(1000);
    chassis.move_pid(35, 3);
    chassis.turn_pid(-53, 2);

    /*delay(1000);
    chassis.move_pid(45,2);
    chassis.turn_pid(20,2);
    intake.set_mode(Intake::Mode::Reverse);
    chassis.move(-20);
    delay(7000);
    chassis.move(0);
    intake.set_mode(Intake::Mode::Off);
    chassis.move(-20);
    delay(2000);
    intake.set_mode(Intake::Mode::Reverse);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(2000);
    //chassis.turn_pid(-45,2); */
    piston.set_value(true);
  }

  if (current_auton == Auton::DriverSide) {  // deploy on roller
    chassis.move(-20);
    delay(1000);
    chassis.move(0);
    intake.set_mode(Intake::Mode::Reverse);
    delay(60);
    intake.set_mode(Intake::Mode::Off);
    delay(2000);
    chassis.move(20);
    delay(1300);
    chassis.turn_pid(90, 2);
    delay(1000);
    catapult.fire();
    delay(1000);
    chassis.turn_pid(-45, 2);
  }

  if (current_auton == Auton::FarSide) {
    chassis.move_pid(6);
    chassis.turn_pid(90, 3);
    chassis.move_pid(23, 2);
    chassis.turn_pid(97, 2);
    delay(1000);

    chassis.move(-20);
    delay(3000);
    chassis.move(0);
    intake.set_mode(Intake::Mode::Reverse);
    //intake.set_mode(Intake::Mode::On);

    delay(60);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);

    chassis.move_pid(-5, 2);
    chassis.turn_pid(-90, 2);
    delay(1000);
    catapult.fire();
  }
}
