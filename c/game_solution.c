#include <stdio.h>

#define MAX_NUMBER 100
#define MAX_MAPPING 256

static int e[MAX_NUMBER];  /* Stores equivalent of each number */
static int d[MAX_MAPPING]; /* Mark if the number is erased */

/* For Game 1 */
static void erase_for_1(int n)
{
    int i;
    for (i = 1; i < (n + 1) / 2; i++)
        d[e[i] ^ e[n - i]] = 1;
}

/* For Game 2 */
static void erase_for_2(int n)
{
    int i;
    if (n >= 2) {
        for (i = 0; i <= (n - 2) / 2; i++)
            d[e[i] ^ e[n - 2 - i]] = 1;
        for (i = 0; i <= (n - 1) / 2; i++)
            d[e[i] ^ e[n - 1 - i]] = 1;
    } else if (n == 1) {
        for (i = 0; i <= (n - 1) / 2; i++)
            d[e[i] ^ e[n - 1 - i]] = 1;
    }
}

static void (*erase_for)(int n) = erase_for_1;

int main(int argc, char *argv[])
{
    int i, j;
    int max = 0;
    if (argc > 1) {
        if (argv[1][0] == '2')
            erase_for = erase_for_2;
    }
    e[0] = 0;
    for (i = 1; i < MAX_NUMBER; i++) {
        for (j = 0; j < MAX_MAPPING; j++)
            d[j] = 0;
        erase_for(i);
        for (j = 0; j < MAX_MAPPING && d[j]; j++)
            ;
        e[i] = j;
        if (j > max)
            max = j;
    }
    for (i = 0; i <= max; i++) {
        printf("%2d:\n", i);
        for (j = 1; j < MAX_NUMBER; j++) {
            if (e[j] == i)
                printf("%4d", j);
        }
        printf("\n");
    }
    return 0;
}
