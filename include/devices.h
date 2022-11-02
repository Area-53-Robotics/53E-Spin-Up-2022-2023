
#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
using namespace pros;

inline Controller controller(E_CONTROLLER_MASTER);

inline Motor left1(16,E_MOTOR_GEAR_BLUE,true);
inline Motor left2(17,E_MOTOR_GEAR_BLUE,true);
inline Motor left3(18,E_MOTOR_GEAR_BLUE,true);

inline Motor right1(11,E_MOTOR_GEAR_BLUE);
inline Motor right2(12,E_MOTOR_GEAR_BLUE);
inline Motor right3(13,E_MOTOR_GEAR_BLUE);

inline Motor rollerMotor(20,E_MOTOR_GEAR_GREEN);

inline Motor launcherMotor(11,E_MOTOR_GEAR_BLUE, true);

inline pros::Motor_Group leftMotors ({left1, left2, left3});
inline pros::Motor_Group rightMotors ({right1, right2, right3});

inline ADIEncoder encoder (2,1);

