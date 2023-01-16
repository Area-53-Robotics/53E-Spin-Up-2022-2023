#include "utils/auton.hpp"
#include "api.h"
#include "devices.h"
#include <cmath>

void movePid(double target, bool isReverse) {

  leftEncoder.reset();
  rightEncoder.reset();
  double distMovedLeft = 0;
  double distMovedRight = 0;
  const float RADIUS = 2.75;
  float kP = 700;
  float kI = 10;
  float kD = 10;
  float error_left = target;
  float error_right = target;
  long int power_left;
  long int power_right;

  float derivative_left;
  float derivative_right;
  float prev_error_left;
  float prev_error_right;

  float integral_right;
  float integral_left;

  while (error_left > 1) {
    // printf("Left Error = %f \n", error_left);

    printf("Error = %f \n", error_left);
    // printf("Encoder Value = %i \n", leftEncoder.get_value());
    // printf("distMovedLeft = %f \n", distMovedLeft);
    // printf("-")

    distMovedLeft = ((leftEncoder.get_value() * 2 * M_PI * RADIUS / 360) * -1);
    distMovedRight = (rightEncoder.get_value() * 2 * M_PI * RADIUS / 360);

    error_left = target - fabs(distMovedLeft);
    // error_right = target - distMovedRight;

    // derivative_left = error_left - prev_error_left;
    // derivative_right = error_right - prev_error_right;

    power_left = (error_left * kP) + (derivative_left * kD);
    // power_right = (error_right * kP) + (derivative_right * kD);
    // printf("P: %f, I: %f, D: %f, Power: %li\n", error_left, integral_left,
    //  derivative_left, power_left);

    if (!isReverse) {
      leftMotors.move_voltage(power_left);
      rightMotors.move_voltage(power_left);
    } else {
      leftMotors.move_voltage(power_left * -1);
      rightMotors.move_voltage(power_left * -1);
    }

    pros::delay(20);
  }
  printf("moved to target\n");
  leftMotors.move(0);
  rightMotors.move(0);
}

void turnBangBang(double target) {
  encoderMutex.take();
  leftEncoder.reset();
  rightEncoder.reset();
  double distMoved = 0;

  leftMotors.move(target);
  rightMotors.move(target * -1);

  while (distMoved <= target) {
    distMoved = (leftEncoder.get_value() - rightEncoder.get_value()) / 3.3 +
                3.3 * M_PI / 180;
    leftMotors.move(-30);
    rightMotors.move(30);
    printf("distMoved: %f\n", distMoved);
    delay(50);
  }
  leftMotors.move(0);
  rightMotors.move(0);
  encoderMutex.give();
}

///////////////////////////////////////////////////////////////////////////////////

void turnPid(Direction direction, float turnValue) {

  float distTurned;
  leftEncoder.reset();
  rightEncoder.reset();
  left2.tare_position();
  right2.tare_position();

  float leftValue;
  float rightValue;
  float change;
  float degrees;
  int dirValue;

  while (degrees < turnValue) {
    leftValue = left2.get_position();
    rightValue = right2.get_position();

    // printf("Left = %f \n", leftValue);
    // printf("Right = %f \n", rightValue);

    change = (leftValue - rightValue) / 12; // distance across;
    degrees = fabs((change * (180 / M_PI)));

    printf("change = %f \n", change);

    printf("degrees = %f \n", degrees);
    printf("left = %f \n", leftValue);
    printf("right = %f \n", rightValue);
    printf("turnValue = %f \n", turnValue);

    leftMotors.move(-50);
    rightMotors.move(50);

    // printf("degrees = %f \n", degrees);
    // printf("target = %f \n", turnValue);

    /* switch (direction) {
       case Left:
       leftMotors.move(-50);
       rightMotors.move(50);
       printf("degrees = %f \n", degrees);
       break;

       case Right:
       leftMotors.move(50);
       rightMotors.move(-50);
       printf("degrees = %f \n", degrees);
       break;
     } */
    delay(20);
  }
}
