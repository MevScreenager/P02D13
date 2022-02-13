#include<stdio.h>
#include<stdlib.h>

void draw(char **field);    //отрисовка поля
void add(char **field, char **start, int x, int y, int lx, int ly);   //добавляем стартовую позицию
int process(char **field, char ** field_old, char ** field_old_old, char d, char l, int time); //процесс игры
void in_old(char **field, char **field_old);
int input();
void clean(char **arr, int n);

int main() {
    int x = 20, y = 10, lx = 3, ly = 3;
    char **field = (char**) malloc(sizeof(char*) * 25),
         **start = (char**) malloc(sizeof(char*) * ly),
        //  start[3][lx] = { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} },
         **field_old = (char**) malloc(sizeof(char*) * 25),
         **field_next = (char**) malloc(sizeof(int*) * 25), d = ' ', l = '0';
    for (int i = 0; i < ly; i++) {
        start[i] = (char*) malloc(sizeof(char) * lx);
        for (int j = 0; j < lx; j++) {
            if (j == 1 || i == 1)
                start[i][j] = l;
            else start[i][j] = d;
        }
    }


    for (int i = 0; i < 25; i++) {
        field[i] = (char*)malloc(sizeof(char) * 80);
        field_old[i] = (char*)malloc(sizeof(char) * 80);
        field_next[i] = (char*)malloc(sizeof(char) * 80);
        for (int j = 0; j < 80; j++)
            field[i][j] = d;
    }
    add((char **) field, (char **) start, x, y, lx, ly);
    in_old((char **) field, (char **) field_old);
    draw(field);
    
    while (1) {
        if (input()) {
            int pr = process((char **) field, (char **) field_old, field_next, d, l, 0);
            if (pr == 1 || pr == 2) {
                in_old((char **) field, (char **) field_next);
                if (process(field_next, field, field_old, d, l, 1) == 0) {
                    for (int i = 0; i < 80; i++) {
                        if (i < 35 || i > 44)
                            printf("-");
                        if (i == 35)
                            printf(" The end! ");
                    }
                    clean(start, ly);
                    clean(field, 25);
                    clean(field_old, 25);
                    clean(field_next, 25);
                    printf("\nAll cells are dead.");
                    return 0;
                }
                if (pr == 2) {
                    for (int i = 0; i < 80; i++) {
                        if (i < 35 || i > 44)
                            printf("-");
                        if (i == 35)
                            printf(" The end! ");
                    }
                    clean(start, ly);
                    clean(field, 25);
                    clean(field_old, 25);
                    clean(field_next, 25);
                    printf("\nCells don't grow and die.");
                    return 0;
                }
                if (process(field_next, field, field_old, d, l, 1) == 3) {
                    int a;
                    printf("\nThe cycle is endless. You want continue? (1 -> yes   2 -> no)\nYou answer: ");
                    scanf("%d", &a);
                    if (a == 2) break;
                }
                in_old((char **) field, (char **) field_old);
                in_old((char **) field, (char **) field_next);
                draw((char **) field);
            } 
            else {
                clean(start, ly);
                clean(field, 25);
                clean(field_old, 25);
                clean(field_next, 25);
                return 0;
            }
        }
        else draw((char **) field);
    }
    clean(start, ly);
    clean(field, 25);
    clean(field_old, 25);
    clean(field_next, 25);
}

void clean(char **arr, int n) {
    for(int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
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

int process(char **field, char ** field_old, char ** field_old_old, char d, char l, int time) {
    int flag = 0, count;

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

    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            if (field[i][j] == d)
                flag++;
    if (flag == 0) return 0;
    
    // flag = 0;
    // for (int i = 0; i < 25; i++)
    //     for (int j = 0; j < 80; j++)
    //         if (field_old[i][j] == field_old_old[i][j])
    //             flag++;
    // if (flag == 25 * 80) return 2;

    if (time == 0) {
        flag = 0;
        for (int i = 0; i < 25; i++)
            for (int j = 0; j < 80; j++)
                if (field[i][j] == field_old[i][j])
                    flag++;
        if (flag == 25 * 80) return 2;
    }

    if (time) {
        flag = 0;
        for (int i = 0; i < 25; i++)
            for (int j = 0; j < 80; j++)
                if (field[i][j] == field_old_old[i][j])
                    flag++;
        if (flag == 25 * 80) return 3;
    }


    return 1;
}

// int input() {
//     char c_1, c_2;
//     scanf("%c%c", &c_1, &c_2);
//     if ((int) c_1 == 32 && (int) c_2 == 10) return 1;
//     return 0;
// }