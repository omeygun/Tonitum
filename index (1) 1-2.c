#include<stdio.h>

#include<stdlib.h>

#include <time.h>

#include<locale.h>

#define PlayerMax 4
#define bmax 15

#define linux 0
#define windows 1



void clearscreen() {
    if (linux) {
        system("clear");
    } else if (windows) {
        system("cls");
    }
}

char get1char() {
    char inp;
    if (linux) {
        system("/bin/stty raw");
        inp = getc(stdin);
        system("/bin/stty cooked");
    }
    if (windows) {
        inp = getch();
    }
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
                printf(">\033[0;31m*\033[0;0m<");
                break;
            case 'e':
                printf(" \033[0;32m*\033[0;0m ");
                error = 1;
                break;
            case 'c':
                printf(" \033[0;31m*\033[0;0m ");
                break;
            case 'h':
                printf(" \033[0;33m*\033[0;0m ");
                break;
            case 'm':
                printf(" \033[0;34m*\033[0;0m ");
                break;
            case '~':
                printf(" * ");
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

int pickboat(int blen, char board[bmax][bmax], int bsize) {
    char inp = '0', ogchar = '~', status = 1;
    int dirx[] = {
        -1,
        0,
        1,
        0
    };
    int diry[] = {
        0,
        1,
        0,
        -1
    };
    int by = 0, bx = 0;
    ogchar = board[by][bx];
    if (ogchar == 'c') {
        board[by][bx] = 'e';
    } else {
        board[by][bx] = 'c';
    }
    while (inp != 'x') {

        InitMenu();
        printf("pick starting point:\n\n");
        status = showboard(board, bsize);

        inp = get1char();

        if (inp == 'w') {
            board[by][bx] = ogchar;
            by = max(by - 1, 0);
            ogchar = board[by][bx];
            if (board[by][bx] == 'c') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'c';
            }
        } else if (inp == 'a') {
            board[by][bx] = ogchar;
            bx = max(bx - 1, 0);
            ogchar = board[by][bx];
            if (board[by][bx] == 'c') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'c';
            }
        } else if (inp == 's') {
            board[by][bx] = ogchar;
            by = min(bsize-1, by + 1);
            ogchar = board[by][bx];
            if (board[by][bx] == 'c') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'c';
            }
        } else if (inp == 'd') {
            board[by][bx] = ogchar;
            bx = min(bsize-1, bx + 1);
            ogchar = board[by][bx];
            if (board[by][bx] == 'c') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'c';
            }
        } else if (inp == 'x' && status == -1) {
            return -1;
        }

        //printf("%c",inp);
    }
    inp = '0';
    int orien = 0;
    char ogc[bsize];
    int dx = bx + dirx[orien] * blen;
    int dy = by + diry[orien] * blen;
    while (inp != 'x') {
        InitMenu();

        int ome;
        while (1) {
            InitMenu();
            showboard(board, bsize);
            dx = bx + dirx[orien] * blen;
            dy = by + diry[orien] * blen;
            if (dx >= -1 && dx < bsize + 1 && dy >= -1 && dy < bsize + 1) {
                int p = bx, q = by, m = 0;
                while (!(p == dx && q == dy)) {
                    ogc[m] = board[q][p];
                    if (board[q][p] == '~' || m == 0) {
                        board[q][p] = 'c';
                    } else {
                        board[q][p] = 'e';
                    }
                    m++;
                    p = p + dirx[orien];
                    q = q + diry[orien];
                }

                break;
            } else {
                orien = (orien + 1) % 4;
            }
        }

        ome = orien;

        InitMenu();
        status = showboard(board, bsize);

        inp = get1char();

        if (inp == 'd') {
            orien++;
        } else if (inp == 'a') {
            orien--;
        } else if (inp == 'x') {
            if (status == -1) {
                return -1;
            } else {
                break;
            }
        } else if (inp == 'r') {
            return -1;
        }

        orien = (orien + 4) % 4;

        if (dx >= -1 && dx < bsize + 1 && dy >= -1 && dy < bsize + 1) {
            int p = bx, q = by, m = 0;
            while (!(p == dx && q == dy)) {
                board[q][p] = ogc[m];
                m++;
                p = p + dirx[ome];
                q = q + diry[ome];
            }
        }
    }

}

