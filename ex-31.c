
#include <stdio.h>

typedef unsigned long long U;

U f(U k, U x)
{
    U z = (x + k) * 0x9E3779B97F4A7C15ULL;

    z ^= z >> 29;
    z *= 0xBF58476D1CE4E5B9ULL;
    z ^= z >> 32;

    return z;
}

int main()
{
    U K, L, K1, K2;
    U h, l, h1, l1, h2, l2;

    printf("Key (number): ");
    scanf("%llu", &K);

    printf("a) Constants: Rb(64-bit)=0x1B, Rb(128-bit)=0x87\n");

    L = f(K, 0);

    K1 = (L << 1) ^ ((L >> 63) ? 0x1B : 0);
    K2 = (K1 << 1) ^ ((K1 >> 63) ? 0x1B : 0);

    printf("64-bit block : L=%016llX\n  K1=%016llX\n  K2=%016llX\n",
           L, K1, K2);

    h = f(K, 1);
    l = f(K, 2);

    h1 = (h << 1) | (l >> 63);
    l1 = l << 1;

    if (h >> 63)
        l1 ^= 0x87;

    h2 = (h1 << 1) | (l1 >> 63);
    l2 = l1 << 1;

    if (h1 >> 63)
        l2 ^= 0x87;

    printf("128-bit block: L=%016llX%016llX\n  K1=%016llX%016llX\n  K2=%016llX%016llX\n",
           h, l, h1, l1, h2, l2);

    return 0;
}
