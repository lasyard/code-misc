#include <stdio.h>

#define RINGS 9

static int pos[RINGS];

static void move_ring(int ring, int to)
{
    static int steps = 0;
    int i;
    steps++;
    pos[ring] = to;
    printf("Step %3d: Ring %2d %-5s->", steps, ring, to ? "Up" : "Down");
    for (i = 0; i < RINGS; i++)
        printf("%d", pos[i]);
    printf("\n");
}

static void move_all_rings(int ring, int to)
{
    if (to && ring >= 1)
        move_all_rings(ring - 1, to);
    if (ring >= 2)
        move_all_rings(ring - 2, 0);
    move_ring(ring, to);
    if (ring >= 2)
        move_all_rings(ring - 2, 1);
    if (!to && ring >= 1)
        move_all_rings(ring - 1, to);
}

int main(void)
{
    int i;
    for (i = 0; i < RINGS; i++)
        pos[i] = 1;
    move_all_rings(RINGS - 1, 0);
    return 0;
}
