#include "Init.h"
#include "Motor.h"

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.enable();
  motor1.stepByNum(600);
  motor1.disable();
}
