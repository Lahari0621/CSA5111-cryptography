#include <stdio.h>
#include <string.h>

int main() {
    char text[100];
    char key[100];
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
            text[i] = (text[i] - 'A' + key[j] - 'A') % 26 + 'A';
            j++;
            j = j % keyLength;
        }

        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + key[j] - 'a') % 26 + 'a';
            j++;
            j = j % keyLength;
        }
    }

    printf("Encrypted text: %s", text);

    j = 0;

    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' - (key[j] - 'A') + 26) % 26 + 'A';
            j++;
            j = j % keyLength;
        }

        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' - (key[j] - 'a') + 26) % 26 + 'a';
            j++;
            j = j % keyLength;
        }
    }

    printf("Decrypted text: %s", text);

    return 0;
}
