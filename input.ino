#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield md;

const int switchA = 2, switchB = 3, switchC = 4, switchD = 5, switchTrigger = 6;
const int xAxis = A0, yAxis = A1, zAxis = A2, Pitch = A3, Roll = A4, Yaw = A5;
int newxAxis = 0, newyAxis = 0, newzAxis = 0, newPitch = 0, newRoll = 0, newYaw = 0;
int Force = 0;
int Trigger = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  md.init();
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT); // 3
}
//A0--X,A3--Pitch

void loop() {
  serialprint1();
}

void serialprint1() {
  newxAxis = map(analogRead(xAxis),741,951,200,300); 
  newyAxis = map(analogRead(yAxis),100,200,100,200); 
  newzAxis = map(analogRead(zAxis),0,133,200,300);
  newPitch = map(analogRead(Pitch),920,890,200,300);
  Trigger = digitalRead(6);
  // Force = 4 * newxAxis;
  //md.setM1Speed(Force);
  Serial.print(newxAxis+200);
  Serial.print(",");
  Serial.print(newyAxis-200);
  Serial.print(",");
  Serial.print(newzAxis);
  Serial.print(",");
  Serial.println(newPitch);
 // Serial.print(newxAxis); // A0
 // Serial.print(",");
 // Serial.println(md.getM1CurrentMilliamps());
 // Serial.println(newPitch); // A3
  Serial.flush();
  delay(10);
}
