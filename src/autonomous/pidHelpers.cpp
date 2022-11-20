#include "main.h"

void moveBangBang(float target) {
  float distMoved;

  while (true) {

    distMoved = right1.get_position() * 0.6 * 8.64;

    controller.print(1, 1, "distMoved = ", distMoved);

    delay(20);

  }
}














void movePid(float target) {
  float kP = 7;
  float distMoved;
  float error = target;
  float power;

  while (abs(error) > 0.2)

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

void turnPid(cooler_direction direction, float turnValue) {
  if (direction == Left) {
    leftMotors.move_absolute(turnValue * -1, 127);
    rightMotors.move_absolute(turnValue, 127);
  } else if (direction == Right) {
    leftMotors.move_absolute(turnValue, 127);
    rightMotors.move_absolute(turnValue * -1, 127);
  }
}