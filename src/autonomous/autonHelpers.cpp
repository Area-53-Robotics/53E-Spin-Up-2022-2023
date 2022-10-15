#include "main.h"

void movePid(float target) {
  left1.set_zero_position(0);
  float kP = 7;
  float distMoved;
  float error = target;
  float power;

  while (abs(error) > 0) {
    distMoved = encoder.get_value() * 8.64; // cir. wheel
    error = target - distMoved;
    power = error * kP;

    if (error > 50 || power > 127) {
      power = 127;
    }

    leftMotors.move(power);
    rightMotors.move(power);

    controller.clear();
    std::cout << "Error: " << error << "-" << power << std::endl;
    // std::cout << "Power: " << power << std::endl;

    pros::delay(10);
  }
}
