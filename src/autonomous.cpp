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

  ///////////////////////////////////////////////////////////
  Auton auton = Auton::Testing;

  if (auton == Auton::Testing) {  // target, timeout, max speed
    //chassis.move_pid(15, 5, 127);
    chassis.move(-20);
    delay(1000);
    chassis.move(0);
    intake.set_mode(Intake::Mode::Reverse);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    
    // chassis.turn_pid(90, 2, 150);
  }  // pid tuning true for cata forward, false for roller forward
}
