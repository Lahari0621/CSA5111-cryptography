#include <stdio.h>
#include <string.h>
#include <ctype.h>
char matrix[5][5];
void createMatrix(char key[]) {
    int used[26] = {0};
    int i, k = 0;
    char ch;
    used['J' - 'A'] = 1;
    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper(key[i]);
        if (ch == 'J')
            ch = 'I';
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}
void prepareText(char input[], char output[]) {
    char clean[200];
    int i, j = 0, k = 0;
    char a, b;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            clean[k] = toupper(input[i]);

            if (clean[k] == 'J')
                clean[k] = 'I';

            k++;
        }
    }
    clean[k] = '\0';
    i = 0;
    while (i < k) {
        a = clean[i];
        if (i + 1 >= k) {
            output[j++] = a;
            output[j++] = 'X';
            i++;
        }
        else {
            b = clean[i + 1];

            if (a == b) {
                output[j++] = a;
                output[j++] = 'X';
                i++;
            }
            else {
                output[j++] = a;
                output[j++] = b;
                i += 2;
            }
        }
    }

    output[j] = '\0';
}

void findPosition(char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char text[]) {
    int i;
    int r1, c1, r2, c2;

    for (i = 0; text[i] != '\0'; i += 2) {

        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2) {
            text[i] = matrix[r1][(c1 + 1) % 5];
            text[i + 1] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            text[i] = matrix[(r1 + 1) % 5][c1];
            text[i + 1] = matrix[(r2 + 1) % 5][c2];
        }
        else {
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

void decrypt(char text[]) {
    int i;
    int r1, c1, r2, c2;

    for (i = 0; text[i] != '\0'; i += 2) {

        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2) {
            text[i] = matrix[r1][(c1 + 4) % 5];
            text[i + 1] = matrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2) {
            text[i] = matrix[(r1 + 4) % 5][c1];
            text[i + 1] = matrix[(r2 + 4) % 5][c2];
        }
        else {
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

int main() {
    char key[100];
    char input[100];
    char text[200];

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);

    createMatrix(key);
    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    prepareText(input, text);
    printf("\nPrepared text: %s\n", text);
    encrypt(text);
    printf("Encrypted text: %s\n", text);
    decrypt(text);
    printf("Decrypted text: %s\n", text);
    return 0;
}
