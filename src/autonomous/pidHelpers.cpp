#include "main.h"
#include "pros/rtos.hpp"





void movePid(double target, bool isReverse) {
  leftEncoder.reset();
  rightEncoder.reset();
  double distMovedLeft = 0;
  double distMovedRight = 0;
  //const float radius = 2.75;
  const float circ = 17.28;
  float kP = 10.0;
  float kI = 0.0;
  float kD = 0.0;
  float error_left = target;
  float error_right = target;
  long int power_left;
  long int power_right;

  float derivative_left;
  float derivative_rght;
  float prev_error_left;
  float prev_error_right;

  float integral_right;
  float intrgral_left;
  
  while (errorLeft > 0 && errorRight > 0) {
    distMovedLeft = (leftEncoder.get_value() * circ / 360);
    distMovedRight = (rightEncoder.get_value() * circ / 360);

    error_left = target - distMovedLeft;
    error_right = target - distMovedRight;


    derivative_left = error_left - prev_error_left;
    derivative_right = error_right - pre_error_right;

      power_left = (error * kP)  +  (derivative * kD);

    
    if (!isReverse) {
      leftMotors.move(power_left);
      rightMotors.move(power_right)
    } else {
      leftMotors.move(power_left * -1);
      rightMotor.move(power_right * -1);
    }

    pros::delay(20);
  }
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
  encoderMutex.give(); */

}

///////////////////////////////////////////////////////////////////////////////////

void turnPid(Direction direction, float turnValue) {
  float distTurned;
  leftEncoder.reset();
  rightEncoder.reset();

  
  if (direction == Left) {
    leftMotors.move_absolute(-turnValue * 5.5 * -1, 75);
    rightMotors.move_absolute(turnValue * 5.5, 75);
    distTurned = abs(leftEncoder.get_value());
    controller.print(0, 0, "distTurned =  %d", distTurned);

  } else if (direction == Right) {
    leftMotors.move_absolute(turnValue * 1 * 5.5, 75);
    rightMotors.move_absolute(turnValue * -1 * 5.5, 75);
    distTurned = abs(leftEncoder.get_value());
    controller.print(0, 0, "distTurned =  %d", distTurned);

  }
}