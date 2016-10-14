#ifndef BT_H
#define BT_H

class Bt
{
	private:
		int pinNum;
	public:
		Bt(int pinNum);
		void enable();
		void disable();
};

#endif
