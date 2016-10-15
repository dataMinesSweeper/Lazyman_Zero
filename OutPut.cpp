#include "Arduino.h"
#include "OutPut.h"

OutPut::OutPut(int pinNum)
{
	this->pinNum = pinNum;
	pinMode(pinNum, OUTPUT);
}

void OutPut::enable()
{
	digitalWrite(pinNum, HIGH);
}

void OutPut::disable()
{
	digitalWrite(pinNum, LOW);
}
