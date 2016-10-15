/* in this file , set the parameters */ 
#ifndef CONFIG_H
#define CONFIG_H

#define MAX_MILLIS 4294967295

#define MOTOR_NUM 3
/* the pin number of Motor1 */
#define MOTOR1_EN_PIN 23
#define MOTOR1_DIR_PIN 25
#define MOTOR1_PUL_PIN 27

/* the pin number of Motor2 */
#define MOTOR2_EN_PIN 29
#define MOTOR2_DIR_PIN 31
#define MOTOR2_PUL_PIN 33

/* the pin number of Motor3 */
#define MOTOR3_EN_PIN 35
#define MOTOR3_DIR_PIN 37
#define MOTOR3_PUL_PIN 39

/* the wait time of the Pul */
#define MOTOR_PUL_WAITTIME 1000

/* the four pin of the four buttons */
#define OUTPUT1_PIN 41
#define OUTPUT2_PIN 43
#define OUTPUT3_PIN 45
#define OUTPUT4_PIN 47

#define DO_BT_PIN 53

/* the button pin defined of the teaching */
#define RESET_BT_PIN 22
#define MOTOR1L_BT_PIN 22
#define MOTOR1R_BT_PIN 24
#define MOTOR2L_BT_PIN 26
#define MOTOR2R_BT_PIN 28
#define MOTOR3U_BT_PIN 30
#define MOTOR3D_BT_PIN 32
#define DELAY_BT_PIN 34
#define BT1_PIN 36
#define BT2_PIN 38
#define BT3_PIN 40
#define BT4_PIN 42

#endif
