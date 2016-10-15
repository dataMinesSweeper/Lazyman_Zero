#include "Config.h"
#include "Motor.h"
#include "OutPut.h"
#include "InputBt.h"

/* init three motor */
Motor motor1(MOTOR1_EN_PIN, MOTOR1_DIR_PIN, MOTOR1_PUL_PIN, MOTOR_PUL_WAITTIME);
Motor motor2(MOTOR1_EN_PIN, MOTOR1_DIR_PIN, MOTOR1_PUL_PIN, MOTOR_PUL_WAITTIME);
Motor motor3(MOTOR1_EN_PIN, MOTOR1_DIR_PIN, MOTOR1_PUL_PIN, MOTOR_PUL_WAITTIME);
Motor* MotorArr[MOTOR_NUM] = {&motor1, &motor2, &motor3};

/* init four Buttons */
OutPut output1( OUTPUT1_PIN );
OutPut output2( OUTPUT2_PIN );
OutPut output3( OUTPUT3_PIN );
OutPut output4( OUTPUT4_PIN );

/* init the do bt */
InputBt doBt( DO_BT_PIN );
