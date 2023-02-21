#include "subsystems/catapult.hpp"

#include "api.h"
#include "devices.h"
#include "pros/rtos.hpp"
#include "sylib/sylib.hpp"

Catapult::Catapult(int motor_port, int limit_switch_port)
    : motor(motor_port, true),
      limit_switch(limit_switch_port),
      catapult_controller([this] { this->run(); }) {
  Catapult::target = 1800;
  Catapult::current_mode = Mode::Loading;
  motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
};
Catapult::~Catapult(){};

void Catapult::run() {
  while (true) {
    if (current_mode == Mode::Loading || current_mode == Mode::Ready) {
      if (!limit_switch.get_value()) {
        motor.move(127);
      } else {
        motor.move(0);
        current_mode = Mode::Ready;
      }
    }
    if (current_mode == Mode::Firing) {
      if (limit_switch.get_value()) {
        motor.move(127);
      } else {
        current_mode = Mode::Loading;
      }
    }

    pros::delay(50);
  }
}

void Catapult::fire() {
  if (Catapult::current_mode == Mode::Ready) {
    Catapult::current_mode = Mode::Firing;
  } else {
    printf("Catapult not ready yet");
  }
}
