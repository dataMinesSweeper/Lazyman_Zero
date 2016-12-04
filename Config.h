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

#include <stdio.h>
#include <stdlib.h>
#define MAP_SIZE 16
#define bool int
#define false 0
#define true 1
void initMap(int pMap[MAP_SIZE][MAP_SIZE]);
void showMap(int curMap[MAP_SIZE][MAP_SIZE]);
void showMap2(int curMap[MAP_SIZE][MAP_SIZE]);
bool gameStart(void);
bool everyStep();
bool isWined();
void init() ;
bool checkWinDir(int changeI, int chageJ, int curI, int curJ);
void getGreatestPosition();

int maxArray[2];
int map[MAP_SIZE][MAP_SIZE];
int curOperator = 0;
int getDotDir(int ope, int changeI, int chageJ, int curI, int curJ, bool* pQiang);
int getMaxDotCurPos(int ope, int curI, int curJ);
int computeBestPos(int ope, int* pI, int* pJ);
int getMaxDot(int ope);

int main()
{
    //游戏主逻辑
    while(gameStart()) ;
    /*int secMap[MAP_SIZE][MAP_SIZE];
    initMap(secMap);
    map[5][8] = 1;
    map[4][8] = 1;
    map[5][7] = 1;
    map[5][9] = 1;
    int i,j;
    for(i = 1; i<MAP_SIZE; i++) {
        for(j = 1; j<MAP_SIZE; j++) {
            secMap[i][j] = getMaxDotCurPos(1, i, j);
        }
    }
    showMap2(secMap); */
    return 0;
}

//一次游戏开始
bool gameStart() {
    //初始化全局
    init();
    //result代表有没有定胜负
    map[MAP_SIZE/2][MAP_SIZE/2] = 1;
    showMap(map);
    curOperator = (curOperator + 1) % 2;

    bool result = false;
    while(false == result) {
        //当前旗手下子
        if (curOperator == 1)  result = everyStep();
        else computeEveryStep();
        //更换棋手
        curOperator = (curOperator + 1) % 2;
        maxArray[0] = getMaxDot(1);
        maxArray[2] = getMaxDot(2);

    }
    printf("不服来战？？？y/n");
    char contiFlag;
    scanf("%c", &contiFlag);
    scanf("%c", &contiFlag);
    if ('y' == contiFlag) return true;
    return  false;
}

//当前棋手下棋
bool everyStep() {
    int row,col;
    while(true) {
         printf("旗手%d:请输入恒纵坐标：————",curOperator + 1);
         if(0 == scanf("%d %d",&row,&col)) {
            printf("输入不合法！！");
            continue;
         }
         if (row > 15 || col > 15) {
            printf("超了");
            continue;
         }
         if (0 == map[row][col]) break;
         else printf("坑已经被占了！！！！！\n");
    }

    //改变地图
    map[row][col] = curOperator + 1;
    showMap(map);
    //判断当前选手是否获胜
    if(isWined()) {
        printf("选手%d已经获胜，你才是新一代的棋王，王中王啦啦啦！！",curOperator + 1);
        return true;
    }
    return false;
}

bool computeEveryStep() {
    int row,col;
    int antiDot = computeBestPos((curOperator + 1) %2 + 1, &row, &col) - maxArray[(curOperator + 1) %2];
    int row2,col2;
    int mineDot = computeBestPos(curOperator+1, &row2, &col2) - maxArray[curOperator];
    printf("antiDot:%d   mineDot:%d\n",antiDot,mineDot);
    antiDot -= 100;
    if (mineDot > antiDot || mineDot > 5000) {
        row = row2;
        col = col2;
    }
    //改变地图
    map[row][col] = curOperator  + 1;
    showMap(map);
    printf("电脑下的位置是%d %d\n",row,col);

    /*
    map[row][col] = (curOperator + 1) %2 + 1;
    int secMap[MAP_SIZE][MAP_SIZE];
    initMap(secMap);
    int i,j;
    for(i = 1; i<MAP_SIZE; i++) {
        for(j = 1; j<MAP_SIZE; j++) {
            secMap[i][j] = getMaxDotCurPos(1, i, j);
        }
    }
    showMap2(secMap);
    map[row][col] = curOperator  + 1;
*/
    //判断当前选手是否获胜
    if(isWined()) {
        printf("选手%d已经获胜，你才是新一代的棋王，王中王啦啦啦！！",curOperator + 1);
        return true;
    }
    return false;
}

//检查当前旗手是否获胜
bool isWined() {
    //遍历数组判断当前选手有没有赢
    int curFlag = curOperator + 1;
    int i,j;
    for (i = 0; i<MAP_SIZE; i++) {
        for (j = 0; j<MAP_SIZE; j++) {
            //如果当前的值不是现在选手continue
            if (curFlag != map[i][j]) continue;
            bool curResult = false;
            //左上判断
            curResult |= checkWinDir(-1,-1,i,j);
            //上判断
            curResult |= checkWinDir(-1,0,i,j);
            //右上判断
            curResult |= checkWinDir(-1,1,i,j);
            //左判断
            curResult |= checkWinDir(0,-1,i,j);
            //右判断
            curResult |= checkWinDir(0,1,i,j);
            //左下判断
            curResult |= checkWinDir(1,-1,i,j);
            //下判断
            curResult |= checkWinDir(1,0,i,j);
            //右下判断
            curResult |= checkWinDir(1,1,i,j);
            if(curResult) return true;
        }
    }
    return false;
}

