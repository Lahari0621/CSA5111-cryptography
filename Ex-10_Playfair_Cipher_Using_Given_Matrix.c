#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M','F','H','I','K'},
    {'U','N','O','P','Q'},
    {'Z','V','W','X','Y'},
    {'E','L','A','R','G'},
    {'D','S','T','B','C'}
};

void findPos(char ch, int *r, int *c) {
    int i, j;
    if (ch == 'J') ch = 'I';

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (matrix[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
}

int main() {
    char input[200], text[300], encrypted[300];
    int i, j = 0, r1, c1, r2, c2;

    printf("Enter message: ");
    fgets(input, sizeof(input), stdin);

    for (i = 0; input[i] != '\0'; i++)
        if (isalpha(input[i])) {
            text[j] = toupper(input[i]);
            if (text[j] == 'J') text[j] = 'I';
            j++;
        }
    text[j] = '\0';

    if (j % 2 != 0) text[j++] = 'X';
    text[j] = '\0';

    for (i = 0; i < j; i += 2) {
        findPos(text[i], &r1, &c1);
        findPos(text[i+1], &r2, &c2);

        if (r1 == r2) {
            encrypted[i] = matrix[r1][(c1+1)%5];
            encrypted[i+1] = matrix[r2][(c2+1)%5];
        } else if (c1 == c2) {
            encrypted[i] = matrix[(r1+1)%5][c1];
            encrypted[i+1] = matrix[(r2+1)%5][c2];
        } else {
            encrypted[i] = matrix[r1][c2];
            encrypted[i+1] = matrix[r2][c1];
        }
    }

    encrypted[j] = '\0';
    printf("Encrypted text: %s\n", encrypted);
    return 0;
}
