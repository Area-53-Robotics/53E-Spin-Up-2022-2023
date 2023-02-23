#ifndef AUTON_HPP
#define AUTON_HPP
#include "main.h"

// Aton:
enum class Auton { RollerShoot, MoveRoller, ProgSkills, Testing, None };
enum Direction { Left, Right};

inline Auton auton;

void turnBangBang(double target);

void movePid(double target, bool isReverse);
void turnPid(Direction direction, float turnValue);
#endif
