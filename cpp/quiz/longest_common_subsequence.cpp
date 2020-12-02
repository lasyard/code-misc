#include <string.h>

#include "longest_common_subsequence.h"

int longestCommonSubsequence(const char *a, const char *b)
{
    if (a == NULL || b == NULL)
        return 0;
    int len_a = strlen(a);
    int len_b = strlen(b);
    int **L = new int *[len_a + 1];
    for (int i = 0; i < len_a + 1; i++) {
        L[i] = new int[len_b + 1];
        L[i][0] = 0;
    }
    for (int j = 0; j < len_b + 1; j++) {
        L[0][j] = 0;
    }
    for (int i = 0; i < len_a; i++) {
        for (int j = 0; j < len_b; j++) {
            if (a[i] == b[j]) {
                L[i + 1][j + 1] = L[i][j] + 1;
            } else if (L[i][j + 1] > L[i + 1][j]) {
                L[i + 1][j + 1] = L[i][j + 1];
            } else {
                L[i + 1][j + 1] = L[i + 1][j];
            }
        }
    }
    int r = L[len_a][len_b];
    for (int i = 0; i < len_a + 1; i++)
        delete[] L[i];
    delete[] L;
    return r;
}
