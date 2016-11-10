#include "InputBt.h"

InputBt::InputBt(int pinNum, int delayTime)
{
	this->pinNum = pinNum;
  this->delayTime = delayTime;
	//pinMode( pinNum, INPUT);
}

boolean InputBt::isPressed()
{
	if (1000 < analogRead(pinNum)) 
	{
    delay(delayTime);
    if (1000 < analogRead(pinNum)) 
    {
      return true;
    }
		return false;
	}
	else
	{
		return false;
	}
}
