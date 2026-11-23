
#include <stdio.h>

typedef unsigned long long U;

U R(U x, int n)
{
    return (x << n) | (x >> (64 - n));
}

int main()
{
    U A[5][5], C[5], D[5];
    int x, y, k, r, z;

    for (y = 0; y < 5; y++)
    {
        for (x = 0; x < 5; x++)
        {
            k = x + 5 * y;
            A[x][y] = k < 16
                ? (k + 1) * 0x9E3779B97F4A7C15ULL
                : 0;
        }
    }

    printf("r=1024 bits (16 lanes), c=576 bits (9 lanes)\n");

    for (r = 0; r <= 3; r++)
    {
        z = 0;

        for (y = 0; y < 5; y++)
        {
            for (x = 0; x < 5; x++)
            {
                if (x + 5 * y >= 16 && A[x][y])
                    z++;
            }
        }

        printf("After round %d: capacity lanes nonzero = %d/9\n", r, z);

        if (z == 9)
            break;

        for (x = 0; x < 5; x++)
            C[x] = A[x][0] ^ A[x][1] ^ A[x][2] ^ A[x][3] ^ A[x][4];

        for (x = 0; x < 5; x++)
            D[x] = C[(x + 4) % 5] ^ R(C[(x + 1) % 5], 1);

        for (x = 0; x < 5; x++)
        {
            for (y = 0; y < 5; y++)
                A[x][y] ^= D[x];
        }
    }

    return 0;
}
