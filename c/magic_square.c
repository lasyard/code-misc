#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_NUMBER 3

static void magic4(int n)
{
    int i, j, ii, jj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            ii = (n / 4 <= i && i < 3 * n / 4) ? n - 1 - j : j;
            jj = (n / 4 <= j && j < 3 * n / 4) ? n - 1 - i : i;
            printf("%5d", ii * n + jj + 1);
        }
        printf("\n");
    }
}

static void magic2(int n)
{
    int i, j, ii, jj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i < n / 2) {
                if (j < n / 2) {
                    ii = ((n + j - i) % (n / 2) < (n + 2) / 4) ? i : n - 1 - i;
                    jj = ((n + i - j) % (n / 2) < (n + 2) / 4) ? j : n - 1 - j;
                } else {
                    ii = ((n + j + i) % (n / 2) < (n + 2) / 4) ? n - 1 - i : i;
                    jj = ((n + i + j + 1) % (n / 2) < (n + 2) / 4) ? j : n - 1 - j;
                }
            } else {
                if (j < n / 2) {
                    ii = ((n + j + i + 1) % (n / 2) < (n + 2) / 4) ? i : n - 1 - i;
                    jj = ((n + i + j) % (n / 2) < (n + 2) / 4) ? n - 1 - j : j;
                } else {
                    ii = ((n + j - i - 1) % (n / 2) < (n + 2) / 4) ? n - 1 - i : i;
                    jj = ((n + i - j - 1) % (n / 2) < (n + 2) / 4) ? n - 1 - j : j;
                }
            }
            printf("%5d", ii * n + jj + 1);
        }
        printf("\n");
    }
}

static void magic1(int n)
{
    int i, j, ii, jj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            ii = (n - i + j + (n - 1) / 2) % n;
            jj = (n - i + n - j + (n - 1) / 2 - 1) % n;
            printf("%5d", ii * n + jj + 1);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int number = DEFAULT_NUMBER;
    if (argc > 2) {
        fprintf(stderr, "Too many arguments!\n");
        return -1;
    } else if (argc == 2) {
        number = atoi(argv[1]);
        if (number < 3 || number > 30) {
            fprintf(stderr, "The argument must be a number from 3 to 30.\n");
            return -1;
        }
    }
    if (number % 4 == 0) {
        magic4(number);
    } else if (number % 2 == 0) {
        magic2(number);
    } else {
        magic1(number);
    }
    return 0;
}
