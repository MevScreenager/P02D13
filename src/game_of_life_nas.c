#include <stdio.h>
#include <stdlib.h>

int read_file(int init_matrix[25][80]);
void dead(int m, int n, int **field, int **new);
void live(int m, int n, int **field, int **new);
void draw(int **new);    //отрисовка поля
//void add(int **field, int **start, int x, int y, int lx, int ly);   //добавляем стартовую позицию
//void in_old(char **field, char **field_old);
void process(int **field, int **new, int *new_string); //процесс игры
int input();
/int game_end();

int main() {
    int init_matrix[25][80];
    int **start = (int**)malloc(80 * 25 *sizeof(int) + 25 * sizeof(int*));
    int *start_string = (int*)(start + 25);
    int **field = (int**)malloc(80*25*sizeof(int) + 25*sizeof(int*));
    int *field_string = (int*)(field + 25);
    int **old = (int**)malloc(80*25*sizeof(int) * 25*sizeof(int*));
    int *old_string = (int*)(old +25);
    int **new = (int**)malloc(80*25*sizeof(int) * 25*sizeof(int*));
    int *new_string = (int*)(new +25);
    
    
    
   if (game_end == 0) {
        process(field, new, new_string);
        draw(new);
        input();
        // in_old(** field, *field_string, **old, *old_string);
        // for(int i = 0; i < 25; i++) {
        //     free(new[i]);
        //     // free(old[i]);
        // }
        // for(int i = 0; i < 25; i++) {
        //     for(int j = 0; j < 80; j++) {
        //         free(new[i][j]);
        //         // free(old[i][j]);
        //     }
        // }
    } else {
    printf("Game end!");
    return 0;
    } return 0;
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

//     in_old((int **) field, (int **) old);
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

// }

// void in_old(char **field, char **field_old) {
//     for (int i = 0; i < 25; i++)
//         for (int j = 0; j < 80; j++)
//             field_old[i][j] = field[i][j];
// }


void draw(int **new) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++) {
            if (i == 25 - 1 && j == 80 - 1) {
                printf("%c", new[i][j]);
                break;
            }
            if (j == 80 - 1) {
                printf("%c\n", new[i][j]);
                break;
            }
            printf("%c", new[i][j]);
        }
}

void process(int **field, int **new, int *new_string) {
    for (int k = 0; k < 25; k++) {
        for (int t = 0; t< 80; t++) {
            if (field[k][t] == 0) {
                dead(k, t, field, new);
            } if (field[k][t] == 1) {
                live(k, t, field, new);
            } for (int i = 0; i < 25; i++) {
                new[i] = new_string + 80 * i;
            } for (int i = 0; i < 25; i++) {
                for (int j = 0; j < 80; j++) {
                    new[i][j] = field[i][j];
        }
    }
        }
    }
}

void dead(int m, int n, int **field, int **new) {
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
            if (field[i][j] == 1) {
                count++;
            }
        }
    } if (count == 3) {
        new[m][n] = 1;
    }
}

void live(int m, int n, int **field, int **new) {
    int count = -1;
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
            if (field[i][j] == 1) {
                count++;
            }
        }
    } if (count < 2 || count > 3) {
            new[m][n] = 1;
    }
}

int game_end() {
    for (int i = m - 1; i <= m + 1; i++) {
        for (int j = n - 1; j <= n + 1; j++) {
            if (field[i][j] = new[i][j]) {
                return 0;
            }
            if (old[i][j] = new[i][j]) {
                return 0;
            }
            if if (field[i][j] = 0) {
                return 0;
            }
        }
    } return 1;
}