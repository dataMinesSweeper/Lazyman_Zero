#include "InputBt.h"

InputBt::InputBt(int pinNum)
{
	this->pinNum = pinNum;
	pinMode( pinNum, INPUT);
}

boolean InputBt::isPressed()
{
	if (HIGH == digitalRead(pinNum)) 
	{
		return true;
	}
	else
	{
		return false;
	}
}
