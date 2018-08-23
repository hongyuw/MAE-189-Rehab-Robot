/*
  This file reads six motor position information from the robotic arm, and map the readings to our desired intervals
*/
#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield md; //motor driver

const int switchA = 2, switchB = 3, switchC = 4, switchD = 5, switchTrigger = 6;  //trigger and 4 buttons on the robotic arm
const int xAxis = A0, yAxis = A1, zAxis = A2, Pitch = A3, Roll = A4, Yaw = A5;   //six potentiometers connected to the motors
//initiate the mapped variables
int newxAxis = 0, newyAxis = 0, newzAxis = 0, newPitch = 0, newRoll = 0, newYaw = 0;

void setup() {
  
  Serial.begin(9600);
  md.init();
  
  //we only use X,Y,Z,Pitch  A0--X, A1--Y, A2--Z, A3--Pitch
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT); 
}


void loop() {
  serialprint1();
}

void serialprint1() {
  //map the readings to desired intervals
  newxAxis = map(analogRead(xAxis),741,951,200,300); 
  newyAxis = map(analogRead(yAxis),100,200,100,200); 
  newzAxis = map(analogRead(zAxis),0,133,200,300);
  newPitch = map(analogRead(Pitch),920,890,200,300);
  
  //formatted output
  Serial.print(newxAxis+200);
  Serial.print(",");
  Serial.print(newyAxis-200);
  Serial.print(",");
  Serial.print(newzAxis);
  Serial.print(",");
  Serial.println(newPitch);

  Serial.flush();
  delay(10);
}
