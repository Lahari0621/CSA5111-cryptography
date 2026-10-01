#include <stdio.h>

int main() {
    char text[100];
    char key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i, j;

    printf("Enter encrypted text: ");
    fgets(text, sizeof(text), stdin);

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
