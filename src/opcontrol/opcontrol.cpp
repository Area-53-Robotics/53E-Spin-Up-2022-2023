#include "main.h"
#include "pros/misc.h"
#include <iostream>

/*
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
////////////////////////////////////////////////////////////////////////////
void movePid (float target) {
   float kP = 7;
   float distMoved;
   float error = target;  
   float power;

   
   while (std::abs(error) > 0)
 {
   distMoved = encoder.get_value() * 8.64; //cir. wheel
   error = target - distMoved;
   power = error * kP;


    if (error > 50 || power > 127) {
		power = 127;
      
    }

      leftMotors.move(power);
      rightMotors.move(power);

//controller.clear();
	 // std::cout << "Error: " << error << "-" << power << std::endl;
	  //std::cout << "Power: " << power << std::endl;


    delay(10);
    }}
 ///////////////////////////////////////////////////////////////////////////////////

 void turnPid (int direction, float turnValue) {

      if (direction == 1) {
        leftMotors.move_absolute(turnValue * -1, 127);
        rightMotors.move_absolute(turnValue, 127);
      }
      else if (direction == 2) {
      leftMotors.move_absolute(turnValue, 127);
      rightMotors.move_absolute(turnValue * -1, 127);
      }
  
    }


    
    void launcherMove () {
      int pAngle = potentiometer.get_angle();
      while (pAngle < 140) {                      //////////////////////////////////////////////// tune at comp
      launcherMotor.move(127);

              controller.print(1, 1, "angle = %i", pAngle);


      if (controller.get_digital(E_CONTROLLER_DIGITAL_L2)) { //cata + potentiometer
        launcherMotor.move(-127);
      }

   }
    }
  
void opcontrol() {
  
    bool isDriveReversed = false;

    

    

  while (true) {

    if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) { //roller
      rollerMotor.move(100);}else {
        rollerMotor.move(0);}

    if (controller.get_digital(E_CONTROLLER_DIGITAL_LEFT)) { //launcher
      launcherMotor.move(127);}else {
        launcherMotor.move(0);
      
      }
    //Task launcherMoveTask(launcherMove);

    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) { //drive switch
    isDriveReversed = !isDriveReversed;
    } 

    if (isDriveReversed == 1) {
        leftMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) * -1);
        rightMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) * -1);
    } else {
      leftMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
      rightMotors.move(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    }



    //leftMotors.move(controller.get_analog(ANALOG_LEFT_Y));
    //rightMotors.move(controller.get_analog(ANALOG_RIGHT_Y));

  /* while (true) {
    

    int rollerMotorVoltage = rollerMotor.get_voltage();

    controller.print(1, 1, "voltage = ", rollerMotorVoltage);
     
    //Tank drive moment
    //leftMotors.move(controller.get_analog(ANALOG_LEFT_Y));
    //rightMotors.move(controller.get_analog(ANALOG_RIGHT_Y));

     //////////////////////////////////////// maybe change value
    } */

   

    bool intakeOn = false;

    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) { //intake + toggle

    if (intakeOn == false) {
      rollerMotor.move(-127);
      intakeOn = true;  //////////////////////////////////////////////////////// tune
    } else if (intakeOn == true) {
      rollerMotor.move(0);
      intakeOn = false;
    }

    }
    
    

    
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) {controller.rumble(".");}
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {controller.rumble(".");}
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {controller.rumble(".");}
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {controller.rumble(".");}
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) {controller.rumble(".");}

    pros::delay(20);
 
    }    
  
//felix wuz here

  
    } 

    

    