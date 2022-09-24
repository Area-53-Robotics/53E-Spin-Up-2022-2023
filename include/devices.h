#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
using namespace pros;

inline Controller controller(E_CONTROLLER_MASTER);
inline Motor left1(10,E_MOTOR_GEARSET_36,true);
inline Motor right1(5,E_MOTOR_GEARSET_36);
inline Motor left2(8,E_MOTOR_GEARSET_36,true);
inline Motor right2(11,E_MOTOR_GEARSET_36);

inline Motor left3(9,E_MOTOR_GEARSET_36,true);
inline Motor right3(7,E_MOTOR_GEARSET_36);

inline ADIEncoder encoder (1,2);
