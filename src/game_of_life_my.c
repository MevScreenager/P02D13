#include<stdio.h>
#include<stdlib.h>

void draw(char **field);    //отрисовка поля
void add(char **field, char **start, int x, int y, int lx, int ly);   //добавляем стартовую позицию
int process(char **field, char ** field_old, char d, char l); //процесс игры
void in_old(char **field, char **field_old);
int input();

int main() {
    int x = 0, y = 0, lx = 20, ly = 10, progress = 1;
    char **field = (char**) malloc(sizeof(char*) * 25), 
         **start = (char**) malloc(sizeof(char*) * ly), 
         **field_old = (char**) malloc(sizeof(char*) * 25), d = ' ', l = '0';
    for (int i = 0; i < ly; i++) {
        start[i] = (char*) malloc(sizeof(char) * lx);
        for (int j = 0; j < lx; j++)
            start[i][j] = l;
    }
    for (int i = 0; i < 25; i++) {
        field[i] = (char*)malloc(sizeof(char) * 80);
        field_old[i] = (char*)malloc(sizeof(char) * 80);
        for (int j = 0; j < 80; j++) {
            field[i][j] = d;
            field_old[i][j] = d;
        }
    }
    // x = 0;
    // y = 0;
    add((char **) field, (char **) start, x, y, lx, ly);
    in_old((char **) field, (char **) field_old);
    draw(field);
    
    while (1) {
        if (input()) {
            // if (progress) {
            //     progress = process((char **) field, (char **) field_old, d, l);
            //     draw(field);
            // }
            progress = 1;
            if (process((char **) field, (char **) field_old, d, l)) {
                in_old((char **) field, (char **) field_old);
                draw((char **) field);
            } 
            else {
                for(int i = 0; i < 25; i++) {
                    if (i < ly)
                        free(start[i]);
                    free(field[i]);
                    free(field_old[i]);
                }
                free(field);
                free(field_old);
                return 0;
            }
        }
        draw((char **) field);
    }
    for(int i = 0; i < 25; i++) {
        if (i < ly)
            free(start[i]);
        free(field[i]);
        free(field_old[i]);
    }
    free(field);
    free(field_old);
}

int input() {
    int flag = 1;
    char c;
    int scan = scanf("%c", &c);
    scan = 1;
    // if ( scan != 1 || c != ' ' ) {
    //     flag = 0;
    // }
    // char d = getchar();
    // if ( d != '\n' && d != EOF ) {
    //     flag = 0;
    // }
     return flag;
}

void in_old(char **field, char **field_old) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            field_old[i][j] = field[i][j];
}

void add(char **field, char **start, int x, int y, int lx, int ly) {
    for (int i = y; i < ly + y; i++)
        for (int j = x; j < lx + x; j++) {
            if (i >= y && j >= x && i < y + ly && j < x + lx)
                field[i][j] = start[i - y][j - x];
        }
}

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

int process(char **field, char ** field_old, char d, char l) {
    int flag = 0, count;
    flag = 0;
    // for (int i = 0; i < 25; i++)
    //     for (int j = 0; j < 80; j++)
    //         if (field[i][j] == field_old[i][j])
    //             flag++;
    // if (flag == 25 * 80) return 0;

    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++) {
            int y[8] = { i - 1, i - 1, i - 1, i, i, i + 1, i + 1, i + 1 }, 
                x[8] = { j - 1, j, j + 1, j - 1, j + 1, j - 1, j, j + 1 };
            
            for (int t = 0; t < 8; t++) {
                if (t < 3 && y[t] < 0) y[t] = 24;
                if (t > 4 && y[t] > 24) y[t] = 0;
                if ((t == 0 || t == 3 || t == 5) && x[t] < 0) x[t] = 79;
                if ((t == 2 || t == 4 || t == 7) && x[t] > 79) x[t] = 0;
            }

            count = 0;
            for (int k = 0; k < 8; k++)
                if (field[y[k]][x[k]] == l)
                    count++;

            if (field_old[i][j] == d && count == 3)
                field[i][j] = l;
            if (field_old[i][j] == l && (count < 2 || count > 3))
                field[i][j] = d;
        }
    return 1;
}

// int input() {
//     char c_1, c_2;
//     scanf("%c%c", &c_1, &c_2);
//     if ((int) c_1 == 32 && (int) c_2 == 10) return 1;
//     return 0;
// }