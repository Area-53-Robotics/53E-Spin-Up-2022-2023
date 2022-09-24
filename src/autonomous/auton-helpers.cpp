#include "main.h"

void movePid (float target) {
   left1.set_zero_position(0);
   float kP = 7;
   float distMoved;
   float error = target;  
   float power;

   
   while (error > 0.2)
 {
   distMoved = left1.get_position() * 12.57; //cir. wheel
   error = target - distMoved;
   power = error * kP;


    if (error > 50 || power > 127) {
		power = 127;
      
    }

      left1.move(power);
      left2.move(power);
      right1.move(power);
      right2.move(power);

	  controller.clear();
	  std::cout << "Error: " << error << "-" << power << std::endl;
	  //std::cout << "Power: " << power << std::endl;


    pros::delay(50);

    }    


      //left1.move(0);
      //left2.move(0);
      //right1.move(0);
      //right2.move(0);

	  
	  //controller.print(0, 0, "Error: %f", error);
	  

	  

}
