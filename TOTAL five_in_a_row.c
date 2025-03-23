#include <stdio.h>
#define SIZE 15

int board[SIZE][SIZE];  // 棋盘（0-空，1-黑，2-白）,棋盘数组
int currentPlayer = 1;   // 当前玩家（1黑方，2白方）

// 初始化棋盘
void initBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0; //所有位置初始化为空(0)
        }
    }
}

// 打印棋盘（带行列号）
void printBoard() {
    printf("  ");
    for (int i = 0; i < SIZE; i++) printf("%2d ", i + 1); // 打印列号 %2控制数字控制输出宽度，保持对齐。
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1); // 打印行号
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) printf(" + ");
            else if (board[i][j] == 1) printf(" ● ");
            else printf(" ○ ");
        }
        printf("\n");
    }
}

// 检查是否五连（核心逻辑）
int checkWin(int x, int y) {
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向 垂直向下 水平向右 右下斜线 左下斜线 
    //如竖直 {1,0} dx = 1  dy = 0 设落子为(3,3) 从当前点向下延展(行号增加，列号不变)
    //垂直覆盖上下
    //水平覆盖左右
    //右下斜线覆盖右上左下
    //左下斜线覆盖左上右下
    int color = board[x][y];

    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0], dy = directions[d][1];
        int count = 1;

        // 正向检查
        for (int i = 1; ; i++) {
            int nx = x + dx * i, ny = y + dy * i;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || board[nx][ny] != color) break;//判断是否越界
            count++;
        }
        // 反向检查
        for (int i = 1; ; i++) {
            int nx = x - dx * i, ny = y - dy * i;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || board[nx][ny] != color) break;
            count++;
        }
        if (count >= 5) return 1;
    }
    return 0;
}

// 获取玩家输入（带错误处理）
int getInput(int *x, int *y) {
    printf("当前玩家：%s,请输入坐标（行 列）：", currentPlayer == 1 ? "黑方●" : "白方○");
    //三元运算符 条件 ？ 表达式1 ：表达式2  如果条件为真则整个表达式的结果是表达式一；否则结果为表达式二 
    int inputX, inputY;
    if (scanf("%d %d", &inputX, &inputY) != 2) { // 输入格式错误
        //scanf函数返回值基本规则是:成功匹配并赋值的输入项数量，成功读取两个数返回值为2
        while (getchar() != '\n'); // 清空输入缓冲区  //会不断读取缓冲区的残留字符，直到遇见\n
        printf("输入错误！请重新输入。\n");
        return 0;
    }

    *x = inputX - 1;
    *y = inputY - 1;
    //坐标转换
    //即将玩家输入1-based坐标棋盘显示的行列号1~15转化为based坐标数组下标1~14

    // 检查坐标是否合法
    if (*x < 0 || *x >= SIZE || *y < 0 || *y >= SIZE) {
        printf("坐标超出范围！\n");
        return 0;
    }
    //检查坐标是否在棋盘范围内

    if (board[*x][*y] != 0) {
        printf("此处已有棋子！\n");
        return 0;
    }
    return 1;
    //检查该位置是否为空(即是是否可以落子)
}
//返回1代表合法
//返回2代表不合法，主循环会要求重新输入

int main() {
    initBoard();
    int x, y;

    while (1) {
        printBoard();
        if (!getInput(&x, &y)) continue;

        board[x][y] = currentPlayer;
        if (checkWin(x, y)) {
            printBoard();
            printf("玩家 %s 获胜！\n", currentPlayer == 1 ? "黑方●" : "白方○");
            break;
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1; // 切换玩家 三元运算
    }
    return 0;
}