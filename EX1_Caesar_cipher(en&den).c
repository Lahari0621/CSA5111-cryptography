#include <stdio.h>

int main() {
    char text[100];
    int encryptKey, decryptKey, i;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter encryption key: ");
    scanf("%d", &encryptKey);

    encryptKey = ((encryptKey % 26) + 26) % 26;

    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = (text[i] - 'A' + encryptKey) % 26 + 'A';

        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = (text[i] - 'a' + encryptKey) % 26 + 'a';
    }

    printf("Encrypted text: %s", text);

    printf("\nEnter decryption key: ");
    scanf("%d", &decryptKey);

    decryptKey = ((decryptKey % 26) + 26) % 26;

    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = (text[i] - 'A' - decryptKey + 26) % 26 + 'A';

        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = (text[i] - 'a' - decryptKey + 26) % 26 + 'a';
    }

    printf("Decrypted text: %s", text);

    return 0;
}
