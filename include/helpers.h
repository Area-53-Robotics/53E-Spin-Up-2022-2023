

// General funtions:
void printData();

// Opcontrol:
void spinUp();

// Auton:
void movePid(float target);
void moveBangBang(float target);
enum cooler_direction{Left, Right};

void turnPid(cooler_direction direction, float turnValue);

// movepid and such would be defined here
