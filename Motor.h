/* define the class of Motor */
/* author: liuxc 20161012*/
#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
class Motor
{
  private:
    int enPin;
    int dirPin;
    int pulPin;
    int waitTime;
    int curMotorNum;
  
  public:
    Motor(int enPin, int dirPin, int pulPin, int waitTime);
    void enable();
    void disable();
    void stepByNum(int num);
    void reset();
};

#endif
