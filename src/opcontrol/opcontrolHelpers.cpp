#include "main.h"
#include "pros/rtos.hpp"

void spinUp() {
  // TODO:
  //- gradually increase speed from halt to midpoint
  //- gradually decrease speed to target
  //- emergency stop
  // halt ---- midpoint ---- target
  int target = 70; // degrees per milisecond
  float currentVelocity;
  float kP = 2000;
  float kI;
  float kD;
  int dT = 200;
  float error = target;
  float power = 0; // sets starting power

 /* while (power <= 63) {
    launcherMotor.move(power);
    currentVelocity = launcherEncoder.get_value() / dT;
    power += 1;
    printf("Power: %f, Velocity: %f\n", power, currentVelocity);
    pros::delay(dT);
  }
  /*
  while (true) {
    launcherEncoder.reset();
    // target in degrees per milisecond
    currentVelocity = launcherEncoder.get_value() / dT;
    if (power <= 12000) {
      error = target - currentVelocity;
      power = error * kP;
    }

    launcherMotor.move_voltage(power);
    pros::delay(dT);
  }
  */
}
