#include "Envi.h"

Envi::Envi()
{
  /* init three motor */
  motor1 = new Motor(MOTOR1_EN_PIN, MOTOR1_DIR_PIN, MOTOR1_PUL_PIN, MOTOR_PUL_WAITTIME);
  motor2 = new Motor(MOTOR2_EN_PIN, MOTOR2_DIR_PIN, MOTOR2_PUL_PIN, MOTOR_PUL_WAITTIME);
  motor3 = new Motor(MOTOR3_EN_PIN, MOTOR3_DIR_PIN, MOTOR3_PUL_PIN, MOTOR_PUL_WAITTIME);

  /* init four Buttons */
  output1 = new OutPut( OUTPUT1_PIN );
  output2 = new OutPut( OUTPUT2_PIN );
  output3 = new OutPut( OUTPUT3_PIN );
  output4 = new OutPut( OUTPUT4_PIN );

  /* init the do bt */
  doBt = new InputBt( DO_BT_PIN, 50);
  resetBt = new InputBt(RESET_BT_PIN, 50);
  motor1lBt = new InputBt( MOTOR1L_BT_PIN, 50);
  motor1rBt = new InputBt( MOTOR1R_BT_PIN, 50);
  motor2lBt = new InputBt( MOTOR2L_BT_PIN, 50);
  motor2rBt = new InputBt( MOTOR2R_BT_PIN, 50);
  motor3uBt = new InputBt( MOTOR3U_BT_PIN, 50);
  motor3dBt = new InputBt( MOTOR3D_BT_PIN, 50);
  delayBt = new InputBt( DELAY_BT_PIN, 50);
  bt1Bt = new InputBt( BT1_PIN, 50);
  bt2Bt = new InputBt( BT2_PIN, 50);
  bt3Bt = new InputBt( BT3_PIN, 50);
  bt4Bt = new InputBt( BT4_PIN, 50);
}

void Envi::enableMotors()
{
  motor1->enable();
  motor2->enable();
  motor3->enable();
}

void Envi::disableMotors()
{
  motor1->disable();
  motor2->disable();
  motor3->disable();
}

void Envi::resetAllMotors()
{
  motor1->reset();
  motor2->reset();
  motor3->reset();
}
