
#include <stdio.h>
#include <ctype.h>

int main()
{
    char c[1000];
    char *E = "etaoinshrdlcumwfgypbvkjxqz";
    char m[26], g[26];

    int cnt[26] = {0};
    int o[26], i, j, N, t;

    printf("Ciphertext: ");
    scanf("%[^\n]", c);

    printf("Top N: ");
    scanf("%d", &N);

    for (i = 0; c[i]; i++)
    {
        if (isalpha(c[i]))
            cnt[toupper(c[i]) - 'A']++;
    }

    for (i = 0; i < 26; i++)
        o[i] = i;

    for (i = 0; i < 25; i++)
    {
        for (j = 0; j < 25 - i; j++)
        {
            if (cnt[o[j]] < cnt[o[j + 1]])
            {
                t = o[j];
                o[j] = o[j + 1];
                o[j + 1] = t;
            }
        }
    }

    for (i = 0; i < 26; i++)
        m[o[i]] = E[i];

    for (t = 0; t < N; t++)
    {
        for (i = 0; i < 26; i++)
            g[i] = m[i];

        if (t > 0)
        {
            int a = (t - 1) % 25;
            char x = g[o[a]];

            g[o[a]] = g[o[a + 1]];
            g[o[a + 1]] = x;
        }

        printf("%d) ", t + 1);

        for (i = 0; c[i]; i++)
        {
            putchar(isalpha(c[i])
                ? g[toupper(c[i]) - 'A']
                : c[i]);
        }

        printf("\n");
    }

    return 0;
}
