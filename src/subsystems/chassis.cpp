#include "subsystems/chassis.hpp"

#include <vector>

// Chassis::Chassis(int port)
//: intake_motor(port), intake_controller([this] { this->start(); }) {
// current_mode = Intake::Mode::Off;
//};

Chassis::Chassis(std::vector<int8_t> left_ports,
                 std::vector<int8_t> right_ports, pros::motor_gearset_e gearset)
    : left_motors(left_ports), right_motors(right_ports) {
  left_motors.set_gearing(gearset);
  right_motors.set_gearing(gearset);
}
Chassis::~Chassis(){};

void Chassis::move(int left, int right) {
  left = calc_drive_curve(left);
  right = calc_drive_curve(right);
  if (reversed) {
    left_motors.move(left * -1);
    right_motors.move(right * -1);
  } else {
    left_motors.move(left);
    right_motors.move(right);
  }
}

void Chassis::reverse() { reversed = !reversed; }

double Chassis::calc_drive_curve(double joy_stick_position) {
  if (drive_curve_scale != 0) {
    return (powf(2.718, -(drive_curve_scale / 10)) +
            powf(2.718, (fabs(joy_stick_position) - 127) / 10) *
                (1 - powf(2.718, -(drive_curve_scale / 10)))) *
           joy_stick_position;
  }
  return joy_stick_position;
}
