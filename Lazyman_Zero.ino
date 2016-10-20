#include "Envi.h"
#include "Function.h"
Envi envi;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //read the status of reset bt
  if (envi.resetBt->isPressed())
  {
    //do the programm of reset
    Serial.println("reset Bt is Pressed");
    resetProgramm(envi);
  }
  else
  {
    //read the status of doBt
    if (envi.doBt->isPressed())
    {
      //do the programm of do
      Serial.println("do Bt is Pressed");
      doProgramm(envi);
    }
  }
}
