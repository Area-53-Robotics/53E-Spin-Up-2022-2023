#ifndef INTAKE_HPP
#define INTAKE_HPP
#include "api.h"
class Intake {
 public:
  Intake(int port);
  ~Intake();
  enum class Mode {
    On,
    Low,
    Off,
    SpinningRoller,
    Reverse,
  };

  pros::Task intake_controller;
  pros::Motor intake_motor;
  Mode current_mode;
  void start();
  void set_mode(Mode target_mode);
};
#endif
