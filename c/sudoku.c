#include <stdio.h>

/* clang-format off */
static int m[][9] = {
    {8, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 6, 0, 0, 0, 0, 0},
    {0, 7, 0, 0, 9, 0, 2, 0, 0},
    {0, 5, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 4, 5, 7, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 3, 0},
    {0, 0, 1, 0, 0, 0, 0, 6, 8},
    {0, 0, 8, 5, 0, 0, 0, 1, 0},
    {0, 9, 0, 0, 0, 0, 4, 0, 0},
    };
/* clang-format on */

static void output(int m[][9])
{
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", m[i][j]);
        }
        putchar('\n');
    }
}

static int row_include(int m[][9], int i, int x)
{
    int j;
    for (j = 0; j < 9; j++)
        if (m[i][j] == x)
            return 1;
    return 0;
}

static int col_include(int m[][9], int j, int x)
{
    int i;
    for (i = 0; i < 9; i++)
        if (m[i][j] == x)
            return 1;
    return 0;
}

static int sqr_include(int m[][9], int i, int j, int x)
{
    int ii, jj;
    for (ii = i / 3 * 3; ii <= i / 3 * 3 + 2; ii++)
        for (jj = j / 3 * 3; jj <= j / 3 * 3 + 2; jj++) {
            if (m[ii][jj] == x)
                return 1;
        }
    return 0;
}

static void next_pos(int pos[2], int m[][9], int i, int j)
{
    do {
        j++;
        if (j == 9) {
            i++;
            j = 0;
        }
        if (i == 9) {
            pos[0] = pos[1] = -1;
            return;
        }
    } while (m[i][j] != 0);
    pos[0] = i;
    pos[1] = j;
}

static void solve(int m[][9], int i, int j)
{
    int a;
    int n[2];
    next_pos(n, m, i, j);
    if (n[0] == -1) {
        output(m);
        return;
    }
    for (a = 1; a <= 9; a++) {
        if (row_include(m, n[0], a) || col_include(m, n[1], a) || sqr_include(m, n[0], n[1], a)) {
            continue;
        }
        m[n[0]][n[1]] = a;
        solve(m, n[0], n[1]);
        m[n[0]][n[1]] = 0;
    }
}

int main(void)
{
    solve(m, 0, -1);
    return 0;
}
