#include "main.h"
#include "pros/rtos.hpp"
#include <cmath>

void moveBangBang(double target, bool isReverse) {
  // double distMovedLeft;
  double distMovedRight = 0;
  const float radius = 2.75;
  // leftEncoder.reset();
  //rightEncoder.reset();

  while (distMovedRight < target) {

    distMovedRight = fabs(rightEncoder.get_value());// * radius * M_PI /
                         // 360); // Absolute value of floating point number
    if (!isReverse) {

      leftMotors.move(50);
      rightMotors.move(50);

    } else {

      rightMotors.move(-50);
      leftMotors.move(-50);
    }
      controller.print(0, 0, "distMoved =  %d", distMovedRight);
      //controller.print(2, 0, "Error =  %d", );

      
    printf("Dist: %f Target: %f\n", distMovedRight, target);
    delay(20);
  }
  leftMotors.move(0);
  rightMotors.move(0);
}









void turnBangBang(double target) {
  encoderMutex.take();
  leftEncoder.reset();
  rightEncoder.reset();
  double distMoved = 0;

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

void movePid(float target) {
  float kP = 7;
  float distMoved;
  float error = target;
  float power;

  while (fabs(error) > 0.2)

  // small = 36
  // big = 60
  {
    distMoved = right1.get_position() * 0.6 * 8.64; // cir. wheel
    error = target - distMoved;
    power = error * kP;

    leftMotors.move(power);
    rightMotors.move(power);

    if (error > 50 || power < 127) {
      power = 127;
    }

    // controller.clear();
    //  std::cout << "Error: " << error << "-" << power << std::endl;
    // std::cout << "Power: " << power << std::endl;

    delay(10);
  }
}

///////////////////////////////////////////////////////////////////////////////////

void turnPid(Direction direction, float turnValue) {
  if (direction == Left) {
    leftMotors.move_absolute(turnValue * -1, 127);
    rightMotors.move_absolute(turnValue, 127);
  } else if (direction == Right) {
    leftMotors.move_absolute(turnValue, 127);
    rightMotors.move_absolute(turnValue * -1, 127);
  }
}
