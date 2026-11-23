
#include <stdio.h>
#include <ctype.h>

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    char s[200];
    int a, b, i, inv = 0;

    printf("a b: ");
    scanf("%d %d", &a, &b);

    if (gcd(a, 26) != 1)
    {
        printf("a not allowed (must be coprime with 26)\n");
        return 0;
    }

    printf("Text: ");
    scanf("%s", s);

    for (i = 1; i < 26; i++)
    {
        if (a * i % 26 == 1)
            inv = i;
    }

    printf("Cipher: ");

    for (i = 0; s[i]; i++)
    {
        printf("%c", (a * (toupper(s[i]) - 'A') + b) % 26 + 'A');
    }

    printf("\nDecrypted: ");

    for (i = 0; s[i]; i++)
    {
        int c = (a * (toupper(s[i]) - 'A') + b) % 26;

        printf("%c", (inv * (c - b + 26)) % 26 + 'A');
    }

    printf("\nb: any value 0-25 allowed\n");
    printf("Invalid a: even numbers and 13\n");

    return 0;
}
