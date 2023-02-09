#include "main.h"

#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems/catapult.hpp"
#include "sylib/system.hpp"
#include "utils/misc.hpp"

using namespace pros;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize();
  sylib::initialize();
  pros::lcd::set_text(1, ":)");
  controller.clear();
  printf("Calibrating IMU\n");
  chassis.calibrate_imu();
  printf("IMU Calibrated\n");

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() { printf("Disabled lmao\n"); }

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // auton selector goes here
}
