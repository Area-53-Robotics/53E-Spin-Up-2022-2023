#include "subsystems/catapult.hpp"

#include "api.h"
#include "pros/rtos.hpp"
#include "sylib/sylib.hpp"

Catapult::Catapult(int motor_port, int limit_switch_port)
    : motor(motor_port),
      limit_switch(limit_switch_port),
      catapult_controller([this] { this->run(); }) {
  Catapult::target = 1800;
  Catapult::current_mode = Mode::Loading;
  motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
};
Catapult::~Catapult(){};

void Catapult::run() {
  while (true) {
    if (!limit_switch.get_value()) {
      printf("Moving, pressed: %i\n", limit_switch.get_value());
      motor.move(127);
      current_mode = Mode::Loading;
    } else {
      printf("Ready\n");
      motor.move(0);
      current_mode = Mode::Ready;
    }

    if (current_mode == Mode::Firing) {
      while (limit_switch.get_value()) {
        printf("Firing\n");
        motor.move(127);
      }
      current_mode = Mode::Loading;
    }
    pros::delay(10);
  }
}

void Catapult::fire() {
  if (Catapult::current_mode == Mode::Ready) {
    Catapult::current_mode = Mode::Firing;
  } else {
    printf("Catapult not ready yet");
  }
}
