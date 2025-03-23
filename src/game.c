#include "game.h"
#include "board.h"  

int currentPlayer = 1;  


int checkWin(int x, int y) {
    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
    int color = board[x][y];

    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0], dy = directions[d][1];
        int count = 1;

   
        for (int i = 1; ; i++) {
            int nx = x + dx * i, ny = y + dy * i;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || board[nx][ny] != color) break;
            count++;
        }

    
        for (int i = 1; ; i++) {
            int nx = x - dx * i, ny = y - dy * i;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || board[nx][ny] != color) break;
            count++;
        }

        if (count >= 5) return 1;
    }
    return 0;
}


void switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}