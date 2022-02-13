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
    int flag = 1;
    char c;
    int scan = scanf("%c", &c);
    if ( scan != 1 || c != ' ' ) {
        flag = 0;
    }
    char d = getchar();
    if ( d != '\n' && d != EOF ) {
        flag = 0;
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

int process(char **field, char d, char l) {
    for (int k = 0; k < 25; k++) {
        for (int t = 0; t< 80; t++) {
            if (field[k][t] = d) {
                dead(field[k][t], **field);
                }
            if (field[k][t] = l) {
                live(field[k][t], **field);
            }
        }
    } return 0;
}

void dead(char field[m][n], char **field) {
    int count = 0;
    for (int i = m - 1; i <= m + 1; i++) {
        for (int j = n - 1; j <= n + 1; j++) {
            if (i < 0) {
                i = 24;
            }
            if (i > 24) {
                i = 0;
            }
            if (j < 0) {
                j = 79;
            }
            if (j > 79) {
                j = 0;
            }
            if (field [i][j] = l) {
                count++;
            }
        }
    } if (count = 3) {
        field[m][n] = l;
    }
}

void live(char field[m][n], char **field) {
    int count = -1;
    for (int i = m - 1; i <= m + 1; i++) {
        for {int j = n - 1}; j <= n + 1; j++) {
            if (i < 0) {
                i = 24;
            }
            if (i > 24) {
                i = 0;
            }
            if (j < 0) {
                j = 79:
            }
            if (j > 79) {
                j = 0:
            }
            if (field[i][j] = l) {
                count++;
            }
        }
    } if (count < 2 || count > 3) {
            field[m][n] = d;
    }
}