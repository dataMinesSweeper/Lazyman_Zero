#ifndef OUTPUT_H
#define OUTPUT_H

class OutPut
{
	private:
		int pinNum;
	public:
		OutPut(int pinNum);
		void enable();
		void disable();
};

#endif
