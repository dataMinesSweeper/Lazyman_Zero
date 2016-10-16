#include "Function.h"
#include "Config.h"
#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
boolean allSixBtIsNull(Envi envi);

void resetProgramm(Envi envi)
{
  //open the programm file to write
  SD.begin();
  File programmFile = SD.open("programm.txt", FILE_WRITE);
  boolean Bt1State = false;
  boolean Bt2State = false;
  boolean Bt3State = false;
  boolean Bt4State = false;
  while(envi.resetBt->isPressed())
  {
    if(envi.delayBt->isPressed())
	{
		unsigned long startTime = millis();
		while(envi.delayBt->isPressed())
		{
			//check four bt status
		}
	}
	else if(allSixBtIsNull(envi)) ;
	else
	{
		//read motor control button status
		
	}
	
  }
  programmFile.close();
}

void doProgramm(Envi envi)
{
  //open the prigramm file to read
  SD.begin();
  File programmFile = SD.open("programm.txt");
  while(programmFile.available())
  {
    int commandFlag = programmFile.read();
	//motor run command
	if( 0 == commandFlag )
	{
		int motor1En = programmFile.read();
		int motor2En = programmFile.read();
		int motor3En = programmFile.read();
		int curNum = programmFile.read();
		int totalNum = curNum;
		while(curNum == 255)
		{
			curNum = programmFile.read();
			totalNum += curNum;
		}
		motorRun(envi, motor1En, motor2En, motor3En, totalNum);
	}
	
	if( 1 == commandFlag )
	{
		changeOutputState(envi, programmFile.read(), programmFile.read(), programmFile.read(), programmFile.read());
	}
	
	if( 3 == commandFlag )
	{
		int curNum = programmFile.read();
		int totalNum = curNum;
		while(curNum == 255)
		{
			curNum = programmFile.read();
			totalNum += curNum;
		}
		delay(totalNum);
	}
  }
  programmFile.close();
}

void changeOutputState(Envi envi, int bt1State, int bt2State, int bt3State, int bt4State)
{
  bt1State ? envi.output1->enable() : envi.output1->disable();
  bt2State ? envi.output2->enable() : envi.output2->disable();
  bt3State ? envi.output3->enable() : envi.output3->disable();
  bt4State ? envi.output4->enable() : envi.output4->disable();
}

void motorRun(Envi envi, int motor1En, int motor2En, int motor3En, int num)
{
	if (1 == motor1En && 0 == motor2En && 0 == motor3En) 
	{
		envi.motor1->enable();
		envi.motor1->stepByNum(num);
		envi.motor1->disable();
		return;
	}
	if (0 == motor1En && 1 == motor2En && 0 == motor3En) 
	{
		envi.motor2->enable();
		envi.motor2->stepByNum(num);
		envi.motor2->disable();
		return;
	}
	if (0 == motor1En && 0 == motor2En && 1 == motor3En) 
	{
		envi.motor3->enable();
		envi.motor3->stepByNum(num);
		envi.motor3->disable();
		return;
	}
	if(motor1En) envi.motor1->enable();
	if(motor2En) envi.motor2->enable();
	if(motor3En) envi.motor3->enable();
	
	if(num > 0)
	{
		int i = 0;
		for(; i<num; i++)
		{
			if(motor1En) envi.motor1->stepByNum(1);
			if(motor2En) envi.motor2->stepByNum(1);
			if(motor3En) envi.motor3->stepByNum(1);
		}
	}
	else
	{
		int i = 0;
		for(; i>num; i--)
		{
			if(motor1En) envi.motor1->stepByNum(-1);
			if(motor2En) envi.motor2->stepByNum(-1);
			if(motor3En) envi.motor3->stepByNum(-1);
		}
	}
	
	if(motor1En) envi.motor1->disable();
	if(motor2En) envi.motor2->disable();
	if(motor3En) envi.motor3->disable();
}

boolean allSixBtIsNull(Envi envi)
{
	if (envi.motor1lBt->isPressed() || envi.motor1rBt->isPressed() ||
		envi.motor2lBt->isPressed() || envi.motor2rBt->isPressed() ||
		envi.motor3uBt->isPressed() || envi.motor3dBt->isPressed() )
	return false;
	return true;
}
