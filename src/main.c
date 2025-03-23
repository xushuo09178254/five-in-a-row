#include "board.h"
#include "game.h"
#include "input.h"

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
        switchPlayer();    
    }
    return 0;
}