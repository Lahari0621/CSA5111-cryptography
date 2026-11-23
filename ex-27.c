
#include <stdio.h>

typedef unsigned long long U;

U pw(U b, U e, U m)
{
    U r = 1;
    b %= m;

    while (e)
    {
        if (e & 1)
            r = r * b % m;

        b = b * b % m;
        e >>= 1;
    }

    return r;
}

int main()
{
    U n = 3599, e = 31;
    U c[100], t[26];

    char s[100];
    int i, j;

    printf("Message (A-Z): ");
    scanf("%s", s);

    for (i = 0; s[i]; i++)
        c[i] = pw(s[i] - 'A', e, n);

    printf("Cipher: ");

    for (i = 0; s[i]; i++)
        printf("%llu ", c[i]);

    for (j = 0; j < 26; j++)
        t[j] = pw(j, e, n);

    printf("\nAttack (encrypt A-Z with public key, compare): ");

    for (i = 0; s[i]; i++)
    {
        for (j = 0; j < 26; j++)
        {
            if (t[j] == c[i])
                putchar('A' + j);
        }
    }

    printf("\n");

    return 0;
}
