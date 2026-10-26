#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

const int PC2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

const int shifts[16] = {
    1,1,2,2,2,2,2,2,
    1,2,2,2,2,2,2,1
};

uint64_t permute(uint64_t input, const int table[],
                 int outputBits, int inputBits)
{
    uint64_t result = 0;
    int i;

    for (i = 0; i < outputBits; i++) {
        result <<= 1;
        result |= (input >> (inputBits - table[i])) & 1ULL;
    }

    return result;
}

uint32_t rotateLeft28(uint32_t value, int shift)
{
    return ((value << shift) |
            (value >> (28 - shift))) & 0x0FFFFFFF;
}

int main(void)
{
    char keyText[100];
    char *end;
    uint64_t key, key56, combined, subkey;
    uint32_t C, D;
    uint32_t first24, second24;
    int i;

    printf("Enter 16-digit hexadecimal DES key: ");

    if (scanf("%99s", keyText) != 1 ||
        strlen(keyText) != 16) {
        printf("Invalid key. Enter exactly 16 hex digits.\n");
        return 1;
    }

    for (i = 0; i < 16; i++) {
        if (!isxdigit((unsigned char)keyText[i])) {
            printf("Invalid hexadecimal key.\n");
            return 1;
        }
    }

    key = strtoull(keyText, &end, 16);

    if (*end != '\0') {
        printf("Invalid key.\n");
        return 1;
    }

    key56 = permute(key, PC1, 56, 64);

    C = (uint32_t)(key56 >> 28);
    D = (uint32_t)(key56 & 0x0FFFFFFF);

    printf("\nDES Round Key Generation\n");
    printf("Each subkey contains 48 bits.\n");
    printf("First 24 bits come from C; "
           "second 24 bits come from D.\n\n");

    for (i = 0; i < 16; i++) {
        C = rotateLeft28(C, shifts[i]);
        D = rotateLeft28(D, shifts[i]);

        combined = ((uint64_t)C << 28) | D;

        subkey = permute(combined, PC2, 48, 56);

        first24 = (uint32_t)(subkey >> 24);
        second24 = (uint32_t)(subkey & 0xFFFFFF);

        printf("K%-2d = %012llX | "
               "First 24 bits: %06X | "
               "Second 24 bits: %06X\n",
               i + 1,
               (unsigned long long)subkey,
               first24,
               second24);
    }

    return 0;
}
