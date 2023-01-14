#ifndef AUTON_HPP
#define AUTON_HPP
// Aton:
enum class Auton { RedLeft, RedRight, BlueLeft, BlueRight, Skills };
enum Direction { Left, Right};

void turnBangBang(double target);

void movePid(double target, bool isReverse);
void turnPid(Direction direction, float turnValue);
#endif
