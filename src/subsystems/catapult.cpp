#include "subsystems/catapult.hpp"
#include "api.h"
#include "sylib/sylib.hpp"

pros::Motor catapultMotor(10, pros::E_MOTOR_GEAR_RED, true);

pros::ADIPotentiometer potentiometer(8);
// If this conflicts with another
//  device, yur gonna be sad

Catapult::Catapult(){};
Catapult::~Catapult(){};
Catapult::Mode Catapult::current_mode = Mode::Loading;
int Catapult::target = 2300;
// fire is 2200

void Catapult::start(void *ignore) {
  catapultMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  int val;
  int prevVal;

  while (true) {
    double error;
    long int power;
    float derivative;
    float integral = 0;
    int prevError;
    int dT = 20;
    float kP = 700.0;
    float kI = 0.0;
    float kD = 70.0;

    error = (target - potentiometer.get_value()) * -1;

    derivative = error - prevError;
    prevError = error;

    integral = integral + error;
    if (error > 300) {
      integral = 0;
    }

    power = error * kP + integral * kI + derivative * kD;
    // the move voltage function doesn't like numbers greater than this
    if (std::fabs(error) > 12000) {
      power = 12000;
    }

    // speeen
    catapultMotor.move_voltage(power);

    printf("P: %f, I: %f, D: %f, Power: %li, Target: %i, Mode: %i\n", error,
           integral, derivative, power, target, current_mode);

    // change behavior based on mode
    switch (current_mode) {
    case Mode::Loading:
      target = 2300;
      if (error < 20) {
        current_mode = Mode::Ready;
      }
      break;
    case Mode::Ready:
      target = 2300;
      break;
    case Mode::Firing:
      target = 2000;
      // TODO: Fix this value
      if (error > 1000) {
        current_mode = Mode::Loading;
        printf("loading now\n");
      }
      break;
    default:
      target = 2300;
      printf("Invalid catapult mode\n");
      break;
    }

    std::uint32_t clock = sylib::millis();
    sylib::delay_until(&clock, 20);
  }
};

void Catapult::fire() {
  if (Catapult::current_mode == Mode::Ready) {
    Catapult::current_mode = Mode::Firing;
  } else {
    printf("Catapult not ready yet");
  }
}
