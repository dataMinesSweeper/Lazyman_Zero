#include "Function.h"
#include "Config.h"
#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
boolean allSixBtIsNull(Envi envi);
unsigned long computeInterMillis(unsigned long start, unsigned long end);
void writeDelayCommand(File* file, unsigned long ms);
void writeOutputChangeCommad(File* file, int bt1State, int bt2State, int bt3State, int bt4State);
void writeMotorRunCommand(File * file, int motor1En, int motor2En, int motor3En, int num);
boolean motorControBtIsDelay(Envi envi, int motor1lState, int motor1rState, int motor2lState, int motor2rState, int motor3uState, int motor3dState);

void resetProgramm(Envi envi)
{
  //open the programm file to write
  SD.remove("programm.txt");
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
		unsigned long endTime;
		while(envi.delayBt->isPressed())
		{
			//check four bt status
			boolean curBt1State = envi.bt1Bt->isPressed();
			boolean curBt2State = envi.bt2Bt->isPressed();
			boolean curBt3State = envi.bt3Bt->isPressed();
			boolean curBt4State = envi.bt4Bt->isPressed();
			if(Bt1State != curBt1State || Bt2State != curBt2State || 
			   Bt3State != curBt3State || Bt4State != curBt4State)
			   {
				   Bt1State = curBt1State;
				   Bt2State = curBt2State;
				   Bt3State = curBt3State;
				   Bt4State = curBt4State;
				   endTime = millis();
				   startTime = endTime;
				   writeDelayCommand(&programmFile, computeInterMillis(startTime, endTime));
				   writeOutputChangeCommad(&programmFile, Bt1State, Bt2State, Bt3State, Bt4State);
				   changeOutputState(envi, Bt1State, Bt2State, Bt3State, Bt4State);
			   }
		}
		endTime = millis();
		writeDelayCommand(&programmFile, computeInterMillis(startTime, endTime));
	}
	else
	{
		//write motor control button status
		boolean motor1lState = envi.motor1lBt->isPressed();
		boolean motor1rState = envi.motor1rBt->isPressed();
		boolean motor2lState = envi.motor2lBt->isPressed();
		boolean motor2rState = envi.motor2rBt->isPressed();
		boolean motor3uState = envi.motor3uBt->isPressed();
		boolean motor3dState = envi.motor3dBt->isPressed();
		
		if(motor1lState || motor1rState || motor2lState || motor2rState || motor3uState || motor3dState)
		{
			int motor1En = motor1lState * MOTOR_L_BASE + motor1rState * MOTOR_R_BASE;
			int motor2En = motor2lState * MOTOR_L_BASE + motor2rState * MOTOR_R_BASE;
			int motor3En = motor3uState * MOTOR_U_BASE + motor3dState * MOTOR_D_BASE;
			motorRun(envi, motor1En, motor2En, motor3En, 1);
			int motorRunNum = 1;
			//等待直到状态改变
			while(motorControBtIsDelay(envi, motor1lState, motor1rState, motor2lState, motor2rState, motor3uState, motor3dState))
			{
				motorRunNum++;
				motorRun(envi, motor1En, motor2En, motor3En, 1);
			}
			writeMotorRunCommand(&programmFile, motor1En, motor2En, motor3En, motorRunNum);
			
		}
		
	}
	
  }
  programmFile.close();
  envi.resetAllMotors();
}

void doProgramm(Envi envi)
{
  //open the prigramm file to read
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
  envi.resetAllMotors();
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
	if (0 != motor1En && 0 == motor2En && 0 == motor3En) 
	{
		envi.motor1->stepByNum(num * motor1En);
		return;
	}
	if (0 == motor1En && 0 != motor2En && 0 == motor3En) 
	{
		envi.motor2->stepByNum(num * motor2En);
		return;
	}
	if (0 == motor1En && 0 == motor2En && 0 != motor3En) 
	{
		envi.motor3->stepByNum(num * motor3En);
		return;
	}
	
	int i = 0;
	for(; i<num; i++)
	{
		if(motor1En) envi.motor1->stepByNum(motor1En);
		if(motor2En) envi.motor2->stepByNum(motor2En);
		if(motor3En) envi.motor3->stepByNum(motor3En);
	}
}

boolean allSixBtIsNull(Envi envi)
{
	if (envi.motor1lBt->isPressed() || envi.motor1rBt->isPressed() ||
		envi.motor2lBt->isPressed() || envi.motor2rBt->isPressed() ||
		envi.motor3uBt->isPressed() || envi.motor3dBt->isPressed() )
	return false;
	return true;
}

unsigned long computeInterMillis(unsigned long start, unsigned long end)
{
	if (start <= end )
	{
		return (end - start);
	}
	else
	{
		return (end + MAX_MILLIS - start);
	}
}

void writeDelayCommand(File* file, unsigned long ms)
{
	file->write(2);
	int i = 0;
	for (; i < ms/MAX_RECORD_NUM; i++)
	{
		file->write(MAX_RECORD_NUM);
	}
	file->write(ms%MAX_RECORD_NUM);
}

void writeOutputChangeCommad(File* file, int bt1State, int bt2State, int bt3State, int bt4State)
{
	file->write(1);
	file->write(bt1State);
	file->write(bt2State);
	file->write(bt3State);
	file->write(bt4State);
}

void writeMotorRunCommand(File* file, int motor1En, int motor2En, int motor3En, int num)
{
	file->write((uint8_t)0);
	file->write(motor1En);
	file->write(motor2En);
	file->write(motor3En);
  int i = 0;
  for (; i<num/MAX_RECORD_NUM; i++)
  {
    file->write(MAX_RECORD_NUM);  
  }
  file->write(num%MAX_RECORD_NUM);
}

boolean motorControBtIsDelay(Envi envi,int motor1lState, int motor1rState, int motor2lState, int motor2rState, int motor3uState, int motor3dState)
{
	boolean motor1lState2 = envi.motor1lBt->isPressed();
	boolean motor1rState2 = envi.motor1rBt->isPressed();
	boolean motor2lState2 = envi.motor2lBt->isPressed();
	boolean motor2rState2 = envi.motor2rBt->isPressed();
	boolean motor3uState2 = envi.motor3uBt->isPressed();
	boolean motor3dState2 = envi.motor3dBt->isPressed();
	if(	motor1lState2 == motor1lState &&
		motor1rState2 == motor1rState &&
		motor2lState2 == motor2lState &&
		motor2rState2 == motor2rState &&
		motor3uState2 == motor3uState &&
		motor3dState2 == motor3dState )
	return true;
	return false;
}
