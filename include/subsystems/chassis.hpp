#ifndef CHASSIS_HPP
#define CHASSIS_HPP
#include <vector>

#include "api.h"

class Chassis {
 public:
  Chassis(std::vector<int8_t> left_ports, std::vector<int8_t> right_ports,
          pros::motor_gearset_e gearset = pros::E_MOTOR_GEAR_BLUE);
  ~Chassis();
  void move(int left, int right);
  void reverse();
  // PID functions
  double drive_curve_scale;

 private:
  // Devices
  pros::Motor_Group left_motors;
  pros::Motor_Group right_motors;
  // we could put the imu and tracking wheels here
  bool reversed;
  double calc_drive_curve(double joy_stick_position);
};
#endif
