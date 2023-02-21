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
    {-11, -12, -13},
    // Right motor ports
    {1, 2, 3},
    // Left tracking wheel ports
    {7, 8},
    // IMU port
    10);

inline Catapult catapult(5, 'c');
inline Intake intake(6);
inline ADIDigitalIn limitSwitch(3);

// Currently, odom doesn't work
// inline Odometry odom;

namespace constants {
const float DRIVE_WHEEL_RADIUS = 3.25;
const float TRACKING_WHEEL_RADIUS = 2.75;
}  // namespace constants

inline Controller controller(E_CONTROLLER_MASTER);

// note to future generations: conlifting triports defs
// will make you want to kys

inline ADIEncoder leftEncoder(-1, -1);
inline ADIEncoder rightEncoder(-1, -1);
inline auto ledStrip = sylib::Addrled(22, 2, 40);
inline Mutex encoderMutex;

inline ADIDigitalOut piston(-1, false);  // see above

inline Imu imu_sensor(-1);

// 18 bod
