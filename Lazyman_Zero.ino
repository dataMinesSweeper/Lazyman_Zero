#include "Envi.h"
#include "Function.h"
Envi envi;
void setup() {
  // put your setup code here, to run once:
  SD.begin(4);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //read the status of reset bt
  if (envi.resetBt->isPressed())
  {
    //do the programm of reset
    Serial.println("reset Bt is Pressed");
    delay(20000);
    envi.enableMotors();
    resetProgramm(envi);
    envi.disableMotors();
  }
  else
  {
    //read the status of doBt
    if (envi.doBt->isPressed())
    {
      //do the programm of do
      Serial.println("do Bt is Pressed");
      envi.enableMotors();
      doProgramm(envi);
      envi.disableMotors();
    }
  }
}