//检查在某个方向上是否获胜
bool checkWinDir(int changeI, int chageJ, int curI, int curJ) {
    bool curResult = false;
    int curNum = 0;
    int addNum = 0;
    for(; curNum < 5; curNum++) {
        if (curI < 1 || curJ < 1) break;
        if (map[curI][curJ] == (curOperator + 1)) addNum++;
        curI += changeI;
        curJ += chageJ;
    }
    if ( 5 == addNum ) return true;
    return curResult;
}


void init() {
    //初始化地图
    initMap(map);
    showMap(map);
    //初始化当前选手
    curOperator = 0;
}


void initMap(int pMap[MAP_SIZE][MAP_SIZE]) {
    int i,j;
    for (i = 0; i<MAP_SIZE; i++) {
        for (j = 0; j<MAP_SIZE; j++) {
            if (i==0 || j==0) {
                pMap[i][j] = i + j;
            } else {
                pMap[i][j] = 0;
            }
        }
    }
}

//打印地图到界面
void showMap(int curMap[MAP_SIZE][MAP_SIZE]) {
    int i,j;
    for (i=0;i<MAP_SIZE;i++){
        for (j=0;j<MAP_SIZE;j++) {
            if (i==0 || j==0) {
                printf("%2d ",curMap[i][j]);
            }
            else {
                if (0 == curMap[i][j]) printf(" . ");
                else if (1 == curMap[i][j]) printf(" O ");
                else (printf(" X "));
            }
        }
        printf("\n");
    }
}

void showMap2(int curMap[MAP_SIZE][MAP_SIZE]) {
    int i,j;
    for (i=0;i<MAP_SIZE;i++){
        for (j=0;j<MAP_SIZE;j++) {
                printf("%2d ",curMap[i][j]);
        }
        printf("\n");
    }
}

int getDotDir(int ope, int changeI, int chageJ, int curI, int curJ, bool* pQiang) {
    int curNum = 0;
    int addNum = 0;
    *pQiang = false;
    curI += changeI;
    curJ += chageJ;
    if (curI < 1 || curJ < 1) {
        return 0;
    }
    if (curI == MAP_SIZE || curJ == MAP_SIZE) {
        return 0;
    }

    for(; curNum < 7; curNum++) {
        if (curI < 1 || curJ < 1) {
            *pQiang = true;
            break;
        }
        if (curI == MAP_SIZE || curJ == MAP_SIZE) {
            *pQiang = true;
            break;
        }
        if (map[curI][curJ] == ope) addNum++;
        else break;
        curI += changeI;
        curJ += chageJ;
    }

    if (map[curI][curJ] == (ope%2 + 1)) *pQiang = true;
    return addNum;
}

int getMaxDotCurPos(int ope, int curI, int curJ) {
    int i = curI;
    int j = curJ;
    bool peng1;
    bool peng2;
    if (map[curI][curJ] != ope) return 0;
    int result = getDotDir(ope,-1,-1,i,j,&peng1) + getDotDir(ope,1,1,i,j,&peng2) + 1;
    if (result != 5) {result -= peng1; result -= peng2;}
    int curResult = getDotDir(ope,-1,0,i,j,&peng1) + getDotDir(ope,1,0,i,j,&peng2) + 1;
    if (curResult != 5) {curResult -= peng1; curResult -= peng2;}
    if (curResult > result) result = curResult;
    curResult = getDotDir(ope,-1,1,i,j,&peng1) + getDotDir(ope,1,-1,i,j,&peng2) + 1;
    if (curResult != 5) {curResult -= peng1; curResult -= peng2;}
    if (curResult > result) result = curResult;
    curResult = getDotDir(ope,0,-1,i,j,&peng1) + getDotDir(ope,0,1,i,j,&peng2) + 1;
    if (curResult != 5) {curResult -= peng1; curResult -= peng2;}
    if (curResult > result) result = curResult;
    //if (4 == result) return 10;
    if (2 == result) return 40;
    if (3 == result) return 60;
    if (4 == result) return 1000;
    if (5 == result) return 999999;
    return result;
}

int computeBestPos(int ope, int* pI, int* pJ) {
    int curMaxDot = 0;
    int otherShouyi = 0;
    int curI = 1;
    int curJ = 1;
    int i,j;
    for (i=1;i<MAP_SIZE;i++){
        for (j=1;j<MAP_SIZE;j++) {
            if (map[i][j] != 0) continue;
            map[i][j] = ope;
            int curDot = getMaxDot(ope);
            if (curDot == curMaxDot) {
                //计算在这点对方的收益
                map[i][j] = (ope%2) + 1;
                int curOtherShouyi = getMaxDot((ope%2) + 1);
                map[i][j] = ope;
                if (curOtherShouyi > otherShouyi) {
                    curI = i;
                    curJ = j;
                    otherShouyi = curOtherShouyi;
                }
            }
            if (curDot > curMaxDot) {
                curMaxDot = curDot;
                curI = i;
                curJ = j;
                map[i][j] = (ope%2) + 1;
                otherShouyi = getMaxDot((ope%2) + 1);
                map[i][j] = ope;
            }
            map[i][j] = 0;
        }
    }
    *pI = curI;
    *pJ = curJ;
    return curMaxDot;
}

int getMaxDot(int ope) {
    int maxDot = 0;
    int i,j;
    for (i=1;i<MAP_SIZE;i++){
        for (j=1;j<MAP_SIZE;j++) {
            maxDot += getMaxDotCurPos(ope, i, j);
        }
    }
    return maxDot;
}

