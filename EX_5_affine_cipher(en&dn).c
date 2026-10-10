#include <stdio.h>
#include <string.h>

int main() {
    char text[100];
    int a, b, i, p, c, inverse = -1;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key a: ");
    scanf("%d", &a);

    printf("Enter key b: ");
    scanf("%d", &b);

    a = ((a % 26) + 26) % 26;
    b = ((b % 26) + 26) % 26;

    // Find modular multiplicative inverse of a
    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            inverse = i;
            break;
        }
    }

    if (inverse == -1) {
        printf("Invalid key a! Choose a value coprime to 26.\n");
        return 0;
    }

    // Encryption
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            p = text[i] - 'A';
            c = (a * p + b) % 26;
            text[i] = c + 'A';
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            p = text[i] - 'a';
            c = (a * p + b) % 26;
            text[i] = c + 'a';
        }
    }

    printf("Encrypted text: %s", text);

    // Decryption
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            c = text[i] - 'A';
            p = (inverse * (c - b + 26)) % 26;
            text[i] = p + 'A';
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            c = text[i] - 'a';
            p = (inverse * (c - b + 26)) % 26;
            text[i] = p + 'a';
        }
    }

    printf("Decrypted text: %s", text);

    return 0;
}
