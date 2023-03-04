#include "main.h"
#include "utils/auton.hpp"
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


void disabled() {
  Auton auton = Auton::None;
  int autonState = 0;

  while (true) {
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
      autonState = autonState + 1;
    }

    if (autonState == 0) {Auton auton = Auton::None;
    pros::lcd::set_text(1, "No Auton");
    pros::lcd::set_text(4, "Does literally nothing :/");
    }

    if (autonState == 1) {Auton auton = Auton::Testing;
    pros::lcd::set_text(1, "Testing");
    pros::lcd::set_text(4, "Last minute testing moment");
    }

    if (autonState == 2) {Auton auton = Auton::MoveRoller;
    pros::lcd::set_text(1, "MoveRoller");
    pros::lcd::set_text(4, "Moves to roller, changes roller, shoots in low goal");
    pros::lcd::set_text(5,"Instructions: Position to the left of the roller on the right edge of the tile with the cata touching the wall, PRELOAD AND PNEUMATICS");
    }
    if (autonState == 3) {Auton auton = Auton::RollerShoot;
    pros::lcd::set_text(1, "RollerShoot");
    pros::lcd::set_text(4, "Deploys on roller, changes roller, turns right, shoots in low goal");
    pros::lcd::set_text(5,"Instructions: Deploy on roller, you better not mess this up, PRE LOAD AND PNEUMATICS");}

    if (autonState == 4) {Auton auton = Auton::ProgSkills;
    pros::lcd::set_text(1, "ProgSkills");
    pros::lcd::set_text(4, "Changes roller, turns, fires low goal, turns, changes other roller ");
    pros::lcd::set_text(5,"Instructions: Deploy on roller, PRE LOAD AND PNEUMATICS");
    if (autonState == 5) {}
    if (autonState > 4) {autonState = 0;}
  }
}
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
