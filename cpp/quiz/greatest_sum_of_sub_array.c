#include <assert.h>
#include <stdio.h>

#include "greatest_sum_of_sub_array.h"

int greatestSumOfSubArray(int A[], int size)
{
    int *p;
    int current = 0;
    int greatest = current;
    assert(A != NULL);
    assert(size > 0);
    for (p = A; p < A + size; p++) {
        current += *p;
        if (current < 0)
            current = 0;
        if (greatest < current)
            greatest = current;
    }
    if (greatest == 0) {
        greatest = A[0];
        for (p = A + 1; p < A + size; p++) {
            if (greatest < *p)
                greatest = *p;
        }
    }
    return greatest;
}
