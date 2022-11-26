#include "api.h"
#include "pros/rtos.hpp"
#include "sylib/sylib.hpp"
using namespace pros;

namespace constants {
const float driveWheelRadius = 3.25;
const float trackingWheelRadius = 2.75;
} // namespace constants

inline Controller controller(E_CONTROLLER_MASTER);

inline Motor left1(14, E_MOTOR_GEAR_BLUE, true);
inline Motor left2(15, E_MOTOR_GEAR_BLUE, true);
inline Motor left3(16, E_MOTOR_GEAR_BLUE, true);

inline Motor right1(8, E_MOTOR_GEAR_BLUE);
inline Motor right2(9, E_MOTOR_GEAR_BLUE);
inline Motor right3(10, E_MOTOR_GEAR_BLUE);

inline Motor rollerMotor(11, E_MOTOR_GEAR_GREEN, true);

inline Motor launcherMotor(2, E_MOTOR_GEAR_BLUE);

inline pros::Motor_Group leftMotors({left1, left2, left3});
inline pros::Motor_Group rightMotors({right1, right2, right3});

// note to future generations: conlifting triports defs will make you want to
// kys
inline ADIEncoder leftEncoder(3, 4, true);
inline ADIEncoder rightEncoder(1, 2, true);
inline auto ledStrip = sylib::Addrled(22, 8, 40);
inline Mutex encoderMutex;
// inline ADIDigitalOut piston(7, false); //see above

 inline ADIPotentiometer potentiometer(2); // see above

// 18 bod
