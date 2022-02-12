#include<stdio.h>

void draw(char **field);    //отрисовка поля
void add(char **field, char **start, int x, int y, int lx, int ly);   //добавляем стартовую позицию
void in_old(char **field, char **field_old);
int process(char **field); //процесс игры
int input();

int main() {
    int x, y, lx = 20, ly = 10;
    char field[25][80], start[ly][lx], field_old[25][80];
    add((char **) field, (char **) start, x, y, lx, ly);
    draw((char **) field);
    in_old((char **) field, (char **) field_old);
    while (1) {
        if (input()) {
            if (process((char **) field)) {
                in_old((char **) field, (char **) field_old);
                draw((char **) field);
            } else {
                return 0;
            }
        }
        draw((char **) field);
    }

}

int input() {
    int flag = 0;
    char c;
    int scan = scanf("%c", &c);
    if ( scan != 1 || c != ' ' ) {
        flag = 1;
    }
    char d = getchar();
    if ( d != '\n' && d != EOF ) {
        flag = 1;
    }
     return flag;
}

void in_old(char **field, char **field_old) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            field_old[i][j] = field[i][j];
}

void add(char **field, char **start, int x, int y, int lx, int ly) {}

void draw(char **field) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++) {
            if (i == 24 && j == 79) {
                printf("%c", field[i][j]);
                break;
            }
            if (j == 79) {
                printf("%c\n", field[i][j]);
                break;
            }
            printf("%c", field[i][j]);
        }
}

int process(char **field, char d, char l) {}