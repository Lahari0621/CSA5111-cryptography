
#include <stdio.h>

typedef long long L;

L pw(L b, L e, L m)
{
    L r = 1;
    b %= m;

    while (e)
    {
        if (e & 1)
            r = r * b % m;

        b = b * b % m;
        e >>= 1;
    }

    return r;
}

L gcd(L a, L b)
{
    return b ? gcd(b, a % b) : a;
}

L eea(L a, L b, L *x, L *y)
{
    if (!b)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    L x1, y1;
    L g = eea(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return g;
}

int main()
{
    L n, e, c, p, q, f, x, y, d;

    printf("n e: ");
    scanf("%lld %lld", &n, &e);

    printf("Cipher block: ");
    scanf("%lld", &c);

    p = gcd(c, n);

    if (p == 1 || p == n)
    {
        printf("gcd(C,n)=%lld: no common factor, no help\n", p);
        return 0;
    }

    q = n / p;

    f = (p - 1) * (q - 1);

    eea(e, f, &x, &y);

    d = (x % f + f) % f;

    printf("gcd(C,n)=%lld -> n=%lld x %lld\n", p, p, q);

    printf("phi=%lld, d=%lld\n", f, d);

    printf("Plaintext block=%lld\n", pw(c, d, n));

    return 0;
}
