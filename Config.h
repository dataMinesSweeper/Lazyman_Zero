/* in this file , set the parameters */ 
#ifndef CONFIG_H
#define CONFIG_H

#define MAX_MILLIS 4294967295
#define MAX_RECORD_NUM 200
#define MOTOR_L_BASE 1 
#define MOTOR_R_BASE -1
#define MOTOR_U_BASE 1
#define MOTOR_D_BASE -1

#define MOTOR_NUM 3
/* the pin number of Motor1 */
#define MOTOR1_EN_PIN 25
#define MOTOR1_DIR_PIN 27
#define MOTOR1_PUL_PIN 29

/* the pin number of Motor2 */
#define MOTOR2_EN_PIN 31
#define MOTOR2_DIR_PIN 33
#define MOTOR2_PUL_PIN 35

/* the pin number of Motor3 */
#define MOTOR3_EN_PIN 37
#define MOTOR3_DIR_PIN 39
#define MOTOR3_PUL_PIN 41

/* the wait time of the Pul */
#define MOTOR_PUL_WAITTIME 500

/* the four pin of the four buttons */
#define OUTPUT1_PIN 4
#define OUTPUT2_PIN 5
#define OUTPUT3_PIN 6
#define OUTPUT4_PIN 7

#define DO_BT_PIN 0

/* the button pin defined of the teaching */
#define RESET_BT_PIN 1
#define MOTOR1L_BT_PIN 14
#define MOTOR1R_BT_PIN 15
#define MOTOR2L_BT_PIN 4
#define MOTOR2R_BT_PIN 5
#define MOTOR3U_BT_PIN 6
#define MOTOR3D_BT_PIN 7
#define DELAY_BT_PIN 8
#define BT1_PIN 9
#define BT2_PIN 10
#define BT3_PIN 11
#define BT4_PIN 12

#endif
