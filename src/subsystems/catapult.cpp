#include "subsystems/catapult.hpp"
#include "api.h"

pros::Motor catapultMotor(10, pros::E_MOTOR_GEAR_RED, true);
pros::ADIPotentiometer potentiometer(8); // see above

// pros::ADIPotentiometer potentiometer(8); //If this conflicts with another
// device, yur gonna be sad

Catapult::Catapult(){};
Catapult::~Catapult(){};
Catapult::Mode Catapult::current_mode = Mode::Loading;
int Catapult::target = 2300;
//fire is 2200

void Catapult::start(void *ignore) {
  int val;
  int prevVal;

  while (true) {
    double error;
    long int power;
    float derivative;
    float integral = 0;
    int prevError;
    int dT = 20;
    float kP = 250.0;
    float kI = 50.0;
    float kD = 50.0;
    switch (current_mode) {
      case Mode::Loading: 
        target = 2300;
        break;
      case Mode::Ready:
        target = 2300;
        break;
      case Mode::Firing:
        target = 2000;
        break;
      default:
        target = 2300;
        printf("Invalid catapult mode\n");
        break;
    }
    error = (target - potentiometer.get_value()) * -1;

    derivative = error - prevError;
    prevError = error;

    integral = integral + error;
    power = error * kP + integral * kI + derivative * kD;

    if (std::fabs(error) > 12000) {
      power = 12000;
    }

    catapultMotor.move_voltage(power);
    printf("P: %f, I: %f, D: %f, Power: %li, Target: %i\n", error, integral, derivative,
           power, target);
    pros::delay(dT);
  }
};

void Catapult::fire() {
  if (Catapult::current_mode == Mode::Ready) {
    Catapult::current_mode = Mode::Firing;
  }
}
