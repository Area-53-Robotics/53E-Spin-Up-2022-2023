#include "main.h"
#include <string>

// Misc helper functions
void printData() {
  while (true) {
    // Print to terminal
    std::cout << launcherMotor.get_position() << std::endl;
    // Print to brain
    std::string position = std::to_string(launcherMotor.get_actual_velocity());
    std::string launcherPosition = std::to_string(launcherEncoder.get_value());
    // Print to controller
    controller.set_text(1, 0, position);
    pros::delay(10); //We need a delay after each screen print
    controller.set_text(0, 0, launcherPosition);
    pros::delay(10);
  }
}
