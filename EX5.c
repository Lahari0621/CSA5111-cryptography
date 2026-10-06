#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100];
    char key[100];
    char encrypted[100];
    int i, j = 0;
    int keyLength;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    key[strcspn(key, "\n")] = '\0';

    keyLength = strlen(key);

    // Encryption
    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z') {
            encrypted[i] = ((text[i] - 'A') +
                            (toupper(key[j % keyLength]) - 'A')) % 26 + 'A';
            j++;
        }

        else if (text[i] >= 'a' && text[i] <= 'z') {
            encrypted[i] = ((text[i] - 'a') +
                            (tolower(key[j % keyLength]) - 'a')) % 26 + 'a';
            j++;
        }

        else {
            encrypted[i] = text[i];
        }
    }

    encrypted[i] = '\0';

    printf("Encrypted text: %s", encrypted);

    // Decryption
    j = 0;

    for (i = 0; encrypted[i] != '\0'; i++) {

        if (encrypted[i] >= 'A' && encrypted[i] <= 'Z') {
            encrypted[i] = ((encrypted[i] - 'A') -
                            (toupper(key[j % keyLength]) - 'A') + 26) % 26 + 'A';
            j++;
        }

        else if (encrypted[i] >= 'a' && encrypted[i] <= 'z') {
            encrypted[i] = ((encrypted[i] - 'a') -
                            (tolower(key[j % keyLength]) - 'a') + 26) % 26 + 'a';
            j++;
        }
    }

    printf("Decrypted text: %s", encrypted);

    return 0;
}

