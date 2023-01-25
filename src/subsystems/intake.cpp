#include "subsystems/intake.hpp"

#include "api.h"
#include "pros/rtos.hpp"
// Constructor
Intake::Intake(int port)
    : intake_motor(port), intake_controller([this] { this->start(); }) {
  current_mode = Intake::Mode::Off;
};
// Destructor
Intake::~Intake(){};

void Intake::start() {
  while (true) {
    switch (current_mode) {
      case Mode::Off:
        intake_motor.move(0);
        break;
      case Mode::On:
        intake_motor.move(127);
        break;
      case Mode::Low:
        intake_motor.move(50);
        pros::delay(5000);
        current_mode = Mode::Off;
        break;
      case Mode::Reverse:
        intake_motor.move(-100);
        break;
      case Mode::SpinningRoller:
        intake_motor.move(-150);
        break;
      default:
        intake_motor.move(0);
        printf("invalid intake mode\n");
        break;
    }
    pros::delay(20);
  }
}
void Intake::set_mode(Intake::Mode target_mode) {
  Intake::current_mode = target_mode;
}
