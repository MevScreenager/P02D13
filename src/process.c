#include <stdio.h>
#include <stdlib.h>

//field [m][n]

int main() {

}

int process(char **field, char d, char l) {
    int count = 0;
    for (int k = 0; k < m; k++) {
        for (int t = 0; t< n; t++) {
            if (field[m][n] = d) {
                dead(field[m][n]);
                }
            if (field[m][n] = l) {
                live(field[m][n]);
            }
        }
    }
}

void dead(char **field, char d, char l) {
    int count++;
    if (field[m][n] = d) {
        for (int i= m - 1; i <= m + 1; i++) {
            for (int j = n - 1; j <= n + 1; j++) {
                if (field [i][j] = l) {
                    count++;
                }
            }
        } if (count = 3) {
            field[m][n] = l;
        }
    }
}