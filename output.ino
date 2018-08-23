/*
  This file detects the output from the unity, and controls the motor to create forces.
*/
#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield md;

char x[20];
String y;
void setup() {
  Serial.begin(9600);
  md.init();
}


void loop() {
  int lf = 10;
  y = Serial.readBytesUntil(lf,x,1); //y is useless, only read the char and store it into x
  
  //if detected output r, turn on the motor, else turn off the motor.
  if(strcmp(x,"r")==0){
      md.setM1Speed(-400);
      delay(20);                    
  }      
  else{
      md.setM1Speed(0);   
      delay(0);
   }
}
