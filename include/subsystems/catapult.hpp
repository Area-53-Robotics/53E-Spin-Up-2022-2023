#ifndef CATAPULT_HPP
#define CATAPULT_HPP
#include "api.h"

class Catapult {
 public:
  Catapult(int motor_port, int potentiometer_port);
  ~Catapult();
  enum class Mode {
    Firing,
    Loading,
    Ready,
  };
  void run();
  void fire();

 private:
  pros::Task catapult_controller;
  // Devices
  pros::ADIPotentiometer potentiometer;
  pros::Motor catapult_motor;

  Mode current_mode;
  int target;
};
#endif
