#pragma once
#include <vector>

#include "api.h"

class Chassis {
 public:
  Chassis(std::vector<int8_t> left_ports, std::vector<int8_t> right_ports,
          int left_encoder_port, int imu_port,
          pros::motor_gearset_e gearset = pros::E_MOTOR_GEAR_BLUE);
  ~Chassis();
  void move(int left, int right);
  void reverse();
  double drive_curve_scale;
  void calibrate_imu();

 private:
  // Devices
  pros::Motor_Group left_motors;
  pros::Motor_Group right_motors;
  pros::Imu imu;
  pros::ADIEncoder left_encoder;

  bool reversed;
  double calc_drive_curve(double joy_stick_position);
};
