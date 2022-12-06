#ifndef CATAPULT_HPP
#define CATAPULT_HPP
#include "api.h"
extern pros::Motor catapultMotor;
class Catapult {
public:
  Catapult();
  ~Catapult();
  enum class Mode {
    Firing,
    Loading,
    Ready,
  };
  static Mode current_mode;
  static int target;
  static void start(void *ignore);
  static void fire();
};
#endif
