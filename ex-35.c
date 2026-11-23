
#include <stdio.h>
#include <string.h>

int main()
{
    char p[] = "sendmoremoney";
    char q[] = "cashnotneeded";
    char c[20];

    int k[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int i, n = strlen(p);

    printf("a) Cipher: ");

    for (i = 0; i < n; i++)
    {
        c[i] = (p[i] - 'a' + k[i]) % 26 + 'A';
        putchar(c[i]);
    }

    printf("\nb) Key for \"cashnotneeded\": ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", ((c[i] - 'A') - (q[i] - 'a') + 26) % 26);
    }

    printf("\n");

    return 0;
}
