#pragma once
#include "api.h"
#include "subsystems/catapult.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "sylib/sylib.hpp"
#include "utils/odometry.hpp"

using namespace pros;

// Conflicting ADI port definitions will cause a deadlock of some sort

inline Chassis chassis(
    // Left motor ports
    {-12, -13, -14},
    // Right motor ports
    {18, 19, 20},
    // Left tracking wheel ports
    {'c', 'd'},
    // IMU port
    15);

inline Catapult catapult(17, 'f');
inline Intake intake(16);

// Currently, odom doesn't work
// inline Odometry odom;

inline Controller controller(E_CONTROLLER_MASTER);

inline auto ledStrip = sylib::Addrled(22, 'e', 19);

inline ADIDigitalOut piston('a', false);  // see above

// 18 bod
