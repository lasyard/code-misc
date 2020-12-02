#include <stdio.h>

#define QUEENS 8

static int pos[QUEENS]; /* Position of queen */

static void output()
{
    static int count = 0;
    int i;
    count++;
    printf("Solution %3d: ", count);
    for (i = 0; i < QUEENS; i++) {
        printf("%3d", pos[i] + 1);
    }
    printf("\n");
}

static void put_queen(int line)
{
    int i, j;
    for (i = 0; i < QUEENS; i++) {
        for (j = 0; j < line; j++) {
            if (i == pos[j] || i - pos[j] == line - j || pos[j] - i == line - j)
                break;
        }
        if (j == line) {
            pos[line] = i;
            if (line == QUEENS - 1) {
                output();
            } else {
                put_queen(line + 1);
            }
        }
    }
}

int main(void)
{
    put_queen(0);
    return 0;
}
