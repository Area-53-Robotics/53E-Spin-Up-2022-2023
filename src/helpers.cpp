#include "main.h"

//Misc helper functions
void printData () {
    while (true) {
    //int printf(encoder.get_value());
    std::cout << "Encoder Value: " << encoder.get_value() << std::endl;
    pros::delay(10);
}
}
