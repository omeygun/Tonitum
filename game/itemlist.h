#include<stdio.h>

#define bmax 15
#define PlayerMax 4
#include"basic.h"

void reveal(char seeboard[bmax][bmax], char opponentBoard[bmax][bmax], int bsize, int x1, int y1) {
    //reveal 5 x 5
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = x1 + i;
            int y = y1 + j;
            if (x >= 0 && x < bsize && y >= 0 && y < bsize) {
                if (opponentBoard[y][x] == '~') {
                    seeboard[y][x] = 'm';
                } else {
                    seeboard[y][x] = opponentBoard[y][x];
                }
            }
        }
    }

}
void bruh(char item[2], int * charge) {
    * charge = -1;
    item[0] = '-';
    item[1] = '-';
    printf("Press anywhere to continue");
    get1char();
}
void superMissile(int * charge) {
    * charge = 4;
    printf("Press anywhere to continue");
    get1char();
}
void barrier(char board[bmax][bmax], int bsize, int x1, int y1) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = x1 + i;
            int y = y1 + j;
            if (x >= 0 && x < bsize && y >= 0 && y < bsize) {
                if (board[y][x] != 'r' && board[y][x] != 'B' && board[y][x] != 'G') {
                    if (board[y][x] == 'b')
                        board[y][x] == 'B';
                    else if (board[y][x] == 'g')
                        board[y][x] == 'G';
                }
            }
        }
    }
    InitMenu();
    showboard(board, bsize);
    printf("Protection installed successfully.../n");
    printf("Press anywhere to continue");
    get1char();
}
void nuke(int * charge) {
    * charge = 10;
    printf("Now it's time to CHECKMATE!\n");
    printf("Press anywhere to continue");
    get1char();
}
void nothing() {
    printf("Press anywhere to continue");
}
void thunderstorm(int * p) {
    * p = -1;
    printf("Press anywhere to continue");
}
void disturb(char item[2]) {
    item[0] = '-';
    item[1] = '-';
    printf("มึงแม่งชาติชั่ว ขอให้มึงโดนเหมือนกันเร็วๆ/n");
    printf("Press anywhere to continue");
}