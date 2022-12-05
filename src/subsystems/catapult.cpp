#include "subsystems/catapult.hpp"
#include "main.h"

pros::Motor catapultMotor(10, E_MOTOR_GEAR_RED, true);
// pros::ADIPotentiometer potentiometer(8); //If this conflicts with another
// device, yur gonna be sad

Catapult::Catapult(){};
Catapult::~Catapult(){};
int Catapult::target = 2000;

void Catapult::set_target(int target_target) { target = target_target; }
void Catapult::start(void *ignore) {
  int val;
  int prevVal;

  while (true) {
    double error;
    long int power;
    float derivative;
    float integral = 0;
    int prevError;
    int dT = 40;
    float kP = 210.0;
    float kI = 0.9;
    float kD = 100.0;
    // starting val:
    error = (target - potentiometer.get_value()) * -1;

    derivative = error - prevError;
    prevError = error;

    integral = integral + error;
    if (integral > 2000) {
      integral = 2000;
    } else if (integral < 0) {
      integral = 0;
    }
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
