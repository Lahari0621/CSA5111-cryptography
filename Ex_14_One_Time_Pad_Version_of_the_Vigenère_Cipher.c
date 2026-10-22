#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100], result[100];
    int key[100], n, i, j = 0, mode;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter number of key values: ");
    scanf("%d", &n);

    printf("Enter key values: ");
    for (i = 0; i < n; i++)
        scanf("%d", &key[i]);

    printf("Enter 1 for encryption, 2 for decryption: ");
    scanf("%d", &mode);

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int p = tolower(text[i]) - 'a';

            if (mode == 1)
                result[i] = (p + key[j]) % 26 + 'a';
            else
                result[i] = (p - key[j] + 26) % 26 + 'a';

            j++;
        } else {
            result[i] = text[i];
        }
    }

    result[i] = '\0';
    printf("Result: %s", result);
    return 0;
}
