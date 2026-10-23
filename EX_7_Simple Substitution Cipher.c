#include <stdio.h>
#include <string.h>

int main()
{
    char cipher[] =
    "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 "
    "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* "
    ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 "
    "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

    int i = 0;

    printf("Enter substitution mapping for each symbol in the code.\n");
    printf("Decrypted text:\n");

    while (cipher[i] != '\0')
    {
        unsigned char c = (unsigned char)cipher[i];

        if (c == 0xE2 &&
            (unsigned char)cipher[i + 1] == 0x80 &&
            (unsigned char)cipher[i + 2] == 0xA1)
        {
            /* UTF-8 symbol ‡ */
            printf("o");
            i += 3;
        }
        else if (c == 0xE2 &&
                 (unsigned char)cipher[i + 1] == 0x80 &&
                 (unsigned char)cipher[i + 2] == 0xA0)
        {
            /* UTF-8 symbol † */
            printf("d");
            i += 3;
        }
        else if (c == 0xC2 &&
                 (unsigned char)cipher[i + 1] == 0xB6)
        {
            /* UTF-8 symbol ¶ */
            printf("v");
            i += 2;
        }
        else if (c == 0xE2 &&
                 (unsigned char)cipher[i + 1] == 0x80 &&
                 (unsigned char)cipher[i + 2] == 0x94)
        {
            /* UTF-8 symbol — */
            printf("-");
            i += 3;
        }
        else
        {
            switch (cipher[i])
            {
                case '5': putchar('a'); break;
                case '3': putchar('g'); break;
                case '0': putchar('l'); break;
                case ')': putchar('s'); break;
                case '6': putchar('i'); break;
                case '*': putchar('n'); break;
                case ';': putchar('t'); break;
                case '4': putchar('h'); break;
                case '8': putchar('e'); break;
                case '2': putchar('b'); break;
                case '.': putchar('p'); break;
                case '9': putchar('m'); break;
                case '(': putchar('r'); break;
                case '?': putchar('u'); break;
                case '1': putchar('f'); break;
                case ']': putchar('w'); break;
                case ':': putchar('y'); break;
                default: putchar(cipher[i]); break;
            }

            i++;
        }
    }

    printf("\n");
    return 0;
}
