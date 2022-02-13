#include<stdio.h>
#include<stdlib.h>

void draw(int **field);    //отрисовка поля
void add(char **field, char **start, int x, int y, int lx, int ly);   //добавляем стартовую позицию
void in_old(int **field, int **field_old);    //один массив в другой
int read_file(int init_matrix[25][80]); // чтение из файла
void process(int **field_next,  int ** field); //процесс игры
void input();    //проверка и ввод пробела
void clean(int **arr, int n);  // отчистка массива
void createArr(int **field, int **field_old, int **field_next);    //создание массива
int check(int **field_next, int **field, int **field_old);    // игра не бессконечна, есть живые клетки и на следующем щаге будет изменение

int main() {
    int init_matrix[25][80];
    int game_mode, speed = 1; //x = 20, y = 10, lx = 3, ly = 3, 
    int **field= NULL, **field_old = NULL, **field_next = NULL;

    // createArr(field, field_old, field_next);
    field = malloc(sizeof(int) * 25 * 80 + 25 * sizeof(int*));
    field_old = malloc(sizeof(int) * 25 * 80 + 25 * sizeof(int*));
    field_next = malloc(sizeof(int) * 25 * 80 + 25 * sizeof(int*));
    int * str = (int*) (field + 25);
    int * str1 = (int*) (field_old + 25);
    int * str2 = (int*) (field_next + 25);
    for (int i = 0; i < 25; i++) {
        field[i] = str + 80*i;
        field_old[i] = str1 + 80*i;
        field_next[i] = str2 + 80*i;
    }

    if (read_file(init_matrix) == 1) {
        printf("n/a");
        return 1;
    }
     
    for (int i = 0; i<25; i++) {
        for (int j = 0; j < 80; j++) {
            field[i][j] = init_matrix[i][j];
            field_old[i][j] = 0;
            field_next[i][j] = field[i][j];
        }
    }
    
    draw(field);

//     // выбор режима игры game_mode = 1 -> обычный game_mode = 2-> интерактив
    game_mode = 1;
    
    if (game_mode == 1) {
        while (1) {
            input();
            if (!check(field_next, field, field_old)) { // 0 условия не выполняются или пользователь не хочет продолжать
                for (int i = 0; i < 80; i++) {
                    if (i < 35 || i > 44)
                        printf("-");
                    if (i == 35)
                        printf(" The end! ");
                }
                break;
            }
            // process(field_next, field);
            in_old(field, field_old);
            in_old(field_next, field);

            draw(field);
        }
    }
    else {
        switch (speed) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
        }
    }
    free(field);
    free(field_old);
    free(field_next);

}


// void createArr(int **field, int **field_old, int **field_next) {
//     fifield = malloc(sizeof(int) * 25 * 80 + 25 * sizeof(int*));
//     field_old = malloc(sizeof(int) * 25 * 80 + 25 * sizeof(int*));
//     field_next = malloc(sizeof(int) * 25 * 80 + 25 * sizeof(int*));
//     int * str = (int*) (field + 25);
//     int * str1 = (int*) (field_old + 25);
//     int * str2 = (int*) (field_next + 25);
//     for (int i = 0; i < 25; i++) {
//         field[i] = str + 80*i;
//         field_old[i] = str1 + 80*i;
//         field_next[i] = str2 + 80*i;
//     }
// }


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

int check(int **field_next, int **field, int **field_old) {
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
            if (field[i][j] == 0)
                flag++;
    if (flag == 0) return 0;

    /* Если бесконечный цикл */
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            if (field_next[i][j] == field_old[i][j])
                flag++;
    if (flag == 25 * 80) {
        int a;
        printf("\nThe cycle is endless. You want continue? (1 -> yes   2 -> no)\nYou answer: ");
        while (!scanf("%d", &a)) printf("\nInpute 1 or 2: ");
        if (a == 2) return 0;
    }
    return 1;
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
        printf("\nInput is'n correct.\nTry again: ");
    }
}

void in_old(int **field, int **field_old) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            field_old[i][j] = field[i][j];
}

void draw(int **field) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++) {
            if (i == 24 && j == 79) {
                if (field[i][j] == 0) printf(" ");
                else printf("o");
                break;
            }
            if (j == 79) {
                if (field[i][j] == 0) printf(" \n");
                else printf("o\n");
                break;
            }
            if (field[i][j] == 0) printf(" ");
            else printf("o");
        }
}




void process(int **field_next, int ** field) {
    int count = 0;

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

            for (int k = 0; k < 8; k++)
                if (field[y[k]][x[k]] == 1)
                    count++;

            if (field[i][j] == 0 && count == 3)
                field_next[i][j] = 1;
            if (field[i][j] == 1 && (count < 2 || count > 3))
                field_next[i][j] = 0;
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