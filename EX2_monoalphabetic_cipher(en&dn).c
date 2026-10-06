#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100];
    char key[27];
    int i, j;

    printf("Enter 26-letter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    while (getchar() != '\n');
    for (i = 0; key[i] != '\0'; i++) {
        key[i] = toupper(key[i]);
    }

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    // Encryption
    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = key[text[i] - 'A'];

        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = key[text[i] - 'a'] + 32;
    }

    printf("Encrypted text: %s", text);

    // Decryption
    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z') {

            for (j = 0; j < 26; j++) {
                if (key[j] == text[i]) {
                    text[i] = 'A' + j;
                    break;
                }
            }
        }

        else if (text[i] >= 'a' && text[i] <= 'z') {

            for (j = 0; j < 26; j++) {
                if (key[j] + 32 == text[i]) {
                    text[i] = 'a' + j;
                    break;
                }
            }
        }
    }

    printf("Decrypted text: %s", text);

    return 0;
}
