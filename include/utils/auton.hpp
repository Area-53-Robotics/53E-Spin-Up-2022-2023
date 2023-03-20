#pragma once
#include "main.h"

// Auton:
enum class Auton { RollerShoot, MoveRoller, ProgSkills, Testing, None };
enum Direction { Left, Right };

Auton get_current_auton();
