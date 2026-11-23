
#include <stdio.h>
#include <string.h>

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

L inv(L a, L m)
{
    for (L i = 1; i < m; i++)
    {
        if (a * i % m == 1)
            return i;
    }

    return 0;
}

int main()
{
    L p = 283, q = 47, g = 64, x = 24;
    L y = pw(g, x, p);
    L H = 0, k[2] = {12, 31};
    L r, s, w, v, i;

    char m[50];

    printf("Message: ");
    scanf("%s", m);

    for (i = 0; m[i]; i++)
        H += m[i];

    H %= q;

    printf("DSA (p=283,q=47,g=64,x=24), H(m)=%lld\n", H);

    for (i = 0; i < 2; i++)
    {
        r = pw(g, k[i], p) % q;
        s = inv(k[i], q) * (H + x * r) % q;
        w = inv(s, q);

        v = pw(g, H * w % q, p) *
            pw(y, r * w % q, p) % p % q;

        printf(" Sign %lld (k=%lld): (r,s)=(%lld,%lld) verify=%s\n",
               i + 1, k[i], r, s, v == r ? "OK" : "FAIL");
    }

    L n = 3599, e = 31, d = 3031, h = 0;

    for (i = 0; m[i]; i++)
        h += m[i];

    printf("RSA (n=3599,d=3031):\n");

    for (i = 0; i < 2; i++)
        printf(" Sign %lld: %lld\n", i + 1, pw(h % n, d, n));

    printf("DSA signatures differ each time; RSA signature is identical\n");

    return 0;
}
