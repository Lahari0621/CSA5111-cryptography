
#include <stdio.h>

int E(int k, int x)
{
    return ((x ^ k) * 37 + k) & 255;
}

int D(int k, int y)
{
    return ((((y - k) & 255) * 173) & 255) ^ k;
}

int k = 0x5A, iv = 0x33, N = 5;

void cbc_enc(int *p, int *c)
{
    int pr = iv;

    for (int i = 0; i < N; i++)
    {
        c[i] = E(k, p[i] ^ pr);
        pr = c[i];
    }
}

void cbc_dec(int *c, int *d)
{
    int pr = iv;

    for (int i = 0; i < N; i++)
    {
        d[i] = D(k, c[i]) ^ pr;
        pr = c[i];
    }
}

void show(char *t, int *a, int *ref)
{
    printf("%s", t);

    for (int i = 0; i < N; i++)
    {
        printf("P%d:%s ", i + 1,
               a[i] == ref[i] ? "ok" : "ERR");
    }

    printf("\n");
}

int main()
{
    int p[5] = {10, 20, 30, 40, 50};
    int c[5], e[5], d[5], q[5], c2[5], i;

    printf("a) Bit error in ciphertext block C1\n");

    for (i = 0; i < N; i++)
        e[i] = E(k, p[i]);

    e[0] ^= 1;

    for (i = 0; i < N; i++)
        d[i] = D(k, e[i]);

    show("   ECB: ", d, p);

    cbc_enc(p, c);
    c[0] ^= 1;
    cbc_dec(c, d);

    show("   CBC: ", d, p);

    printf("b) Bit error in source block P1\n");

    for (i = 0; i < N; i++)
        q[i] = p[i];

    q[0] ^= 1;

    cbc_enc(p, c);
    cbc_enc(q, c2);

    printf("   Ciphertext blocks changed: ");

    for (i = 0; i < N; i++)
    {
        printf("C%d:%s ", i + 1,
               c[i] == c2[i] ? "same" : "CHANGED");
    }

    cbc_dec(c2, d);

    printf("\n");

    show("   Receiver (vs original P): ", d, p);

    return 0;
}
