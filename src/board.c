#include "board.h"
#include <stdio.h> 

int board[SIZE][SIZE]; 

void initBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard() {
    printf("  ");
    for (int i = 0; i < SIZE; i++) printf("%2d ", i + 1); // 列号
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1); // 行号
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) printf(" + ");
            else if (board[i][j] == 1) printf(" ● ");
            else printf(" ○ ");
        }
        printf("\n");
    }
}