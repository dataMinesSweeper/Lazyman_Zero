#include "Motor.h"

Motor::Motor(int enPin, int dirPin, int pulPin, int waitTime)
{
  this->enPin = enPin;
  this->dirPin = dirPin;
  this->pulPin = pulPin;
  this->waitTime = waitTime;
  this->curMotorNum = 0;
  pinMode(enPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(pulPin, OUTPUT);
  
  digitalWrite(enPin, HIGH);
}

void Motor::enable()
{
  digitalWrite(enPin, LOW);
}

void Motor::disable()
{
  digitalWrite(enPin, HIGH);
}

void Motor::stepByNum(int num)
{
   int loopTime = num;
   if (num < 0)
   {
     digitalWrite(this->dirPin, HIGH);
     loopTime = 0 - num;
   } 
   else{
     digitalWrite(this->dirPin, LOW);
   }
   
   int i;
   for(i=0; i< loopTime; i++)
   {
     digitalWrite(this->pulPin, HIGH);
     delayMicroseconds(this->waitTime);
     digitalWrite(this->pulPin, LOW);
   }
   this->curMotorNum += num;
}

void Motor::reset()
{
  stepByNum(0 - curMotorNum);  
  curMotorNum = 0;
}


