#include <stdio.h>
#include <stdlib.h>

//field [m][n]

int main() {
    
        }
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