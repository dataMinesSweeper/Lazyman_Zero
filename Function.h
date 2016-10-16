#ifndef FUNCTION_H
#define FUNCTION_H
#include "Envi.h"

void resetProgramm(Envi envi);

void doProgramm(Envi envi);

void motorRun(Envi envi, int motor1En, int motor2En, int motor3En, int num);

void changeOutputState(Envi envi, int bt1State, int bt2State, int bt3State, int bt4State);


#endif
