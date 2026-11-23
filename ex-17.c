
#include <stdio.h>
#include <string.h>

typedef unsigned char B;

B PC1[56] = {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,21,13,5,28,20,12,4
};

B PC2[48] = {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
};

int SL[16] = {
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

int SR[16] = {
    0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

B ke[16][48], kd[16][48];

void sub(B *cd, B *o)
{
    for (int j = 0; j < 48; j++)
        o[j] = cd[PC2[j] - 1];
}

void rot(B *cd, int s, int left)
{
    for (; s; s--)
    {
        for (int h = 0; h < 2; h++)
        {
            B *a = cd + 28 * h, t;

            if (left)
            {
                t = a[0];
                memmove(a, a + 1, 27);
                a[27] = t;
            }
            else
            {
                t = a[27];
                memmove(a + 1, a, 27);
                a[0] = t;
            }
        }
    }
}

void hex(B *b)
{
    for (int i = 0; i < 48; i += 4)
    {
        printf("%X",
            b[i] * 8 + b[i + 1] * 4 +
            b[i + 2] * 2 + b[i + 3]);
    }
}

int main()
{
    B k[64], cd[56];
    int i, ok = 1;
    char h[17];

    printf("Key (16 hex): ");
    scanf("%s", h);

    for (i = 0; i < 64; i++)
    {
        int v = h[i / 4] >= 'A'
            ? h[i / 4] - 'A' + 10
            : h[i / 4] - '0';

        k[i] = (v >> (3 - i % 4)) & 1;
    }

    for (i = 0; i < 56; i++)
        cd[i] = k[PC1[i] - 1];

    for (i = 0; i < 16; i++)
    {
        rot(cd, SL[i], 1);
        sub(cd, ke[i]);
    }

    for (i = 0; i < 56; i++)
        cd[i] = k[PC1[i] - 1];

    for (i = 0; i < 16; i++)
    {
        rot(cd, SR[i], 0);
        sub(cd, kd[i]);
    }

    printf("Enc K(i)           Dec schedule (right shifts 0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1)\n");

    for (i = 0; i < 16; i++)
    {
        printf("K%-2d=", i + 1);
        hex(ke[i]);

        printf("   used as K%-2d=", 16 - i);
        hex(kd[i]);

        int m = !memcmp(kd[i], ke[15 - i], 48);
        ok &= m;

        printf(" %s\n", m ? "match" : "DIFF");
    }

    printf(ok
        ? "Decryption keys = encryption keys in reverse order\n"
        : "Mismatch\n");

    return 0;
}
