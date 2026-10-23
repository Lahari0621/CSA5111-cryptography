#include <stdio.h>
int main()
{
    int P[2][2] = {{19, 19}, {4, 19}};
    int C[2][2] = {{24, 5}, {5, 9}};
    int invP[2][2];
    int K[2][2];
    int det = (P[0][0] * P[1][1] -
               P[0][1] * P[1][0]) % 26;
    int i, j, inv = -1;

    if (det < 0)
        det += 26;

    for (i = 1; i < 26; i++)
    {
        if ((det * i) % 26 == 1)
        {
            inv = i;
            break;
        }
    }

    if (inv == -1)
    {
        printf("Plaintext matrix is not invertible.\n");
        return 0;
    }

    invP[0][0] = (inv * P[1][1]) % 26;
    invP[0][1] = (inv * (26 - P[0][1])) % 26;
    invP[1][0] = (inv * (26 - P[1][0])) % 26;
    invP[1][1] = (inv * P[0][0]) % 26;

    printf("Known plaintext: test\n");
    printf("Corresponding ciphertext: yftj\n");
    printf("\nRecovered key matrix:\n");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            K[i][j] = (C[i][0] * invP[0][j] +
                       C[i][1] * invP[1][j]) % 26;
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }

    return 0;
}
