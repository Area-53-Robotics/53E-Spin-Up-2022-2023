#pragma once
#include "api.h"
#include "subsystems/catapult.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "sylib/sylib.hpp"
#include "utils/odometry.hpp"

using namespace pros;

inline Chassis chassis(
    // Left motor ports
    {16, 17, 18},
    // Right motor ports
    {6, 7, 8},
    // Left tracking wheel ports
    {7, 8},
    // IMU port
    2);
inline Catapult catapult(10, 3);
inline Intake intake(20);

// Currently, odom doesn't work
// inline Odometry odom;

namespace constants {
const float DRIVE_WHEEL_RADIUS = 3.25;
const float TRACKING_WHEEL_RADIUS = 2.75;
}  // namespace constants

inline Controller controller(E_CONTROLLER_MASTER);

inline Motor left1(16, E_MOTOR_GEAR_BLUE, true);
inline Motor left2(17, E_MOTOR_GEAR_BLUE, true);
inline Motor left3(18, E_MOTOR_GEAR_BLUE, true);

inline Motor right1(6, E_MOTOR_GEAR_BLUE);
inline Motor right2(7, E_MOTOR_GEAR_BLUE);
inline Motor right3(8, E_MOTOR_GEAR_BLUE);

inline Motor rollerMotor(20, E_MOTOR_GEAR_GREEN, true);

inline Motor catapultMotor(10, E_MOTOR_GEAR_RED, true);

inline Mutex leftMotorMutex;
inline Mutex rightMotorMutex;
inline pros::Motor_Group leftMotors({left1, left2, left3});
inline pros::Motor_Group rightMotors({right1, right2, right3});

// note to future generations: conlifting triports defs
// will make you want to kys

inline ADIEncoder leftEncoder(-1, -1);
inline ADIEncoder rightEncoder(-1, -1);
inline auto ledStrip = sylib::Addrled(22, 2, 40);
inline Mutex encoderMutex;

inline ADIDigitalOut piston(1, false);  // see above

inline Imu imu_sensor(-1);

// 18 bod
