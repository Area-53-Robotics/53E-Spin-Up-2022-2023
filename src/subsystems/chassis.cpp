#include "main.h"
#include "subsystems/chassis.hpp"
pros::Motor L1(2, E_MOTOR_GEAR_BLUE), L2(3, E_MOTOR_GEAR_BLUE),
    L3(4, E_MOTOR_GEAR_BLUE);
pros::Motor R1(2, E_MOTOR_GEAR_BLUE), R2(3, E_MOTOR_GEAR_BLUE),
    R3(4, E_MOTOR_GEAR_BLUE);

Chassis::Chassis() {}
