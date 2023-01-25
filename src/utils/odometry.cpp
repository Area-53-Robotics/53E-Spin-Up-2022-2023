#include "utils/odometry.hpp"

#include "api.h"
#include "pros/rtos.hpp"

Odometry::Odometry()
    : imu(2),
      left_encoder('e', 'f'),
      s_encoder('c', 'd'),
      odom_task([this] { this->run(); }) {
  printf("Odom constructed\n");
};

Odometry::~Odometry() {
  // Kills the task
  printf("odom task killed\n");
  odom_task.remove();
};

void Odometry::run() {
  imu.reset(true);
  printf("Starting odom task\n");
  // Constants
  const double WHEEL_RADIUS = 2.75;

  // starting angle
  const double THETA_START = M_PI;

  const double LEFT_TRACKING_RADIUS = 3.25;
  const double S_TRACKING_RADIUS = 2.0;

  double left_position;
  double s_position;

  double left_prev_position;
  double s_prev_position;

  double delta_l;
  double delta_s;

  double total_delta_l;
  double total_delta_s;

  double current_absolute_orientation;

  double delta_theta;
  double previous_theta;

  double delta_x_local;
  double delta_y_local;

  double avg_theta_for_arc;

  double delta_x_global;
  double delta_y_global;

  while (true) {
    // Encoders output in degrees

    left_position = s_encoder.get_value();
    s_position = s_encoder.get_value();

    delta_l =
        ((left_position - left_prev_position) * M_PI / 180) * WHEEL_RADIUS;
    delta_s = ((s_position - s_prev_position) * M_PI / 180) * WHEEL_RADIUS;

    // Log previous values in degrees
    left_prev_position = left_position;
    s_prev_position = s_position;

    // Totol movement on both encoders in inches
    total_delta_l += delta_l;
    total_delta_s = delta_s;

    // Radians
    current_absolute_orientation = (360 - imu.get_heading() * M_PI / 180);

    delta_theta = current_absolute_orientation - previous_theta;

    previous_theta = current_absolute_orientation;

    // If we didn't rotate, we moved in a straight line
    if (delta_theta == 0) {
      delta_x_local = delta_l;
      delta_y_local = delta_l;
    } else {
      delta_x_local =
          2 * sin(delta_theta) * ((delta_s / delta_theta) + S_TRACKING_RADIUS);
      delta_y_local = 2 * sin(delta_theta) *
                      ((delta_l / delta_theta) + LEFT_TRACKING_RADIUS);
    }

    // calculate average angle of the robot during it's arc in radians
    avg_theta_for_arc = current_absolute_orientation - (delta_theta / 2);

    delta_x_global = (delta_y_local * cos(avg_theta_for_arc)) -
                     (delta_x_local * sin(avg_theta_for_arc));

    delta_y_global = (delta_y_local * sin(avg_theta_for_arc)) -
                     (delta_x_local * cos(avg_theta_for_arc));

    // wraps angles back around if they ever go under 0 or over 2 pi
    while (current_absolute_orientation >= 0) {
      current_absolute_orientation -= 2 * M_PI;
    }

    while (current_absolute_orientation < 0) {
      current_absolute_orientation += 2 * M_PI;
    }

    // update global coordinates
    x_coord += delta_x_global;
    y_coord += delta_y_global;

    // delay to give other tasks time to do things
    pros::delay(10);
  }
}

Odometry::Coordinates Odometry::get_position() {
  Odometry::Coordinates coordinates;
  coordinates.x = x_coord;
  coordinates.y = y_coord;

  return coordinates;
}
