#include "subsystems/catapult.hpp"

#include "api.h"
#include "sylib/sylib.hpp"

Catapult::Catapult(int motor_port, int potentiometer_port)
    : catapult_motor(motor_port),
      potentiometer(potentiometer_port),
      catapult_controller([this] { this->run(); }) {
  Catapult::target = 1800;
  Catapult::current_mode = Mode::Loading;
  catapult_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
};
Catapult::~Catapult(){};

void Catapult::run() {
  int val;
  int prevVal;

  while (true) {
    double error;

    error = (target - potentiometer.get_value()) * -1;
    if (error > 40 and catapult_motor.get_torque() < 100) {
      catapult_motor.move(127);
    } else {
      catapult_motor.move(0);
    }

    // change behavior based on mode
    switch (current_mode) {
      case Mode::Loading:
        target = 2000;  // 2100
        if (error < 50) {
          current_mode = Mode::Ready;
        }
        break;
      case Mode::Ready:
        // target = 3000;
        break;
      case Mode::Firing:
        target = 0;
        if (error > 1000) {
          current_mode = Mode::Loading;
          printf("loading now\n");
        }
        break;
      default:
        printf("Invalid catapult mode\n");
        break;
    }

    std::uint32_t clock = sylib::millis();
    sylib::delay_until(&clock, 40);
  }
};

void Catapult::fire() {
  if (Catapult::current_mode == Mode::Ready) {
    Catapult::current_mode = Mode::Firing;
  } else {
    printf("Catapult not ready yet");
  }
}
