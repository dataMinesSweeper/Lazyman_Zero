#ifndef INPUTBT_H
#define INPUTBT_H
#include "Arduino.h"

class InputBt
{
	private:
		int pinNum;
	
	public:
		InputBt(int pinNum);
		boolean isPressed();
};

#endif
