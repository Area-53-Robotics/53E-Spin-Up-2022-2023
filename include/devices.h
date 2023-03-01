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
    {-12, -13, -14},
    // Right motor ports
    {18, 19, 20},
    // Left tracking wheel ports
    {-1, -1},
    // IMU port
    15);

inline Catapult catapult(17, 'f');
inline Intake intake(16);

// Currently, odom doesn't work
// inline Odometry odom;

inline Controller controller(E_CONTROLLER_MASTER);

// note to future generations: conlifting triports defs
// will make you want to kys

inline ADIEncoder leftEncoder(-1, -1);
inline ADIEncoder rightEncoder(-1, -1);
inline auto ledStrip = sylib::Addrled(22, 8, 40);
inline Mutex encoderMutex;

inline ADIDigitalOut piston('b', false);  // see above

// 18 bod
