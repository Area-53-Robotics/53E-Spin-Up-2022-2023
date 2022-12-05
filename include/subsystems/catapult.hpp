#ifndef CATAPULT_HPP
#define CATAPULT_HPP
#include "api.h"
extern pros::Motor catapultMotor;
class Catapult {
public:
  Catapult();
  ~Catapult();
  static int target;
  static void start(void *ignore);
  void set_target(int target_target);
};
#endif
