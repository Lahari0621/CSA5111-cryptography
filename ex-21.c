
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char m[80];
    char s[60];
    int n, i, pad;

    printf("Message: ");
    scanf("%[^\n]", s);

    n = strlen(s);

    memcpy(m, s, n);

    pad = 8 - n % 8;

    m[n] = 0x80;

    for (i = n + 1; i < n + pad; i++)
        m[i] = 0;

    printf("Length=%d bytes, blocks before padding=%d, after padding=%d\n",
           n, (n + 7) / 8, (n + pad) / 8);

    for (i = 0; i < n + pad; i++)
    {
        printf("%02X ", m[i]);

        if (i % 8 == 7)
            printf("\n");
    }

    i = n + pad - 1;

    while (m[i] == 0)
        i--;

    printf("Receiver removes padding -> original length=%d\n", i);

    return 0;
}
