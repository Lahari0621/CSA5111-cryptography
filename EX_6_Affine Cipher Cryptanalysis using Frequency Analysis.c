#include <stdio.h>
#include <ctype.h>

int main()
{
    char cipher[1000];
    int i, c, p;

    int a_inverse = 9;
    int b = 15;

    printf("Enter ciphertext: ");
    scanf("%999s", cipher);

    printf("Candidate plaintext: ");

    for (i = 0; cipher[i] != '\0'; i++)
    {
        c = tolower((unsigned char)cipher[i]) - 'a';

        p = (a_inverse * (c - b + 26)) % 26;

        printf("%c", p + 'a');
    }

    printf("\n");

    return 0;
}


//kbwwf
