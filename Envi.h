#ifndef ENVI_H
#define ENVI_H

#include "Config.h"
#include "Motor.h"
#include "OutPut.h"
#include "InputBt.h"

class Envi
{
  public:
    Motor* motor1;
    Motor* motor2;
    Motor* motor3;

    /* init four Buttons */
    OutPut* output1;
    OutPut* output2;
    OutPut* output3;
    OutPut* output4;

    /* init the do bt */
    InputBt* doBt;
    
    InputBt* resetBt;
    InputBt* motor1lBt;
    InputBt* motor1rBt;
    InputBt* motor2lBt;
    InputBt* motor2rBt;
    InputBt* motor3uBt;
    InputBt* motor3dBt;
    InputBt* delayBt;
    InputBt* bt1Bt;
    InputBt* bt2Bt;
    InputBt* bt3Bt;
    InputBt* bt4Bt;
  
    Envi();
  
    void enableMotors();
    void disableMotors();
    void resetAllMotors();
};

#endif
