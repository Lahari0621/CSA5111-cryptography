
#include <stdio.h>

long eea(long a, long b, long *x, long *y)
{
    if (!b)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    long x1, y1;
    long g = eea(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return g;
}

int main()
{
    long e, n, p, q, f, x, y, d;

    printf("e n: ");
    scanf("%ld %ld", &e, &n);

    for (p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
            break;
    }

    q = n / p;

    f = (p - 1) * (q - 1);

    eea(e, f, &x, &y);

    d = (x % f + f) % f;

    printf("p=%ld q=%ld phi=%ld\n", p, q, f);

    printf("Private key d=%ld\n", d);

    return 0;
}
