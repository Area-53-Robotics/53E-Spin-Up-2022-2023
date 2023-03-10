#include "subsystems/chassis.hpp"
#include <cmath>
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

void Chassis::tank(int left, int right) {
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

void Chassis::move(int left, int right) {
  left_motors.move(left);
  right_motors.move(right);
}
// OVERLOADING ENGAGE!!!!
void Chassis::move(int input) {
  left_motors.move(input);
  right_motors.move(input);
};

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
  float delay_time = 20;
  double time_elapsed = 0;
  int start_time = pros::millis();
  int end_time = start_time + 1000 * timeout;
  int time_at_target = 0;
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

  const float kp = 11;
  const float ki = 0;
  const float kd = 12;

  const float kp_theta = 3;
  const float ki_theta = 0;
  const float kd_theta = 6;

  while (true) {
    // Calculate PID values for distance distance traveled
    dist_traveled =
        left_encoder.get_value() * ((2 * M_PI / 360) * WHEEL_RADIUS);
    error = target - dist_traveled;
    integral = integral + error * delay_time;
    derivative = error - prev_error;
    prev_error = error;

    // Calculate PID values for rotation
    error_theta = imu.get_rotation();
    integral_theta = integral_theta + error_theta * delay_time;
    derivative_theta = error_theta - prev_error_theta;
    prev_error_theta = error_theta;
    power_theta = (error_theta * kp_theta) + (derivative_theta * kd_theta);

    if (power_theta > max_speed) {
      integral_theta = 0;
    }

    power = (error * kp) + (integral * ki) + (derivative * kd);

    // Correct the power based on rotation (we want to move in a straight line)
    left_power = (power + power_theta);
    right_power = (power - power_theta);

    if (left_power > max_speed) {
      left_power = max_speed;
    }
    if (right_power > max_speed) {
      right_power = max_speed;
    }

    move(left_power * -1, right_power * -1);

    // check exit conditions
    if (error < 0.5 && error > -0.5) {
      // The chassis has to spend time at the target to make sure it doesn't
      // overshoot.
      time_at_target += delay_time;
      if (time_at_target > 500) {  // 500 Milliseconds
        printf("move_pid met the target\n");
        break;
      }
    } else {
      time_at_target = 0;
    }

    // Timeout
    if (pros::millis() > end_time) {
      printf("turn_pid timed out\n");
      break;
    }

    printf("%f, %f, %f, %f\n", power, error * kp, integral * ki,
           derivative * kd);

    // printf("%f, %f, %f, %f\n", power_theta, error_theta * kp_theta,
    // integral_theta * ki_theta, derivative_theta * kd_theta);

    pros::delay(delay_time);
    time_elapsed += delay_time;
  }

  move(0, 0);
}

void Chassis::turn_pid(double target, int timeout, int max_speed) {
  imu.tare();
  left_encoder.reset();
  const float WHEEL_RADIUS = 2.75 / 2;  // Inches
  float delay_time = 10;
  double end_time = pros::millis() + timeout * 1000;  // Convert to seconds
  double time_elapsed = 0;
  double time_at_target = 0;
  double power;
  bool is_target_negative = false;

  if (target < 0) {
    is_target_negative = true;
  }

  double dist_traveled;
  double error;
  double prev_error = error;

  double integral;

  double derivative;

  const double kp = 0.8;
  const double ki = 0.0008;
  const double kd = 0.5;

  while (true) {
    // Calculate PID values for distance distance traveled
    dist_traveled = imu.get_rotation();
    error = fabs(target) - dist_traveled;
    integral = integral + error * delay_time;
    derivative = error - prev_error;
    prev_error = error;


    power = (error * kp) + (integral * ki) + (derivative * kd);

    if (power > max_speed) {
      power = max_speed;
    }

    if (power > 50) {
      integral = 0;
    }

    if (!is_target_negative) {
      move(power, -power);
    } else {
      move(-power, power);
    }

    // check exit conditions
    if (error < 0.5 && error > -0.5) {
      // The chassis has to spend time at the target to make sure it doesn't
      // overshoot.
      time_at_target += delay_time;
      if (time_at_target > 500) {  // 500 Milliseconds
        printf("turn_pid met the target\n");
        break;
      }
    } else {
      time_at_target = 0;
    }

    // Timeout
    if (pros::millis() > end_time) {
      printf("turn_pid timed out\n");
      break;
    }

    // printf("%f, %f, %f, %f\n", power, error * kp, integral * ki,
    // derivative * kd);

    pros::delay(delay_time);  // Milliseconds
  }

  move(0, 0);
}