void SetBoard(int nboard, char board[PlayerMax][bmax][bmax], char names[PlayerMax][11], int bsize, int Boatlen[], int nboats) {
    InitMenu();
    //Set options
    //Initialize the board to be 0

    //Iterate through players
    for (int i = 0; i < nboard; i++) {
        //Get name of player
        InitMenu();

        printf("player #%d enter your name(max 10 char, no spaces): ", i + 1);
        scanf("%s", names[i]);
        //Set each boats position
        for (int j = 0; j < nboats; j++) {
            if (pickboat(Boatlen[j], board[i], bsize) == -1) {
                for (int p = 0; p < bsize; p++) {
                    for (int q = 0; q < bsize; q++) {
                        board[i][p][q] = '~';
                    }
                }
                j = -1;
                continue;
            }

        }

    }
}

void InitBoards(char board[PlayerMax][bmax][bmax], char seeboard[PlayerMax][PlayerMax][bmax][bmax], int lives[PlayerMax], int boatlife) {
    for (int i = 0; i < PlayerMax; i++) {
        lives[i] = boatlife;
        for (int j = 0; j < PlayerMax; j++) {
            for (int p = 0; p < bmax; p++) {
                for (int q = 0; q < bmax; q++) {
                    seeboard[i][j][p][q] = '~';
                }
            }
        }
        for (int p = 0; p < bmax; p++) {
            for (int q = 0; q < bmax; q++) {
                board[i][p][q] = '~';
            }
        }
    }
}

