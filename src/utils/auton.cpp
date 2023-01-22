#include "utils/auton.hpp"
#include "api.h"
#include "devices.h"
#include <cmath>

void movePid(double target, bool isReverse) {
  imu_sensor.tare();

  double distMovedLeft = 0;
  const float RADIUS = 2.75;
  float kP = 700;
  float kI = 10;
  float kD = 10;
  float kR = 3;
  float driftVoltageLeft;
  float driftVoltageRight;
  float driftAngle;
  float error = target;
  float error_right = target;
  long int power_left;
  long int power_right;

  float derivative_left;
  float derivative_right;
  float prev_error_left;
  float prev_error_right;

  float integral_right;
  float integral_left;

  while (error > 1) {
    // printf("Left Error = %f \n", error_left);

    //printf("Error = %f \n", error_left);

    driftAngle = imu_sensor.get_rotation();

   /* if ( driftAngle < 0) {
      driftVoltageRight = kR * fabs(driftAngle);
    } 
    else if (driftAngle > 0) {
      driftVoltageLeft = kR * fabs(driftAngle);
    }
    else {
      driftVoltageLeft = 0;
      driftVoltageRight = 0; 

    } */

    // printf("Encoder Value = %i \n", leftEncoder.get_value());
    // printf("distMovedLeft = %f \n", distMovedLeft);
    // printf("-")

    distMovedLeft = ((leftEncoder.get_value() * 2 * M_PI * RADIUS / 360) * -1);

    error = target - fabs(distMovedLeft);
    printf("error = %f \n", error);

    // error_right = target - distMovedRight;

    // derivative_left = error_left - prev_error_left;
    // derivative_right = error_right - prev_error_right;

    power_left = (error * kP) + (derivative_left * kD);
    // power_right = (error_right * kP) + (derivative_right * kD);
    // printf("P: %f, I: %f, D: %f, Power: %li\n", error_left, integral_left,pto  //  derivative_left, power_left);
    float powerL = power_left - driftVoltageLeft;
    float powerR = power_left - driftVoltageRight;

    //printf("Power Left = %f || Power Right = %f \n", powerL, powerR);

    if (!isReverse) {
      leftMotors.move_voltage(power_left );
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
  imu_sensor.tare();
  printf("started");


  const float RADIUS = 2.75;
  float kP = 7;
  float kI = 1;
  float kD = 28;
  float prev_error;
  float degrees;
  float error = turnValue;
  long int power;

  float derivative;
  float prev_error_left;

  float integral_left;

  while (error > 0.1) {
    // printf("Left Error = %f \n", error_left);
    // printf("Encoder Value = %i \n", leftEncoder.get_value());
    // printf("distMovedLeft = %f \n", distMovedLeft);
    // printf("-")

    degrees = fabs(imu_sensor.get_rotation());
    prev_error = error;
    error = turnValue - degrees;
    derivative = error - prev_error;
    printf("error = %f  \n", error);

    power = (error * kP) + (derivative * kD);

    if (direction == Direction::Right) {
      leftMotors.move(power);
      rightMotors.move(power * -1);
    }
    else {
      leftMotors.move(power * -1) ;
      rightMotors.move(power);
    }
    

    if (power > 127) {
      power = 127;
    }
    delay(20);
  }
    leftMotors.move(0);
    rightMotors.move(0);
    printf("done \n");
}



