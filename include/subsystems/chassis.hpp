#pragma once
#include <array>
#include <vector>

#include "api.h"

class Chassis {
 public:
  Chassis(std::vector<int8_t> left_ports, std::vector<int8_t> right_ports,
          std::array<int, 2> left_encoder_ports, int imu_port,
          pros::motor_gearset_e gearset = pros::E_MOTOR_GEAR_BLUE);
  ~Chassis();
  void move(int left, int right);
  void reverse();
  double drive_curve_scale;
  void calibrate_imu();
  // PID Function
  void move_pid(double target, int timeout = 100, int max_speed = 127);

 private:
  // Devices
  pros::Motor_Group left_motors;
  pros::Motor_Group right_motors;
  pros::Imu imu;
  pros::ADIEncoder left_encoder;

  bool reversed;
  double calc_drive_curve(double joy_stick_position);
};
