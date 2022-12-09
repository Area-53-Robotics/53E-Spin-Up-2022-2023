#include "utils/misc.hpp"
#include "api.h"
#include <cmath>
#include "devices.h"

float arcMeasure(float arcLength, float radius) {
  return (arcLength / (2 * radius * M_PI)) * 360;
}

float arcLength(float degrees, float radius) {
  return (degrees / 360) * (2 * radius * M_PI);
}
// Misc helper functions
void printData() {
  while (true) {
    // Print to terminal
    // std::cout << launcherMotor.get_position() << std::endl;
    // Print to brain
    // std::string position =
    // std::to_string(launcherMotor.get_actual_velocity()); std::string power =
    // std::to_string(70 - launcherEncoder.get_value()/10*1000);
    // Print to controller
    // controller.set_text(1, 0, position);
    // pros::delay(10); // We need a delay after each screen print

    // double distMovedRight =
    // int distMoved = leftEncoder.get_value() - rightEncoder.get_value();
    // right1.get_position() * 3 / 5 * 3.75 * M_PI * 2 / 360;
    pros::delay(50);
  }
}
