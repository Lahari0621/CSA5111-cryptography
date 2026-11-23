
B sk1[16][48], sk2[16][48], sk3[16][48];

void te(B *x, B *y)
{
    des(x, y, sk1, 0);
    des(y, y, sk2, 1);
    des(y, y, sk3, 0);
}

void td(B *x, B *y)
{
    des(x, y, sk3, 1);
    des(y, y, sk2, 0);
    des(y, y, sk1, 1);
}

int main()
{
    char k1[17], k2[17], k3[17], iv[17], pt[200];
    B kb[64], pv[64], blk[64], c[20][64], d[64];
    int n, i, j;

    printf("Key1 Key2 Key3 (hex): ");
    scanf("%s %s %s", k1, k2, k3);

    printf("IV (16 hex): ");
    scanf("%s", iv);

    printf("Plaintext (hex, multiple of 16): ");
    scanf("%s", pt);

    h2b(k1, kb);
    keys(kb, sk1);

    h2b(k2, kb);
    keys(kb, sk2);

    h2b(k3, kb);
    keys(kb, sk3);

    n = strlen(pt) / 16;

    h2b(iv, pv);

    printf("CBC-3DES cipher: ");

    for (i = 0; i < n; i++)
    {
        char t[17];

        strncpy(t, pt + 16 * i, 16);
        t[16] = 0;

        h2b(t, blk);

        for (j = 0; j < 64; j++)
            blk[j] ^= pv[j];

        te(blk, c[i]);

        memcpy(pv, c[i], 64);

        b2h(c[i]);
    }

    h2b(iv, pv);

    printf("\nDecrypted      : ");

    for (i = 0; i < n; i++)
    {
        td(c[i], d);

        for (j = 0; j < 64; j++)
            d[j] ^= pv[j];

        memcpy(pv, c[i], 64);

        b2h(d);
    }

    printf("\n");

    return 0;
}
