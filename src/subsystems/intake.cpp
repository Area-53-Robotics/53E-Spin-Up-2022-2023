#include "subsystems/intake.hpp"
#include "api.h"
#include "pros/rtos.hpp"

pros::Motor intakeMotor(20, pros::E_MOTOR_GEAR_GREEN);

Intake::Mode Intake::current_mode = Intake::Mode::Off;

Intake::Intake(){};
Intake::~Intake(){};
void Intake::start(void *ignore) {
  while (true) {
    switch (current_mode) {
    case Mode::Off:
      intakeMotor.move(0);
      break;
    case Mode::On:
      intakeMotor.move(127);
      break;
    case Mode::Low:
      intakeMotor.move(50);
      pros::delay(5000);
      current_mode = Mode::Off;
      break;
    case Mode::Reverse:
      intakeMotor.move(-100);
      break;
    case Mode::SpinningRoller:
      intakeMotor.move(-150);
      break;
    default:
      intakeMotor.move(0);
      printf("invalid intake mode\n");
      break;
    }
    pros::delay(20);
  }
}
void Intake::set_mode(Intake::Mode target_mode) {
  Intake::current_mode = target_mode;
}
