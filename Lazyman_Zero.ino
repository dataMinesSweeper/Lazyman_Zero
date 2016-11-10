#include <SPI.h>
#include <SD.h>
#include "Envi.h"
#include "Function.h"
Envi envi;
void setup() {
  // put your setup code here, to run once:
  SD.begin(4);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //read the status of reset bt 
  if (envi.resetBt->isPressed())
  {
    //do the programm of reset
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
      envi.enableMotors();
      delay(1000);
      doProgramm(envi);
      envi.disableMotors();
      delay(1000);
    }
  }
}
