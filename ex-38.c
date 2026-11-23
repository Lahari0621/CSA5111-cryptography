
#include <stdio.h>

int inv(int a)
{
    for (int i = 1; i < 26; i++)
    {
        if (a * i % 26 == 1)
            return i;
    }

    return 0;
}

int md(int x)
{
    return ((x % 26) + 26) % 26;
}

int main()
{
    char p[5], c[5];

    int P[2][2], C[2][2];
    int A[2][2], K[2][2];
    int d, i;

    printf("Plaintext(4 letters): ");
    scanf("%s", p);

    printf("Ciphertext(4 letters): ");
    scanf("%s", c);

    for (i = 0; i < 4; i++)
    {
        P[i % 2][i / 2] = p[i] - 'a';
        C[i % 2][i / 2] = c[i] - 'A';
    }

    d = inv(md(P[0][0] * P[1][1] - P[0][1] * P[1][0]));

    if (!d)
    {
        printf("P not invertible, choose other pairs\n");
        return 0;
    }

    A[0][0] = md(d * P[1][1]);
    A[0][1] = md(-d * P[0][1]);
    A[1][0] = md(-d * P[1][0]);
    A[1][1] = md(d * P[0][0]);

    for (i = 0; i < 4; i++)
    {
        K[i / 2][i % 2] = md(
            C[i / 2][0] * A[0][i % 2] +
            C[i / 2][1] * A[1][i % 2]
        );
    }

    printf("Key matrix:\n%d %d\n%d %d\n",
           K[0][0], K[0][1],
           K[1][0], K[1][1]);

    return 0;
}
