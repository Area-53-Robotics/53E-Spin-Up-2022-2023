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
#include "utils/auton.hpp"


//Auton auton = Auton::Testing;

void autonomous() {
  printf("Started Auton\n");
  // Set the LED strip to a gradient in HSV color space
  // that displays a full range of hues
  ledStrip.gradient(0x30d15b, 0xFF0005, 0, 0, false, true);

  // Cycle the colors at speed 10
  ledStrip.cycle(*ledStrip, 10);

  ///////////////////////////////////////////////////////////

  if (auton == Auton::Testing) {
    chassis.move(-20);
    delay(1000);
    chassis.move(0);
    intake.set_mode(Intake::Mode::Reverse);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    //chassis.turn_pid(90, 2, 150);
  }  // pid tuning true for cata forward, false for roller forward

  if (auton ==
      Auton::RollerShoot) {  // leftside auton (shoot discs to the right)
    chassis.move(20);
    delay(1000);
    chassis.move(0);
    intake.set_mode(Intake::Mode::On);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    chassis.move_pid(5);
    delay(1100);
    // turnPid(Right, 90);
    delay(1000);
    catapult.fire();
    delay(200);
    catapult.fire();
    delay(200);
    catapult.fire();
    delay(1000);
    // turnPid(Right, -90);
  }

  if (auton == Auton::MoveRoller) {  // leftside auton (move to roller)
    movePid(11, false);
    delay(1000);
    turnPid(Right, 90);
    delay(1000);
    movePid(34, false);  /////
    delay(1000);
    turnPid(Right, 80);
    delay(1000);
    chassis.move(30, 30);
    delay(1100);
    intake.set_mode(Intake::Mode::On);
    delay(140);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    chassis.move(-20, -20);
    delay(900);
    chassis.move(0, 0);
    delay(1000);
    // turnPid(Left, 90);
    delay(1000);
    catapult.fire();
    delay(200);
    catapult.fire();
    delay(200);
    catapult.fire();
  }

  if (auton == Auton::ProgSkills) {  // prog skills
    chassis.move(20, 20);
    delay(1000);
    chassis.move(0, 0);
    intake.set_mode(Intake::Mode::Reverse);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    movePid(5, true);
    delay(1100);
    turnPid(Right, 90);
    delay(1000);
    catapult.fire();
    delay(200);
    catapult.fire();
    delay(200);
    catapult.fire();
    delay(200);
    delay(1000);
    turnPid(Right, 90);
    delay(2000);
    chassis.move(40, 40);
    delay(1200);
    chassis.move(0, 0);

    delay(1000);
    turnPid(Left, 90);
    delay(1000);
    movePid(35, false);
    delay(1000);
    chassis.move(20, 20);
    delay(9000);
    chassis.move(0, 0);
    delay(1000);
    intake.set_mode(Intake::Mode::Reverse);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    chassis.move(-40, -40);
    delay(2000);
    chassis.move(0, 0);

    delay(2000);
    // turnPid(Left, 45);
    piston.set_value(1);
  }

  // delay(1000);
  // leftMotors.move_absolute(10, 50);
  // rightMotors.move_absolute(10,50);
  // delay(1000);
  // rightMotors.move_absolute(20,100);
}
