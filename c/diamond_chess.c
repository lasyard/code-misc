/* This program does not run fast enough. Maybe the optimal solution cannot be found
   during your whole life */

#include <stdio.h>

struct jump {
    int x1, y1;
    int x2, y2;
};

/* clang-format off */
static int map[7][7] = {
    {2, 2, 1, 1, 1, 2, 2},
    {2, 2, 1, 1, 1, 2, 2},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {2, 2, 1, 1, 1, 2, 2},
    {2, 2, 1, 1, 1, 2, 2},
    };
/* clang-format on */

#define VALID(x, y)            (0 <= (x) && (x) < 7 && 0 <= (y) && (y) < 7)
#define OCCUPIED(x, y)         (VALID(x, y) && map[y][x] == 1)
#define VACANCY(x, y)          (VALID(x, y) && map[y][x] == 0)
#define CAN_MOVE(x, y, dx, dy) (VACANCY((x) + 2 * (dx), (y) + 2 * (dy)) && OCCUPIED((x) + (dx), (y) + (dy)))

static struct jump jump[32];
static int top = 0;

static void output_jump(const struct jump *j)
{
    printf("(%d, %d) -> (%d, %d)  ", j->x1, j->y1, j->x2, j->y2);
}

static void output()
{
    int i;
    int moves = 1;
    for (i = 1; i < top; i++) {
        if (jump[top].x1 != jump[top - 1].x2 || jump[top].y1 != jump[top - 1].y2)
            moves++;
    }
    printf("%d moves:", moves);
    for (i = 0; i < top; i++) {
        if (i % 3 == 0)
            printf("\n");
        output_jump(&jump[i]);
    }
    printf("\n");
}

static void push_jump(x1, y1, x2, y2)
{
    map[y1][x1] = 0;
    map[(y1 + y2) / 2][(x1 + x2) / 2] = 0;
    map[y2][x2] = 1;
    jump[top].x1 = x1;
    jump[top].y1 = y1;
    jump[top].x2 = x2;
    jump[top].y2 = y2;
    top++;
}

static void pop_jump()
{
    int x1, y1, x2, y2;
    top--;
    x1 = jump[top].x1;
    y1 = jump[top].y1;
    x2 = jump[top].x2;
    y2 = jump[top].y2;
    map[y2][x2] = 0;
    map[(y1 + y2) / 2][(x1 + x2) / 2] = 1;
    map[y1][x1] = 1;
}

static int move(int x1, int y1, int x2, int y2)
{
    int ok = 0;
    int i, j;
    push_jump(x1, y1, x2, y2);
    if (top == 31) {
        if (map[3][3] == 1) {
            output();
            ok = 1;
        }
    } else {
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (!OCCUPIED(i, j))
                    continue;
                if (CAN_MOVE(i, j, -1, 0))
                    ok = move(i, j, i - 2, j) || ok;
                if (CAN_MOVE(i, j, 0, -1))
                    ok = move(i, j, i, j - 2) || ok;
                if (CAN_MOVE(i, j, 1, 0))
                    ok = move(i, j, i + 2, j) || ok;
                if (CAN_MOVE(i, j, 0, 1))
                    ok = move(i, j, i, j + 2) || ok;
            }
        }
    }
    pop_jump();
    return ok;
}

int main(void)
{
    if (!move(1, 3, 3, 3))
        printf("Failed!\n");
    return 0;
}
