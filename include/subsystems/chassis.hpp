#ifndef CHASSIS_HPP
#define CHASSIS_HPP
#include "main.h"
extern pros::Motor L1, L2, L3, R1, R2, R3;

class Chassis {
public:
  Chassis();
  ~Chassis();
  void run();
  void drive();
};
#endif
