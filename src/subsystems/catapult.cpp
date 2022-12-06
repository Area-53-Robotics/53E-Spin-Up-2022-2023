#include "subsystems/catapult.hpp"
#include "main.h"

pros::Motor catapultMotor(10, E_MOTOR_GEAR_RED, true);
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
    // starting val:
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
    delay(dT);
  }
};

void Catapult::set_mode(Catapult::Mode target_mode) {
  Catapult::current_mode = target_mode;
}
