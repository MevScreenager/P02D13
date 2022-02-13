#include<stdio.h>

void draw(char **field);    //отрисовка поля
void add(char **field, char **start, int x, int y, int lx, int ly);   //добавляем стартовую позицию
void in_old(char **field, char **field_old);    //один массив в другой
int read_file(int init_matrix[25][80]); // чтение из файла
int process(char **field); //процесс игры
int input();    //проверка и ввод пробела
void clean(char **arr, int n);  // отчистка массива
void createArr(char **field, char **start, char **field_old, char **field_next);    //создание массива
int check();    // игра не бессконечна, есть живые клетки и на следующем щаге будет изменение

int main() {
    int init_matrix[25][80];
    int x = 20, y = 10, lx = 3, ly = 3, game_mode, speed = 1;
    char **field, **start, **field_old, **field_next, d = ' ', l = '0';

    if (read_file(init_matrix) == 1) {
        printf("n/a");
        return 1;
    } else {
        for(int i = 0; i < 25; i++) {
            for (int j = 0; j < 80; j++) {
                printf("%d ", init_matrix[i][j]);
            }
            puts("");
        }
    }
    for (int i = 0; i < 25; i++) {
        field[i] = field_string + 80 * i;
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            field[i][j] = init_matrix[i][j];
        }
    }
    
    createArr((char**)field, (char**)start, (char**)field_old, (char**)field_next);
    add((char **) field, (char **) start, x, y, lx, ly);
    in_old((char **) field, (char **) field_old);
    draw(field);


    // выбор режима игры game_mode = 1 -> обычный game_mode = 2-> интерактив

    if (game_mode == 1) {
        while (1) {
            input();
            if (!check()) { // 0 условия не выполняются или пользователь не хочет продолжать
                for (int i = 0; i < 80; i++) {
                    if (i < 35 || i > 44)
                        printf("-");
                    if (i == 35)
                        printf(" The end! ");
                }
            }
            process((char **) field, (char **) field_old, field_next, d, l, 0);
            in_old((char **) field, (char **) field_old);
            in_old((char **) field, (char **) field_next);
            draw((char **) field);
        }
    }
    else {
        // метод который 
    }

    clean(start, ly);
    clean(field, 25);
    clean(field_old, 25);
    clean(field_next, 25);
}

int read_file(int init_matrix[25][80]) {
    int flag = 0;
    for (int i = 0; i < 25; i++) {
        for(int j = 0; j < 80; j++) {
            int read_int = scanf("%d", &init_matrix[i][j]);
            if(read_int == 0 || read_int == EOF) {
                flag = 1;
                break;
            }
        } if(flag) {
            break;
        }
    } freopen("/dev/tty", "r", stdin);
    return flag;
}

int check(char ** field_next, char **field, char **field_old) {
    int flag = 0;
    /* Если поле не поменялось */
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            if (field[i][j] == field_old[i][j])
                flag++;
    if (flag == 25 * 80) return 0;

    /* Если все клетки мертвы */
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            if (field[i][j] == d)
                flag++;
    if (flag == 0) return 0;

    /* Если бесконечный цикл */
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            if (field[i][j] == field_old_old[i][j])
                flag++;
    if (flag == 25 * 80) {
        int a;
        printf("\nThe cycle is endless. You want continue? (1 -> yes   2 -> no)\nYou answer: ");
        while (!scanf("%d", &a)) printf("\nInpute 1 or 2: ");
        if (a == 2) return 0;
    }
    return 1;
}

void createArr(char **field, char **start, char **field_old, char **field_next) {
    **field = (char**) malloc(sizeof(char*) * 25);
    **start = (char**) malloc(sizeof(char*) * ly);
    **field_old = (char**) malloc(sizeof(char*) * 25);
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
}

void clean(char **arr, int n) {
    for(int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

void input() {
    char c;
    int flag = 1;
    while (1) {
        int scan = scanf("%c", &c);
        if ( scan != 1 || c != ' ' )
            flag = 0;
        char d = getchar();
        if ( d != '\n' && d != EOF )
            flag = 0;
        if (flag) break;
        printf("\nInput is'n correct.\nTry again: ")
    }
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



// if (read_file(init_matrix) == 1) { // там где считываем матрицу, в елс игровой цикл
//         printf("n/a");
//         return 1;
//     } else {
//         for(int i = 0; i < 25; ++i) {
//             for(int j = 0; j < 80; ++j) {
//                 printf("%d ", init_matrix[i][j]);
//             }
//             puts("");
//         }
//     }
//     add((char **) field, (char **) start, x, y, lx, ly);
//     draw((char **) field);
//     in_old((char **) field, (char **) field_old);
//     while (1) {
//         if (input()) {
//             if (process((char **) field)) {
//                 in_old((char **) field, (char **) field_old);
//                 draw((char **) field);
//             } else {
//                 return 0;
//             }
//         }
//         draw((char **) field);
//     }