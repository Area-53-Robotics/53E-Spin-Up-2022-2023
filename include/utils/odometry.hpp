#pragma once
#include "api.h"

class Odometry {
 public:
  Odometry();
  ~Odometry();
  struct Coordinates {
    double x;
    double y;
  };
  Coordinates get_position();

 private:
  double x_coord;
  double y_coord;

  void run();

  pros::Task odom_task;

  pros::Imu imu;
  pros::ADIEncoder left_encoder;
  pros::ADIEncoder s_encoder;
};
