#include "input.h"
#include <stdio.h>

int getInput(int *x, int *y) {
    printf("当前玩家：%s,请输入坐标（行 列）：", currentPlayer == 1 ? "黑方●" : "白方○");
    int inputX, inputY;
    if (scanf("%d %d", &inputX, &inputY) != 2) {
        while (getchar() != '\n'); 
        printf("输入错误！请重新输入。\n");
        return 0;
    }
    *x = inputX - 1;
    *y = inputY - 1;
    if (*x < 0 || *x >= SIZE || *y < 0 || *y >= SIZE) {
        printf("坐标超出范围！\n");
        return 0;
    }
    if (board[*x][*y] != 0) {
        printf("此处已有棋子！\n");
        return 0;
    }
    return 1;
}