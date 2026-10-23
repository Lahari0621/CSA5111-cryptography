#include <stdio.h>
#include <math.h>

int main()
{
    int i;
    long double total = 1.0L;
    long double unique;

    for (i = 1; i <= 25; i++)
    {
        total *= i;
    }

    unique = total / 4.0L;

    printf("Total possible Playfair keys = 25!\n");
    printf("Total keys = %.0Lf\n", total);
    printf("Approximate power of 2 = 2^%.2Lf\n",
           log2l(total));

    printf("\nEffectively unique keys = 25! / 4\n");
    printf("Unique keys = %.0Lf\n", unique);
    printf("Approximate power of 2 = 2^%.2Lf\n",
           log2l(unique));

    return 0;
}
