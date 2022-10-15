#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
using namespace pros;

inline Controller controller(E_CONTROLLER_MASTER);

inline Motor left1(9, E_MOTOR_GEARSET_36, true);
inline Motor left2(10, E_MOTOR_GEARSET_36, true);
inline Motor left3(8, E_MOTOR_GEARSET_36, true);

inline Motor right1(20, E_MOTOR_GEARSET_36);
inline Motor right2(19, E_MOTOR_GEARSET_36);
inline Motor right3(18, E_MOTOR_GEARSET_36);

inline Motor rollerMotor(7, E_MOTOR_GEARSET_36);

inline Motor launcherMotor(11, E_MOTOR_GEARSET_36, true);

inline pros::Motor_Group leftMotors({left1, left2, left3});
inline pros::Motor_Group rightMotors({right1, right2, right3});

inline ADIEncoder encoder(7, 8);
inline ADIEncoder launcherEncoder(1, 2);
