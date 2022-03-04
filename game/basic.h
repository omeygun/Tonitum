#include<stdio.h>

#include<stdlib.h>

#include <time.h>

#include<locale.h>

#define PlayerMax 4
#define bmax 15

#define linux 1
#define windows 0

void clearscreen() {
    if (linux) {
        system("clear");
    }
}

char get1char() {
    char inp;
    system("/bin/stty raw");
    inp = getc(stdin);
    system("/bin/stty cooked");
    printf("\b \b");
    return inp;
}

void InitMenu() {
    clearscreen();
    //open startup.txt then print the startup text
    FILE * fptr = fopen("startup.txt", "r");
    char menu[200];
    while (fgets(menu, 100, fptr)) {
        printf("%s", menu);
    }
}

int min(int a, int b) {
    if (a > b) {
        return b;
    } else return a;
}

int max(int a, int b) {
    if (a < b) {
        return b;
    } else return a;
}

int SelectFromOp(char * qtext, int opsize, int playersOp[]) {

    char inp = '0';

    int cursor = 0;
    while (inp != 'x') {

        InitMenu();

        printf("%s", qtext);
        for (int i = 0; i < opsize; i++) {
            printf("- %d ", playersOp[i]);
            if (i == cursor) {
                printf("<-");
            }
            printf("\n");
        }
        /*
        system("/bin/stty raw");
        inp = getc(stdin);
        system("/bin/stty cooked");
        */
        inp = get1char();
        if (inp == 's') {
            cursor = min(cursor + 1, opsize - 1);
        }
        if (inp == 'w') {
            cursor = max(cursor - 1, 0);
        }
    }

    return playersOp[cursor];
}

int SelectPlayer(char * qtext, int opsize, char playersNames[PlayerMax][11]) {

    char inp = '0';

    int cursor = 0;
    while (inp != 'x') {

        InitMenu();

        printf("%s", qtext);
        for (int i = 0; i < opsize; i++) {
            printf("- %s ", playersNames[i]);
            if (i == cursor) {
                printf("<-");
            }
            printf("\n");
        }
        /*
        system("/bin/stty raw");
        inp = getc(stdin);
        system("/bin/stty cooked");
        */
        inp = get1char();
        if (inp == 's') {
            cursor = min(cursor + 1, opsize - 1);
        }
        if (inp == 'w') {
            cursor = max(cursor - 1, 0);
        }
    }

    return cursor;
}

void GetOptions(int * np, int * bs) {
    //Set the available options
    int playersOp[] = {
        2,
        4
    };
    int boardOp[] = {
        10,
        15
    };
    //Get the initial options from the players

    * np = SelectFromOp("How many players are playing?(w to select up, s to select down)\n", \
        sizeof(playersOp) / sizeof(int), playersOp);

    * bs = SelectFromOp("What board size?(w to select up, s to select down)\n", \
        sizeof(boardOp) / sizeof(int), boardOp);
}

int showboard(char board[bmax][bmax], int bsize) {
    int error = 0;
    for (int i = 0; i < bsize; i++) {
        for (int j = 0; j < bsize; j++) {
            switch (board[i][j]) {
            case 'p':
                printf(">\033[0;35m*\033[0;0m<"); //red
                break;
            case 'e':
                error = 1;
                printf(" \033[0;31mO\033[0;0m "); //green
                break;
            case 'c':
                printf(" \033[0;32mO\033[0;0m "); //green
                break;
            case 's':
                printf(" \033[0;31mX\033[0;0m "); //red
                break;
            case 'h':
                printf(" \033[0;33m\u2588\033[0;0m "); //yellow
                break;
            case 'm':
                printf(" \033[0;34m~\033[0;0m "); //blue
                break;
            case 'M':
                printf(" \033[0;33m~\033[0;0m "); //yellow
                break;
            case 'C':
                printf(" \033[0;33mO\033[0;0m "); //yellow
                break;
            case '~':
                printf(" - ");
                break;
            default:
                printf(" = ");
                break;
            }
        }
        printf("\n\n");
    }
    if (error) {
        printf("Warning: there this boat has intersection\nYou cannot choose this\nYou will have to choose again\n");
        return -1;
    }
    return 0;
}

int pickpoint(char board[bmax][bmax], int bsize, int * x, int * y, char * qtext) {
    char inp = '0', ogchar = '~', status = 1;
    int by = 0, bx = 0;
    ogchar = board[by][bx];
    if (ogchar == 'p') {
        board[by][bx] = 'e';
    } else {
        board[by][bx] = 'p';
    }
    while (inp != 'x') {

        InitMenu();
        printf("%s", qtext);
        status = showboard(board, bsize);

        inp = get1char();

        if (inp == 'w') {
            board[by][bx] = ogchar;
            by = max(by - 1, 0);
            ogchar = board[by][bx];
            if (board[by][bx] == 'p') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'p';
            }
        } else if (inp == 'a') {
            board[by][bx] = ogchar;
            bx = max(bx - 1, 0);
            ogchar = board[by][bx];
            if (board[by][bx] == 'p') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'p';
            }
        } else if (inp == 's') {
            board[by][bx] = ogchar;
            by = min(bsize - 1, by + 1);
            ogchar = board[by][bx];
            if (board[by][bx] == 'p') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'p';
            }
        } else if (inp == 'd') {
            board[by][bx] = ogchar;
            bx = min(bsize - 1, bx + 1);
            ogchar = board[by][bx];
            if (board[by][bx] == 'p') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'p';
            }
        } else if (inp == 'x' && status == -1) {
            return -1;
        }

        //printf("%c",inp);
    }
    board[by][bx] = ogchar;
    * x = bx;
    * y = by;
    return 1;
}