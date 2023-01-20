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
#include "main.h"
#include "utils/auton.hpp"



void autonomous() {

  // Set the LED strip to a gradient in HSV color space
  // that displays a full range of hues
  ledStrip.gradient(0x30d15b, 0xFF0005, 0, 0, false, true);

  // Cycle the colors at speed 10
  ledStrip.cycle(*ledStrip, 10);

  // movePid(5, false);

  // moveBangBangLeft(100, true);
  // moveBangBangRight(100, true);

  //  moveBangBang(100,true);
  // turnBangBang(45);
  // 1 towards you
  // 2 away from you

  int x = 1; // 2 to roller 5 to shoot 0 PID
  Auton auton;

  if (x == 15) {
    movePid(150,false);

  } // pid tuning true for cata forward, false for roller forward

  if (auton == Auton::rollerShoot) { //leftside auton (shoot discs to the right)
    leftMotors.move(20);
    rightMotors.move(20);
    delay(1000);
    leftMotors.move(0);
    rightMotors.move(0);
    intake.set_mode(Intake::Mode::On);
    delay(120);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    movePid(5, true);
    delay(1100);
    leftMotors.move(40); // turn
    rightMotors.move(-40);
    delay(900);
    leftMotors.move(0);
    rightMotors.move(0);
    catapult.fire();
    delay(1000);
    leftMotors.move(-40); // turn
    rightMotors.move(40);
    delay(900);
    leftMotors.move(0); // turn
    rightMotors.move(0);
  }

  if (auton == Auton::moveRoller) { //leftside auton (move to roller)
  movePid(8,false);
  delay(1000);
  turnPid(Right,90);
  delay(1000);
  movePid(30,false);
  delay(1000);
  turnPid(Right,90);
  delay(1000);
  leftMotors.move(30);
  rightMotors.move(30);
  delay(1000);
  intake.set_mode(Intake::Mode::On);
  delay(120);
  intake.set_mode(Intake::Mode::Off);
  }
  

  if (auton == Auton::progSkills) { // prog skills
    leftMotors.move(40);
    rightMotors.move(40);
    delay(1000);
    leftMotors.move(0);
    rightMotors.move(0);
    intake.set_mode(Intake::Mode::Reverse);
    delay(400);
    intake.set_mode(Intake::Mode::Off);
    delay(1000);
    movePid(5, true);
    delay(1100);
    leftMotors.move(40); // turn
    rightMotors.move(-40);
    delay(850);
    leftMotors.move(0);
    rightMotors.move(0);
    catapult.fire();
    delay(1000);
    leftMotors.move(-40); // turn
    rightMotors.move(40);
    delay(450);
    leftMotors.move(0); // turn
    rightMotors.move(0);
    delay(1000);
    leftMotors.move(-25); // turn
    rightMotors.move(-25);
    delay(1500);
    leftMotors.move(0); // turn
    rightMotors.move(0);
    delay(1000);
    piston.set_value(1);
  }

  

  // delay(1000);
  // leftMotors.move_absolute(10, 50);
  // rightMotors.move_absolute(10,50);
  // delay(1000);
  // rightMotors.move_absolute(20,100);
}
