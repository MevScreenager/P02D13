#include<stdio.h>

void draw(char **field);    //отрисовка поля
void add(char **field, char **start, int x, int y, int lx, int ly);   //добавляем стартовую позицию
int process(char **field); //процесс игры
int input();

int main() {
    int x, y, lx = 20, ly = 10;
    char field[25][80], start[ly][lx];
    add((char **) field, (char **) start, x, y, lx, ly);
    draw((char **) field);
    while (1) {
        if (input()) {
            process((char **) field);
            draw((char **) field);
        }
        else
            draw((char **) field);
        
    }

}

int input() {
    char c_1, c_2;
    scanf("%c")
    
}

void add(char **field, char **start, int x, int y, int lx, int ly) {}

void draw(char **field) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++) {
            if (i == 24 && j == 79) {
                printf("%c", start[i][j]);
                break;
            }
            if (j == 79) {
                printf("%c\n", start[i][j]);
                break;
            }
            printf("%c", start[i][j]);
        }
}

int process(char **field) {}