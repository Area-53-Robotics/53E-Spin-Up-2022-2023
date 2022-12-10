#ifndef AUTON_HPP
#define AUTON_HPP
// Auton:
enum class Auton { RedLeft, RedRight, BlueLeft, BlueRight, Skills };
enum Direction { Left, Right, Forward, Backward };

void turnBangBang(double target);

void movePid(double target, bool isReverse);
void turnPid(Direction direction, float turnValue);
#endif
