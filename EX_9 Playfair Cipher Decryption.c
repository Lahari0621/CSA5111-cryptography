#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char key[])
{
    int used[26] = {0};
    int i, j, k = 0;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i] != '\0'; i++)
    {
        ch = toupper((unsigned char)key[i]);

        if (ch < 'A' || ch > 'Z')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }
}

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPair(char a, char b)
{
    int r1, c1, r2, c2;

    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if (r1 == r2)
    {
        putchar(matrix[r1][(c1 + 4) % 5]);
        putchar(matrix[r2][(c2 + 4) % 5]);
    }
    else if (c1 == c2)
    {
        putchar(matrix[(r1 + 4) % 5][c1]);
        putchar(matrix[(r2 + 4) % 5][c2]);
    }
    else
    {
        putchar(matrix[r1][c2]);
        putchar(matrix[r2][c1]);
    }
}

int main()
{
    char key[100];
    char cipher[] =
        "KXJEYUREBEZWEHEWRYTUHEYFS"
        "KREHEGOYFIWTTTUOLKSYCAJPO"
        "BOTEIZONTXBYBNTGONEYCUZWR"
        "GDSONSXBOUYWRHEBAAHYUSEDQ";

    int i;

    printf("Enter Playfair keyword: ");
    scanf("%99s", key);

    createMatrix(key);

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    printf("\nDecrypted message:\n");

    for (i = 0; cipher[i] != '\0'; i += 2)
        decryptPair(cipher[i], cipher[i + 1]);

    printf("\n");

    return 0;
}
