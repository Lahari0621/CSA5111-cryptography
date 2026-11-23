
#include <stdio.h>
#include <ctype.h>

double f[26] = {
    8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0,
    6.1, 7.0, 0.15, 0.77, 4.0, 2.4, 6.7,
    7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8,
    1.0, 2.4, 0.15, 2.0, 0.07
};

int main()
{
    char c[500];
    int N, i, k, j, o[26];
    double s[26];

    printf("Ciphertext: ");
    scanf("%[^\n]", c);

    printf("Top N: ");
    scanf("%d", &N);

    for (k = 0; k < 26; k++)
    {
        s[k] = 0;

        for (i = 0; c[i]; i++)
        {
            if (isalpha(c[i]))
                s[k] += f[(toupper(c[i]) - 'A' - k + 26) % 26];
        }

        o[k] = k;
    }

    for (i = 0; i < 25; i++)
    {
        for (j = 0; j < 25 - i; j++)
        {
            if (s[o[j]] < s[o[j + 1]])
            {
                int t = o[j];
                o[j] = o[j + 1];
                o[j + 1] = t;
            }
        }
    }

    for (i = 0; i < N && i < 26; i++)
    {
        k = o[i];

        printf("%d) key=%d: ", i + 1, k);

        for (j = 0; c[j]; j++)
        {
            putchar(isalpha(c[j])
                ? (toupper(c[j]) - 'A' - k + 26) % 26 + 'a'
                : c[j]);
        }

        printf("\n");
    }

    return 0;
}
