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
  y = Serial.readBytesUntil(lf,x,1);
  
  if(strcmp(x,"r")==0){
      md.setM1Speed(-400);
      delay(20);                    
  }      
  else{
      md.setM1Speed(0);   
      delay(0);
   }
}
