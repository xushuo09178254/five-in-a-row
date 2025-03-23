//长连禁手: 黑子落子后形成6颗或更多连续的棋子(无论是否被阻挡)
//双活三禁手:黑子落棋后同时形成两个或多个活三
//双四禁手:黑子落棋后同时形成两个或多个活四

#include <stdio.h>
#define SIZE 15

//长连
int board[SIZE][SIZE];
int isOverline(int x, int y, int player) {
    if (player != 1) return 0; 
    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0], dy = directions[d][1];
        int count = 1;
        for (int i = 1; ; i++) {
            int nx = x + dx * i, ny = y + dy * i;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || board[nx][ny] != player) break;
            count++;
        }
        for (int i = 1; ; i++) {
            int nx = x - dx * i, ny = y - dy * i;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || board[nx][ny] != player) break;
            count++;
        }
        if (count > 5) return 1; 
    }
    return 0;
}

//活三
int isOpenThree(int x, int y, int dx, int dy, int player) {
    int nx = x + dx * 3, ny = y + dy * 3;
    if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == 0) {
        if (board[x+dx][y+dy] == player && 
            board[x+dx*2][y+dy*2] == player &&
            board[x+dx*3][y+dy*3] == 0) {
            return 1;
        }
    }
    return 0;
}

//双活三
int isDoubleThree(int x, int y, int player) {
    if (player != 1) return 0;
    int threeCount = 0;
    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0], dy = directions[d][1];
        if (isOpenThree(x, y, dx, dy, player)) threeCount++;
        if (threeCount >= 2) return 1; 
    }
    return 0;
}

//活四
int isFour(int x, int y, int dx, int dy, int player) {
    int count = 0;
    int emptyEnds = 0;
    for (int i = 1; i <= 4; i++) {
        int nx = x + dx * i, ny = y + dy * i;
        if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE) break;
        if (board[nx][ny] == player) count++;
        else if (board[nx][ny] == 0) { emptyEnds++; break; }
        else break;
    }

    return (count == 4 && emptyEnds >= 1); 
}

// 四四
int isDoubleFour(int x, int y, int player) {
    if (player != 1) return 0;
    int fourCount = 0;
    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0], dy = directions[d][1];
        if (isFour(x, y, dx, dy, player)) fourCount++;
        if (fourCount >= 2) return 1; 
    }
    return 0;
}