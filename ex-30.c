
#include <stdio.h>

int E(int k, int x)
{
    return ((x ^ k) * 37 + k) & 255;
}

int mac(int k, int *m, int n)
{
    int c = 0;

    for (int i = 0; i < n; i++)
        c = E(k, m[i] ^ c);

    return c;
}

int main()
{
    int k = 0x5A, X, T, m[2];

    printf("One-block message X (0-255): ");
    scanf("%d", &X);

    T = mac(k, &X, 1);

    printf("T = MAC(K,X) = %d\n", T);

    m[0] = X;
    m[1] = X ^ T;

    printf("Forged message X || (X xor T) = %d || %d\n",
           m[0], m[1]);

    printf("MAC(K, X||(X^T)) = %d\n", mac(k, m, 2));

    printf(mac(k, m, 2) == T
        ? "Equal to T: forgery works without knowing K\n"
        : "Not equal\n");

    return 0;
}
