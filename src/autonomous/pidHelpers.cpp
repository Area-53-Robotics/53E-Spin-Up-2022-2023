#include "main.h"
#include "pros/rtos.hpp"
#include <cmath>

void moveBangBang(double target, bool isReverse) {
    //rightEncoder.reset();
  // double distMovedLeft;
  leftEncoder.reset();
  rightEncoder.reset();
  double distMovedLeft = 0;
  double distMovedRight = 0;
  float error = target;
  //const float radius = 2.75;
  const float circ = 17.28;
  float kP = 15;
  float kD = 15;
  float power;
  float derivative;
  float prevError;
  
  delay(10);

  while (error > 0) {
    distMovedLeft = (leftEncoder.get_value() * circ / 360);
    int error = target - distMovedLeft;
    controller.print(0, 0, "error =  %d", error);

//////////////////////////////////////////////////////////////////////////////
      derivative = error - prevError;
      prevError = error;

      power = error * kP  +  derivative * kD;
////////////////////////////////////////////////////////////////////////////// Derivatave moment moment
 
    // Absolute value of floating point number
      //controller.print(2, 0, "Error =  %d", );
    
    if (!isReverse) {

      leftMotors.move(error * kP);
      rightMotors.move(error * kP);


    } else {

      leftMotors.move(-error * kP);
      rightMotors.move(-error * kP);

    }

    delay(20);
  }
  
  leftMotors.move(0);
  rightMotors.move(0);
}
/*
void moveBangBangRight (double target, bool isReverse) {
  leftEncoder.reset();
  rightEncoder.reset();
  double distMovedLeft = 0;
  double distMovedRight = 0;
  //const float radius = 2.75;
  const float circ = 17.28;
  while (distMovedRight < target) {
    distMovedRight = fabs(rightEncoder.get_value() * circ / 360);
    controller.print(2, 0, "distMoved =  %d", distMovedRight);
 
    // Absolute value of floating point number
      //controller.print(2, 0, "Error =  %d", );
    
    if (!isReverse) {

      rightMotors.move(50);

    } else {
      
      rightMotors.move(-50);
    }

    delay(20);
  }

  leftMotors.move(0);
  rightMotors.move(0);
  }
  */








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
