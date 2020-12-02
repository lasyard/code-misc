/* Compile it with
 * gcc -Wall user_setkeycode.c
 */

#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct code_pair {
    int scancode;
    int keycode;
};

int main(int argc, char *argv[])
{
    int fd;
    struct code_pair codes;
    if (argc < 4) {
        printf("Usage: %s /dev/input/eventX scancode keycode\n", argv[0]);
        printf("Where X = input device number\n");
        return -1;
    }
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        return -1;
    }
    codes.scancode = strtol(argv[2], NULL, 0);
    codes.keycode = strtol(argv[3], NULL, 0);
    ioctl(fd, EVIOCSKEYCODE, &codes);
    close(fd);
    return 0;
}
