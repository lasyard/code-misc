/* Run slow if the chessboard is larger */

#include <stdio.h>

#define MAP_SIZE_X 8
#define MAP_SIZE_Y 4
#define START_X 0
#define START_Y 0

static int map[MAP_SIZE_Y][MAP_SIZE_X];
static int steps;

static int hop_from(int x, int y);

static void output()
{
    int i, j;
    for (i = 0; i < MAP_SIZE_Y; i++) {
        for (j = 0; j < MAP_SIZE_X; j++)
            printf("%5d", map[i][j]);
        printf("\n");
    }
}

static int hop_to(int x, int y)
{
    int ok = 0;
    if (0 <= x && x < MAP_SIZE_X && 0 <= y && y < MAP_SIZE_Y && map[y][x] == 0) {
        steps++;
        map[y][x] = steps;
        if (steps == MAP_SIZE_X * MAP_SIZE_Y) {
            output();
            ok = 1;
        } else {
            ok = hop_from(x, y);
        }
    }
    return ok;
}

static int hop_from(int x, int y)
{
    int ok = 0;
    ok = ok || hop_to(x - 2, y - 1) || hop_to(x - 2, y + 1);
    ok = ok || hop_to(x - 1, y + 2) || hop_to(x + 1, y + 2);
    ok = ok || hop_to(x + 2, y + 1) || hop_to(x + 2, y - 1);
    ok = ok || hop_to(x + 1, y - 2) || hop_to(x - 1, y - 2);
    map[y][x] = 0;
    steps--;
    return ok;
}

int main(void)
{
    int i, j;
    for (i = 0; i < MAP_SIZE_Y; i++)
        for (j = 0; j < MAP_SIZE_X; j++)
            map[i][j] = 0;
    steps = 1;
    map[START_Y][START_X] = steps;
    printf("Searching...\n");
    if (!hop_from(START_X, START_Y))
        printf("Failed!\n");
    return 0;
}
