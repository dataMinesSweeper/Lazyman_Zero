#include "Arduino.h"
#include "Bt.h"

Bt::Bt(int pinNum)
{
	this->pinNum = pinNum;
	pinMode(pinNum, OUTPUT);
}

void Bt::enable()
{
	digitalWrite(pinNum, HIGH);
}

void Bt::disable()
{
	digitalWrite(pinNum, LOW);
}
