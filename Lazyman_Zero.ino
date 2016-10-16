#include "Envi.h"
#include "Function.h"
Envi envi;
void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //read the status of reset bt
  if (envi.resetBt->isPressed())
  {
    //do the programm of reset
    resetProgramm(envi);
  }
  else
  {
    //read the status of doBt
    if (envi.doBt->isPressed())
    {
      //do the programm of do
      doProgramm(envi);
    }
  }
}
