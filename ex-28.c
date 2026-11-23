
#include <stdio.h>

long eea(long a, long b, long *x, long *y)
{
    if (!b)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    long x1, y1, g = eea(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return g;
}

int main()
{
    long q, a, x, y;
    long A, B, ka, kb;
    long ia, ix, iy, ex;

    printf("q a x y: ");
    scanf("%ld %ld %ld %ld", &q, &a, &x, &y);

    A = x * a % q;
    B = y * a % q;

    printf("Alice sends x*a mod q = %ld\n", A);
    printf("Bob sends y*a mod q = %ld\n", B);

    ka = x * B % q;
    kb = y * A % q;

    printf("Alice key = x*(ya) = %ld\n", ka);
    printf("Bob key   = y*(xa) = %ld\n", kb);

    eea(a, q, &ix, &iy);
    ia = (ix % q + q) % q;

    ex = A * ia % q;

    printf("Eve: x = (xa)*a^-1 mod q = %ld\n", ex);
    printf("Eve key = x*(ya) mod q = %ld\n", ex * B % q);

    printf("Eve breaks it easily: multiplication mod q is easy to invert (unlike discrete log)\n");

    return 0;
}
