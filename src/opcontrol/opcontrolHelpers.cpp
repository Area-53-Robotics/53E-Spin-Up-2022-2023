#include "main.h"
#include "pros/rtos.hpp"

void spinUp() {
  // TODO:
  //- gradually increase speed from halt to midpoint
  //- gradually decrease speed to target
  //- emergency stop
  // halt ---- midpoint ---- target
  // in units of velocity
  int dT = 10;
  int target = 70;
  float kP = 7;
  float distMoved;
  float error = target;
  float power = 0;

  while (true) {
    launcherEncoder.reset();
    //target in degrees per milisecond
    target = launcherEncoder.get_value() / dT;
    launcherMotor.move(power);


    pros::delay(dT);
  }
}
/*
void spinUp() {
  int voltage = 0;

  while (voltage < 128) {
    launcherMotor.move(voltage);
    voltage += 1;
    pros::delay(200);
  }
}
*/
