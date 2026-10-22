#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char input[200], text[200], cipher[200];
    int i, n = 0, p1, p2, c1, c2;
    int a = 9, b = 4, c = 5, d = 7;
    int inverse = 23;

    printf("Enter plaintext: ");
    fgets(input, sizeof(input), stdin);

    for (i = 0; input[i]; i++)
        if (isalpha(input[i]))
            text[n++] = tolower(input[i]) - 'a';

    if (n % 2) text[n++] = 'x' - 'a';

    for (i = 0; i < n; i += 2) {
        p1 = text[i];
        p2 = text[i+1];
        cipher[i]   = (a*p1 + b*p2) % 26;
        cipher[i+1] = (c*p1 + d*p2) % 26;
    }

    printf("Encrypted text: ");
    for (i = 0; i < n; i++) {
        cipher[i] += 'a';
        printf("%c", cipher[i]);
    }
    printf("\n");

    printf("Decrypted text: ");
    for (i = 0; i < n; i += 2) {
        c1 = cipher[i] - 'a';
        c2 = cipher[i+1] - 'a';

        p1 = (23 * (7*c1 - 4*c2) % 26 + 26) % 26;
        p2 = (23 * (-5*c1 + 9*c2) % 26 + 26) % 26;

        printf("%c%c", p1+'a', p2+'a');
    }
    printf("\n");

    return 0;
}
