#include "subsystems/intake.hpp"
#include "api.h"

pros::Motor intakeMotor(10, pros::E_MOTOR_GEAR_RED, true);

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
            case Mode::Reverse:
                intakeMotor.move(-100);
                break;
            case Mode::SpinningRoller:
                intakeMotor.move(-127);
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