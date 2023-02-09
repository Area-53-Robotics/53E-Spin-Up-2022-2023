#include "subsystems/chassis.hpp"

#include <array>
#include <vector>

#include "pros/rtos.hpp"

Chassis::Chassis(std::vector<int8_t> left_ports,
                 std::vector<int8_t> right_ports,
                 std::array<int, 2> left_encoder_ports, int imu_port,
                 pros::motor_gearset_e gearset)
    : left_motors(left_ports),
      right_motors(right_ports),
      left_encoder(left_encoder_ports[0], left_encoder_ports[1], true),
      imu(imu_port),
      drive_curve_scale(7) {
  left_motors.set_gearing(gearset);
  right_motors.set_gearing(gearset);
}
Chassis::~Chassis(){};

void Chassis::move(int left, int right) {
  left = calc_drive_curve(left);
  right = calc_drive_curve(right);
  if (reversed) {
    left_motors.move(right * -1);
    right_motors.move(left * -1);
  } else {
    left_motors.move(left);
    right_motors.move(right);
  }
}

void Chassis::reverse() { reversed = !reversed; }

void Chassis::calibrate_imu() { imu.reset(true); }

double Chassis::calc_drive_curve(double joy_stick_position) {
  if (drive_curve_scale != 0) {
    return (powf(2.718, -(drive_curve_scale / 10)) +
            powf(2.718, (fabs(joy_stick_position) - 127) / 10) *
                (1 - powf(2.718, -(drive_curve_scale / 10)))) *
           joy_stick_position;
  }
  return joy_stick_position;
}

void Chassis::move_pid(double target, int timeout, int max_speed) {
  imu.tare();
  left_encoder.reset();
  const float WHEEL_RADIUS = 2.75 / 2;  // Inches
  bool exited = false;
  float delay_time = 10;
  double time_elapsed = 0;
  double power, left_power, right_power, power_theta;

  double dist_traveled;
  double error;
  double prev_error = error;

  double error_theta;
  double prev_error_theta = error_theta;

  double integral;
  double integral_theta;

  double derivative;
  double derivative_theta;

  const float kp = 40;
  const float ki = 0;
  const float kd = 1;

  const float kp_theta = 8;
  const float ki_theta = 0;
  const float kd_theta = 0;

  while (!exited) {
    // Calculate PID values for distance distance traveled
    dist_traveled =
        left_encoder.get_value() * ((2 * M_PI / 360) * WHEEL_RADIUS);
    error = target - dist_traveled;
    integral = integral + error * delay_time;
    derivative = error - prev_error;

    // Calculate PID values for rotation
    error_theta = imu.get_rotation();
    integral_theta = integral_theta + error_theta * delay_time;
    derivative_theta = error_theta - prev_error_theta;
    power_theta = (error_theta * kp_theta) + (derivative_theta * kd_theta);

    power = (error * kp) + (derivative * kd);

    // Correct the power based on rotation (we want to move in a straight line)
    left_power = power - power_theta;
    right_power = power + power_theta;

    if (left_power > max_speed) {
      left_power = max_speed;
    }
    if (right_power > max_speed) {
      right_power = max_speed;
    }

    move(left_power, right_power);

    pros::delay(delay_time);
    time_elapsed += delay_time;
    // printf("%f %f %f\n", error, integral, derivative);
    printf("%f, %f, %f, %f\n", power_theta, error_theta, integral_theta,
           derivative_theta);
  }

  move(0, 0);
}
