#ifndef INPUTBT_H
#define INPUTBT_H
#include "Arduino.h"

class InputBt
{
	private:
		int pinNum;
	  int delayTime;
	public:
		InputBt(int pinNum, int delayTime);
		boolean isPressed();
};

#endif
