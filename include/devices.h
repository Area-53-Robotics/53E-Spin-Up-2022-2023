#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
using namespace pros;

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
inline pros::Motor left1(10,E_MOTOR_GEARSET_36,true);
inline pros::Motor right1(5,E_MOTOR_GEARSET_36);
inline pros::Motor left2(8,E_MOTOR_GEARSET_36,true);
inline pros::Motor right2(11,E_MOTOR_GEARSET_36);

inline pros::Motor left3(9,E_MOTOR_GEARSET_36,true);
inline pros::Motor right3(7,E_MOTOR_GEARSET_36);

inline pros::ADIEncoder encoder (1,2);
