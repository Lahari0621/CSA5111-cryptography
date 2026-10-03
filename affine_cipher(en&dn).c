#include <stdio.h>

int main() {
    char text[100];
    int a, b, i, x, inverse;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key a: ");
    scanf("%d", &a);

    printf("Enter key b: ");
    scanf("%d", &b);
    
    for (i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            inverse = i;
            break;
        }
    }

    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z') {
            x = text[i] - 'A';
            text[i] = (a * x + b) % 26 + 'A';
        }

        else if (text[i] >= 'a' && text[i] <= 'z') {
            x = text[i] - 'a';
            text[i] = (a * x + b) % 26 + 'a';
        }
    }

    printf("Encrypted text: %s", text);

    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z') {
            x = text[i] - 'A';
            text[i] = (inverse * (x - b + 26)) % 26 + 'A';
        }

        else if (text[i] >= 'a' && text[i] <= 'z') {
            x = text[i] - 'a';
            text[i] = (inverse * (x - b + 26)) % 26 + 'a';
        }
    }

    printf("Decrypted text: %s", text);

    return 0;
}
