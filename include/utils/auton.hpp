#pragma once
#include "main.h"

// Auton:
enum class Auton { DriverSide, FarSide, ProgSkills, Testing, None };
enum Direction { Left, Right };

Auton get_current_auton();
