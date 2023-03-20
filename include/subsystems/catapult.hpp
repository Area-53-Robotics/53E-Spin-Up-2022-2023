#ifndef CATAPULT_HPP
#define CATAPULT_HPP
#include "api.h"
#include "pros/adi.hpp"

class Catapult {
 public:
  Catapult(int motor_port, int limit_switch_port);
  ~Catapult();
  enum class Mode {
    Firing,
    Loading,
    Ready,
    Disabled,
  };
  void run();
  void toggle_disable();
  void fire();

 private:
  // Devices
  pros::Motor motor;
  pros::Task catapult_controller;
  pros::ADIDigitalIn limit_switch;

  Mode current_mode;
  int target;
};
#endif
