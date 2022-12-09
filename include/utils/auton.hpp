#ifndef AUTON_HPP
#define AUTON_HPP
// Auton:
enum Direction { Left, Right, Forward, Backward };

void turnBangBang(double target);

void movePid(float target);
void turnPid(Direction direction, float turnValue);
#ifndef