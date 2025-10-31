#define _CRT_SECURE_NO_WARNINGS
#define HEIGHT 16
#define WIDTH 30
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

char go;
short x = 0;
short y = 0;
short hp = 100;
char field[HEIGHT][WIDTH];
struct termios oldt, newt;

void display_hp(void);
void input(void);
void init(void) {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("\033[?25l");
}


int main(void) {
    init();

    while (1) {
        system("clear");
        for (short i = 0; i < HEIGHT; i++) {
            for (short j = 0; j < WIDTH; j++) {
                field[i][j] = '.';
            }
        }
        field[x][y] = '@';

        for (short i = 0; i < HEIGHT; i++) {
            for (short j = 0; j < WIDTH; j++) {
                printf("%c", field[i][j]);
            }
            printf("\n");
        }

        display_hp();
        if (hp == 0) {
            system("clear");
            printf("\nGAME OVER\n");
            goto end;
        }

        input();
    }

        end:
        return 0;

}

void input(void) {
    read(STDIN_FILENO, &go, 4);
    if (go == 'w') {
        if (x > 0) x--;
    }  else if (go == 'a') {
        if (y > 0) y--;
    }  else if (go == 's') {
        if (x < HEIGHT - 1) x++;
    }  else if (go == 'd') {
        if (y < WIDTH - 1) y++;
    }
}

void display_hp(void) {
    printf("\n    [%d / 100]", hp);
    printf("\nHP: ");
    for (short i = 1; i <= (short)(hp / 4) + 1; i++) {
        printf("#");
    } printf("\n");
}