int pickpoint(char board[bmax][bmax], int bsize, int * x, int * y, char * qtext) {
    char inp = '0', ogchar = '~', status = 1;
    int dirx[] = {
        -1,
        0,
        1,
        0
    };
    int diry[] = {
        0,
        1,
        0,
        -1
    };
    int by = 0, bx = 0;
    ogchar = board[by][bx];
    if (ogchar == 'p') {
        board[by][bx] = 'e';
    } else {
        board[by][bx] = 'p';
    }
    while (inp != 'x') {

        InitMenu();
        printf("%s\n\n", qtext);
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
            by = min(bsize-1, by + 1);
            ogchar = board[by][bx];
            if (board[by][bx] == 'p') {
                board[by][bx] = 'e';
            } else {
                board[by][bx] = 'p';
            }
        } else if (inp == 'd') {
            board[by][bx] = ogchar;
            bx = min(bsize-1, bx + 1);
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

void play(char board[PlayerMax][bmax][bmax], char seeboard[PlayerMax][PlayerMax][bmax][bmax], char names[PlayerMax][11], int nplayers, int bsize, int lives[PlayerMax]) {
    int winner = -1, Player = 0,opponent,x1,y1,x,y,status;
    int RPlayer = nplayers,item,itemnow='-';
    char attacktext[100];
    char itemnames[3] = {'R','^','|'};
    int asize[nplayers];
    for(int i=0;i<nplayers;i++){
        asize[i]=1;
    }
    while (winner == -1) {
        if (lives[Player] == 0) {
            Player = (Player + 1) % nplayers;
            continue;
        }
        InitMenu();
        printf("scoreboard:\n");
        RPlayer = 0;
        for (int i = 0; i < nplayers; i++) {
            printf("%s : %d\n", names[i], lives[i]);
            if (lives[i] != 0) {
                RPlayer++;
            }
        }
        if (RPlayer == 1) {
            for (int i = 0; i < nplayers; i++) {
                if (lives[i] != 0) {
                    winner = i;
                    break;
                }
            }
            break;
        }
        printf("%s's turn\n(press any key to continue...)", names[Player]);
        get1char();
        int attack;
        char aops[4][11] = {
            "Shoot",
            "Charge",
            "Spin",
            "Use"
        };
        attack = SelectPlayer("Select what you want to do\n", 4, aops);
        if (attack == 0) {

            opponent = -1,x1,y1,x,y, status = 1;
            opponent = SelectPlayer("Select the player to attack\n", \
                nplayers, names);

            while (opponent == Player) {
                printf("Don't pick yourself!! >:(\n(press any key to continue...):");
                get1char();
                opponent = SelectPlayer("Select the player to attack\n", \
                    nplayers, names);
            }
            shootagain:

                snprintf( attacktext, 100, "Pick a position to attack(attack size is %d).",asize[Player] );
                status = pickpoint(seeboard[Player][opponent], bsize, &x1, &y1, \
                    attacktext);

            for(int i=0;i<asize[Player];i++){
                for(int j=0;j<asize[Player];j++){
                    x=x1+i;
                    y=y1+j;
                    if(!(x>=0 && x<bsize && y>=0 && y<bsize)){
                        break;
                    }

            if (board[opponent][y][x] == 'c') {
                InitMenu();
                seeboard[Player][opponent][y][x] = 'h';
                board[opponent][y][x] = 's';
                showboard(seeboard[Player][opponent], bsize);
                lives[opponent]--;
                printf("YOU HIT A BOAT :O\n(press any key to continue...):\n");
                get1char();
                printf("%s now has %d boat tile(s) left :O\n(press any key to continue...):\n", names[opponent], lives[opponent]);
                get1char();
                if(asize[Player]==1){
                    printf("You get to shoot again :> \n(press any key to continue...):\n");
                    get1char();
                    goto shootagain;
                }
            } else if (board[opponent][y][x] == 's') {
                InitMenu();
                seeboard[Player][opponent][y][x] = 'h';
                showboard(seeboard[Player][opponent], bsize);
                printf("YOU HIT A BOAT :O\n(press any key to continue...):\n");
                get1char();
                printf("But that boat was already hit :( \n(press any key to continue...):\n");
                get1char();
                printf("%s now has %d boat tile(s) left :O\n(press any key to continue...):\n", names[opponent], lives[opponent]);
                get1char();
            } else {
                InitMenu();
                seeboard[Player][opponent][y][x] = 'm';
                showboard(seeboard[Player][opponent], bsize);
                printf("YOU MISSED :P\n(press any key to continue...):\n");
                get1char();
            }
                }
            }
            asize[Player]=1;

        }
        else if(attack==1){
            asize[Player]=min(asize[Player]+1,3);
            printf("Attack size is now %d(max 3)\n(press any key to continue...):\n",asize[Player]);
            get1char();
        }
        else if(attack==2){
            srand(time(0));
            item = rand()%3;
            printf("You got %c !!!!\n(press any key to continue...):\n",itemnames[item]);
            get1char();
            itemnow = itemnames[item];
        }
        else if(attack==3){
            switch(itemnow){
            case 'R':
                snprintf( attacktext, 100, "Pick a position to attack(attack size is %d).",asize[Player] );
                opponent = SelectPlayer("Select the player to attack\n",nplayers, names);
                pickpoint(seeboard[Player][opponent], bsize, &x1, &y1, attacktext);

                for(int i=0;i<5;i++){
                    for(int j=0;j<5;j++){
                        x = x1+i;
                        y = y1+j;
                        if(x>=0 && x<bsize && y>=0 && y<bsize){
                            if(board[opponent][y][x]=='~'){
                                seeboard[Player][opponent][y][x]='m';
                            }
                            else {
                                seeboard[Player][opponent][y][x] = board[opponent][y][x];
                            }
                        }

                    }
                }
                InitMenu();
                showboard(seeboard[Player][opponent],bsize);
                printf("Press anywhere to continue");
                get1char();
                break;
            case '^':
                asize[Player]=4;
                break;
            case '|':
                opponent = SelectPlayer("Select the player to attack\n",nplayers, names);
                asize[opponent]=0;
                break;
            }
        }

        Player = (Player + 1) % nplayers;
    }
    printf("%s IS THE WINNER !!!!\n", names[winner]);
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-16");
    int nplayers, bsize;
    char board[PlayerMax][bmax][bmax];
    char seeboard[PlayerMax][PlayerMax][bmax][bmax];
    char names[PlayerMax][11];
    int lives[PlayerMax];
    int Boatlen[] = {
        5,
        3,
        3,
        3
    };
    int Boatlife = 14, nboats = sizeof(Boatlen) / sizeof(Boatlen[0]);
    InitBoards(board, seeboard, lives, Boatlife);
    //Initialize the interface.
    InitMenu();
    //Get some options
    GetOptions( & nplayers, & bsize);

    //Let each players initialize their board
    SetBoard(nplayers, board, names, bsize, Boatlen, nboats);
    play(board, seeboard, names, nplayers, bsize, lives);
}
/*

*/
