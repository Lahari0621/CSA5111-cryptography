#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1000
#define TOP 10

const char *common[] = {
    "th", "he", "in", "er", "an", "re", "on", "at",
    "en", "nd", "ti", "es", "or", "te", "of", "ed",
    "is", "it", "al", "ar", "st", "to", "nt", "ng",
    "se", "ha", "as", "ou", "io", "le", "ve", "co",
    "the", "and", "ing", "her", "ere", "ent", "tha",
    "nth", "was", "eth", "for", "hat", "she", "ion",
    "his", "all", "you", "not", "are", "this", "that",
    "have", "with", "from", "they", "will", "your",
    "one", "would", "there", "their", "about", "which"
};

#define NCOMMON (sizeof(common) / sizeof(common[0]))

const double freq[26] = {
    8.2, 1.5, 2.8, 4.3, 13.0, 2.2, 2.0, 6.1, 7.0,
    0.15, 0.77, 4.0, 2.4, 6.7, 7.5, 1.9, 0.10, 6.0,
    6.3, 9.1, 2.8, 1.0, 2.4, 0.15, 2.0, 0.07
};

char cipher[MAX];
char bestText[TOP][MAX];
double bestScore[TOP];

void decode(const char *text, const int key[26], char out[MAX])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
        {
            int c = tolower((unsigned char)text[i]) - 'a';
            out[i] = key[c] + 'a';
        }
        else
        {
            out[i] = text[i];
        }
    }

    out[i] = '\0';
}

double scoreText(const char *text)
{
    int count[26] = {0};
    int letters = 0;
    int i, j;
    double score = 0.0;
    char lower[MAX];

    for (i = 0; text[i] != '\0'; i++)
    {
        lower[i] = (char)tolower((unsigned char)text[i]);

        if (isalpha((unsigned char)text[i]))
        {
            count[lower[i] - 'a']++;
            letters++;
        }
    }
    lower[i] = '\0';

    if (letters == 0)
        return -1e9;

    /* English letter-frequency score */
    for (i = 0; i < 26; i++)
        score += count[i] * freq[i] / letters;

    /* Common English letter combinations and words */
    for (i = 0; i < (int)NCOMMON; i++)
    {
        int len = (int)strlen(common[i]);

        for (j = 0; lower[j] != '\0'; j++)
        {
            if (strncmp(&lower[j], common[i], len) == 0)
                score += (len == 2) ? 0.8 : (len == 3) ? 2.0 : 3.0;
        }
    }

    return score;
}

void saveCandidate(const char *text, double score)
{
    int i, j;

    for (i = 0; i < TOP; i++)
    {
        if (strcmp(bestText[i], text) == 0)
        {
            if (score <= bestScore[i])
                return;

            bestScore[i] = score;
            break;
        }
    }

    if (i == TOP)
    {
        for (i = 0; i < TOP; i++)
            if (score > bestScore[i])
                break;
    }

    if (i == TOP)
        return;

    for (j = TOP - 1; j > i; j--)
    {
        strcpy(bestText[j], bestText[j - 1]);
        bestScore[j] = bestScore[j - 1];
    }

    strcpy(bestText[i], text);
    bestScore[i] = score;
}

int main()
{
    int key[26], trial[26];
    int i, j, r, iterations, top;
    char decoded[MAX], candidate[MAX];
    double current, next, temperature, delta;

    printf("Enter ciphertext: ");
    if (fgets(cipher, sizeof(cipher), stdin) == NULL)
        return 1;

    printf("How many possible plaintexts (1-10)? ");
    if (scanf("%d", &top) != 1 || top < 1 || top > TOP)
    {
        printf("Enter a number from 1 to 10.\n");
        return 1;
    }

    for (i = 0; i < TOP; i++)
    {
        bestText[i][0] = '\0';
        bestScore[i] = -1e9;
    }

    srand(12345);

    /* Try many possible substitution keys */
    for (r = 0; r < 40; r++)
    {
        for (i = 0; i < 26; i++)
            key[i] = i;

        /* Randomly shuffle the key */
        for (i = 25; i > 0; i--)
        {
            j = rand() % (i + 1);

            int temp = key[i];
            key[i] = key[j];
            key[j] = temp;
        }

        decode(cipher, key, decoded);
        current = scoreText(decoded);

        /* Improve the key by swapping mappings */
        for (iterations = 0; iterations < 2500; iterations++)
        {
            int a = rand() % 26;
            int b = rand() % 26;
            int temp;

            while (a == b)
                b = rand() % 26;

            temp = key[a];
            key[a] = key[b];
            key[b] = temp;

            decode(cipher, key, candidate);
            next = scoreText(candidate);
            delta = next - current;

            temperature = 3.0 *
                (2500 - iterations) / 2500.0 + 0.05;

            if (delta > 0 ||
                (rand() % 1000) / 1000.0 <
                temperature / (temperature + (-delta)))
            {
                strcpy(decoded, candidate);
                current = next;
            }
            else
            {
                temp = key[a];
                key[a] = key[b];
                key[b] = temp;
            }
        }

        saveCandidate(decoded, current);
    }

    printf("\nTop %d possible plaintexts:\n\n", top);

    for (i = 0; i < top; i++)
    {
        if (bestText[i][0] != '\0')
            printf("%d. %s\n", i + 1, bestText[i]);
    }

    return 0;
}
