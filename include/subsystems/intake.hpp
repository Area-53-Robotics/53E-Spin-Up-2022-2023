#ifndef INTAKE_HPP
#define INTAKE_HPP
#include "api.h"
extern pros::Motor intakeMotor;
class Intake {
public:
  Intake();
  ~Intake();
  enum class Mode {
    On,
    Off,
    SpinningRoller,
    Reverse,
  };
  static Mode current_mode;
  static void start(void *ignore);
  static void set_mode(Mode target_mode);
};
#endif