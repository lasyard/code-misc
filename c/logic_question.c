#include <stdio.h>

#define ABS(x) (((x) < 0) ? -(x) : (x))

static int a3[6] = {0, 1, 2, 4, 7, 6};
static int A[11];

static void search(int n)
{
    int i, f, t;
    if (n < 11) {
        for (A[n] = 1; A[n] <= 5; A[n]++)
            search(n + 1);
        return;
    }
    /* 1 */
    for (i = 1; i < 11 && A[i] != 2; i++)
        ;
    if (A[1] + 1 != i)
        return;
    /* 2 */
    f = 0;
    for (i = 1; i < 10; i++)
        if (A[i] == A[i + 1])
            f++;
    if (f != 1 || A[A[2] + 1] != A[A[2] + 2])
        return;
    /* 3 */
    if (A[a3[A[3]]] != A[3])
        return;
    /* 4 */
    t = 0;
    for (i = 1; i < 11; i++)
        if (A[i] == 1)
            t++;
    if (A[4] - 1 != t)
        return;
    /* 5 */
    if (A[11 - A[5]] != A[5])
        return;
    /* 6 */
    if (A[6] == 5) {
        f = 0;
        for (i = 1; i < 11; i++)
            if (A[i] == 2)
                f++;
        if (f == t)
            return;
        f = 0;
        for (i = 1; i < 11; i++)
            if (A[i] == 3)
                f++;
        if (f == t)
            return;
        f = 0;
        for (i = 1; i < 11; i++)
            if (A[i] == 4)
                f++;
        if (f == t)
            return;
        f = 0;
        for (i = 1; i < 11; i++)
            if (A[i] == 5)
                f++;
        if (f == t)
            return;
    } else {
        f = 0;
        for (i = 1; i < 11; i++)
            if (A[i] == A[6] + 1)
                f++;
        if (f != t)
            return;
    }
    /* 7 */
    if (ABS(A[8] - A[7]) != 5 - A[7])
        return;
    /* 8 */
    f = 0;
    for (i = 1; i < 11; i++)
        if (A[i] == 5)
            f++;
    f += t;
    if (A[8] + 1 != f)
        return;
    /* 9 */
    f = 10 - f;
    if (A[9] == 1) {
        if (f != 2 && f != 3 && f != 5 && f != 7)
            return;
    } else if (A[9] == 2) {
        if (f != 1 && f != 2 && f != 6)
            return;
    } else if (A[9] == 3) {
        if (f != 1 && f != 4 && f != 9)
            return;
    } else if (A[9] == 4) {
        if (f != 1 && f != 8)
            return;
    } else {
        if (f % 5 != 0)
            return;
    }
    /* output */
    printf("The answer: ");
    for (i = 1; i < 11; i++)
        printf("%c ", A[i] + 96);
    printf("\n");
}

int main(void)
{
    search(1);
    return 0;
}
