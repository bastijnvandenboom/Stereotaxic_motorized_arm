
// Arduino powered stereotaxic arm robot 20171201 Bastijn van den Boom
//
// First connect the steppermotor to the arduino, then plug in the 9v power supply. Put the switch to O.
// Use the knob on top of the motor to turn the stereotaxic arm and place your object on bregma, write down 
// coordinates of bregma. Move your object above the target area. Lower the object using the know on top of 
// the stereotaxic arm. Keep in mind that there is some slack in the stereotaxic arm and connection with the 
// robot, meaning that the arm doesn't start going down immediately as soon as you start the script or move
// the knob. To account for this, lower the stereotaxic arm with the knob downwards untill you reach bregma
// zero coordinate. 
// 
// Use button A to lower the needle (to make a track) (15min), leave it in for 10 min, and take it out (15min).
// Use button B to lower the lens (30 min)


// Button A (needle lowering) - change accordingly

long total_distance_A = 4500;   // distance to target for needle (unit is micrometer (um))
long time_A = 5;   // time it should take to lower to and then retrack from target (min)
long stay_in_A = 5;    // duration to stay at target (min)


// Button B (lens lowering) - change accordingly

long total_distance_B = 4500;   // distance to target for lens  (unit is micrometer (um))
long time_B = 15;   // time it should take to lower to target (min)




// needle (A) variable to leave like is

float current_distance_A = 0;   // arm moves 0.93125 um per step (float is for variable with many decimals)
long speed_A = (((time_A * 60000) * 0.93125) / total_distance_A); // calculates the corresponding speed
long delay_A = (stay_in_A * 60000);   // calculate how long to stay in milliseconds (ms)

// lens (B) variables to leave like is

float current_distance_B = 0;   // arm moves 0.93125 um per step
long speed_B = (((time_B * 60000) * 0.93125) / total_distance_B);   // how fast should the needle (A) go in and out

// Arduino and SilentStepStick variables, leave it

int button_A_pin = 7;
int button_B_pin = 6;

int button_A = 0;
int button_B = 0;

int steppin = 8;
int dirpin = 9;

int LEDpin = 2;  // LED that indicates motor is running

// int CFG1 = 3;   // to configure SilentStepStick driver mode
// int CFG2 = 4;   // same



void setup()
{

  pinMode(button_A_pin,INPUT_PULLUP);
  pinMode(button_B_pin,INPUT_PULLUP);

  pinMode(steppin, OUTPUT);
  pinMode(dirpin, OUTPUT);
  digitalWrite(dirpin, LOW);  //LOW: goes down. //HIGH: goes up.

  pinMode(LEDpin, OUTPUT);


  //pinMode(CFG1, OUTPUT);
  //pinMode(CFG2, OUTPUT);
  
  //digitalWrite(CFG1, LOW);        // FULL step
  //digitalWrite(CFG2, LOW);

}




void loop()
{

// button A lowers needle, waits, and retrackts needle

digitalWrite(LEDpin, LOW);

      button_A = digitalRead(button_A_pin); 

      if (button_A == LOW){
        delay(200);
        digitalWrite(dirpin, LOW);

        digitalWrite(LEDpin, HIGH);

        while (current_distance_A < total_distance_A){
          
          digitalWrite(steppin, LOW);
          digitalWrite(steppin, HIGH);
          delay(speed_A);

          current_distance_A = current_distance_A + 0.93125;    // distance the arm moves per step
        
        }
        
        delay(delay_A);   // wait with retracking the needle (A)
        digitalWrite(dirpin, HIGH);

        while (current_distance_A >= 0){
          
          digitalWrite(steppin, LOW);
          digitalWrite(steppin, HIGH);
          delay(speed_A);

          current_distance_A = current_distance_A - 0.93125;    // distance the arm moves per step
          
        }
        
      }

           
    
// button B lowers lens 

      button_B = digitalRead(button_B_pin); 

      if (button_B == LOW){
        delay(200);
        digitalWrite(dirpin, LOW);

        digitalWrite(LEDpin, HIGH);

        while (current_distance_B < total_distance_B){
          
          digitalWrite(steppin, LOW);
          digitalWrite(steppin, HIGH);
          delay(speed_B);

          current_distance_B = current_distance_B + 0.93125;    // distance the arm moves per step
        
        }
  
      }

}



        


