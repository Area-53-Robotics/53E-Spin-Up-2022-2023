
// General funtions:
void printData();

// Opcontrol:
void spinUp();

// Auton:
enum Direction { Left, Right, Forward, Backward };
void moveBangBang(double target, bool isReverse);
void turnBangBang(double target);

void movePid(float target);
void turnPid(Direction direction, float turnValue);

// movepid and such would be defined here
