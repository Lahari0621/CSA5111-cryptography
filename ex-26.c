
#include <stdio.h>

typedef unsigned long long U;

U pw(U b, U e, U m)
{
    U r = 1;
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

U gcd(U a, U b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    U n, e, d, t, a, x, y;
    int s = 0, i;

    printf("n e d: ");
    scanf("%llu %llu %llu", &n, &e, &d);

    t = e * d - 1;

    while (t % 2 == 0)
    {
        t /= 2;
        s++;
    }

    for (a = 2; a < 50; a++)
    {
        x = pw(a, t, n);

        if (x == 1 || x == n - 1)
            continue;

        for (i = 0; i < s; i++)
        {
            y = x * x % n;

            if (y == 1)
            {
                U p = gcd(x - 1, n);

                if (p > 1 && p < n)
                {
                    printf("Leaked d factors n: p=%llu q=%llu\n",
                           p, n / p);

                    printf("Same modulus is unsafe: attacker can compute every new private key\n");

                    return 0;
                }
            }

            x = y;

            if (x == n - 1)
                break;
        }
    }

    printf("not found\n");

    return 0;
}
