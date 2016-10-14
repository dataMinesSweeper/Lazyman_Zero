#include "Config.h"
#include "Motor.h"
#include "Bt.h"

/* init three motor */
Motor motor1(MOTOR1_EN_PIN, MOTOR1_DIR_PIN, MOTOR1_PUL_PIN, MOTOR_PUL_WAITTIME);
Motor motor2(MOTOR1_EN_PIN, MOTOR1_DIR_PIN, MOTOR1_PUL_PIN, MOTOR_PUL_WAITTIME);
Motor motor3(MOTOR1_EN_PIN, MOTOR1_DIR_PIN, MOTOR1_PUL_PIN, MOTOR_PUL_WAITTIME);

/* init four Buttons */
Bt bt1( BT1_PIN );
Bt bt2( BT2_PIN );
Bt bt3( BT3_PIN );
Bt bt4( BT4_PIN );