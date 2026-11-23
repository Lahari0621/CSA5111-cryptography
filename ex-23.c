
#include <stdio.h>
#include <string.h>

int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[] = {6,3,7,4,8,5,10,9};
int IP[] = {2,6,3,1,4,8,5,7};
int IPI[] = {4,1,3,5,7,2,8,6};
int EP[] = {4,1,2,3,2,3,4,1};
int P4[] = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

int k1[8], k2[8];

void perm(int *o, int *i, int *t, int n)
{
    int x[10];

    for (int j = 0; j < n; j++)
        x[j] = i[t[j] - 1];

    for (int j = 0; j < n; j++)
        o[j] = x[j];
}

void ls(int *a)
{
    int t = a[0];

    for (int i = 0; i < 4; i++)
        a[i] = a[i + 1];

    a[4] = t;
}

void keygen(int *k)
{
    int p[10];

    perm(p, k, P10, 10);

    ls(p);
    ls(p + 5);

    perm(k1, p, P8, 8);

    ls(p);
    ls(p + 5);
    ls(p);
    ls(p + 5);

    perm(k2, p, P8, 8);
}

void fk(int *b, int *k)
{
    int e[8], s[4], o[4];

    perm(e, b + 4, EP, 8);

    for (int i = 0; i < 8; i++)
        e[i] ^= k[i];

    int a = S0[e[0] * 2 + e[3]][e[1] * 2 + e[2]];
    int c = S1[e[4] * 2 + e[7]][e[5] * 2 + e[6]];

    s[0] = a >> 1;
    s[1] = a & 1;
    s[2] = c >> 1;
    s[3] = c & 1;

    perm(o, s, P4, 4);

    for (int i = 0; i < 4; i++)
        b[i] ^= o[i];
}

void sw(int *b)
{
    for (int i = 0; i < 4; i++)
    {
        int t = b[i];
        b[i] = b[i + 4];
        b[i + 4] = t;
    }
}

void sd(int *b, int dec)
{
    perm(b, b, IP, 8);

    fk(b, dec ? k2 : k1);

    sw(b);

    fk(b, dec ? k1 : k2);

    perm(b, b, IPI, 8);
}

int main()
{
    char ks[11], ps[100];

    int k[10], b[8];
    int n, i, j, ctr = 0;

    int c[12][8];

    printf("Key (10 bits): ");
    scanf("%s", ks);

    printf("Plaintext bits: ");
    scanf("%s", ps);

    for (i = 0; i < 10; i++)
        k[i] = ks[i] - '0';

    keygen(k);

    n = strlen(ps) / 8;

    printf("Cipher: ");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 8; j++)
            b[j] = (ctr >> (7 - j)) & 1;

        sd(b, 0);
        for (j = 0; j < 8; j++)
        {
            b[j] ^= ps[8 * i + j] - '0';

            c[i][j] = b[j];

            printf("%d", b[j]);
        }
        printf(" ");
        ctr++;
    }
    ctr = 0;
    printf("\nDecrypted: ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 8; j++)
            b[j] = (ctr >> (7 - j)) & 1;
        sd(b, 0);
        for (j = 0; j < 8; j++)
            printf("%d", b[j] ^ c[i][j]);
        printf(" ");
        ctr++;
    }
    printf("\n");
    return 0;
}
