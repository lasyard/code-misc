#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_DISK_NUMBER 9

static void show_move(int disk, int from, int to)
{
    static int steps = 0;
    steps++;
    printf("Step %04d: Disk %2d, %1d -> %1d\n", steps, disk, from, to);
}

static void move_disk(int disk, int from, int to)
{
    if (disk > 0) {
        int other = 3 - from - to;
        move_disk(disk - 1, from, other);
        show_move(disk, from, to);
        move_disk(disk - 1, other, to);
    }
}

int main(int argc, char *argv[])
{
    int disk_number = DEFAULT_DISK_NUMBER;
    if (argc > 2) {
        fprintf(stderr, "Too many arguments!\n");
        return -1;
    } else if (argc == 2) {
        disk_number = atoi(argv[1]);
        if (disk_number == 0) {
            fprintf(stderr, "The argument must be a number.\n");
            return -1;
        }
    }
    move_disk(disk_number, 0, 1);
    return 0;
}
