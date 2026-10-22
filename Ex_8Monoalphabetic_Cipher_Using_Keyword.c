#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char key[100], cipher[27], text[200];
    int used[26] = {0};
    int i, j = 0;

    printf("Enter keyword: ");
    scanf("%99s", key);

    for (i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            cipher[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (i = 0; i < 26; i++) {
        if (!used[i])
            cipher[j++] = 'A' + i;
    }
    cipher[26] = '\0';

    printf("Cipher alphabet: %s\n", cipher);

    getchar();
    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i]))
            text[i] = cipher[text[i] - 'A'];
        else if (islower(text[i]))
            text[i] = tolower(cipher[text[i] - 'a']);
    }

    printf("Encrypted text: %s", text);
    return 0;
}
