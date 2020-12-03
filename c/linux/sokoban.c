/* Compile it with:
 * gcc -Wall sokoban.c libs/term_linux.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/term_linux.h"

#define BUF_SIZE 127

#define FLOOR 0x00000000
#define WALL  0x00000001
#define GOAL  0x00000002
#define BOX   0x00010000
#define MAN   0x00020000

struct level {
    int map_x, map_y;
    int **map;
    int count;
    int man_x, man_y;
};

static struct level g_level;

static int read_level(struct level *lv, const char *file)
{
    int i, j;
    FILE *fp;
    char buf[BUF_SIZE + 1];
    lv->count = 0;
    lv->map_x = 0;
    lv->map_y = 0;
    fp = fopen(file, "r");
    if (fp == NULL)
        return 0;
    while (fgets(buf, BUF_SIZE, fp) != NULL) {
        int len;
        buf[BUF_SIZE] = '\0';
        len = strlen(buf);
        if (len > lv->map_x)
            lv->map_x = len;
        lv->map_y++;
    }
    lv->map = malloc(lv->map_y * sizeof(int *));
    if (lv->map == NULL)
        return 0;
    rewind(fp);
    for (i = 0; i < lv->map_y; i++) {
        lv->map[i] = malloc(lv->map_x * sizeof(int));
        if (lv->map[i] == NULL)
            break;
        memset(lv->map[i], 0, lv->map_x * sizeof(int));
        if (fgets(buf, BUF_SIZE, fp) == NULL)
            break;
        for (j = 0; j < lv->map_x; j++) {
            char ch = buf[j];
            if (ch == '\0' || ch == '\r' || ch == '\n')
                break;
            switch (ch) {
            case '-':
            case ' ':
                lv->map[i][j] = FLOOR;
                break;
            case '#':
                lv->map[i][j] = WALL;
                break;
            case '$':
                lv->map[i][j] = BOX;
                lv->count++;
                break;
            case '.':
                lv->map[i][j] = GOAL;
                break;
            case '*':
                lv->map[i][j] = (BOX | GOAL);
                break;
            case '@':
                lv->map[i][j] = FLOOR;
                lv->man_x = j;
                lv->man_y = i;
                break;
            case '+':
                lv->map[i][j] = GOAL;
                lv->man_x = j;
                lv->man_y = i;
            default:
                break;
            }
        }
    }
    if (i < lv->map_y) {
        while (--i >= 0)
            free(lv->map[i]);
        return 0;
    }
    fclose(fp);
    return 1;
}

static void release_level(struct level *lv)
{
    int i;
    for (i = 0; i < lv->map_y; i++)
        free(lv->map[i]);
    free(lv->map);
}

static int is_victory(const struct level *lv)
{
    if (lv->count == 0) {
        move_cursor_to(0, lv->map_y + 1);
        printf("You are smart!\n");
        return 1;
    }
    return 0;
}

static void show(int x, int y, int type)
{
    move_cursor_to(x * 2 + 1, y + 1);
    switch (type) {
    case FLOOR:
        set_backcolor(0);
        puts("  ");
        break;
    case WALL:
        set_backcolor(7);
        puts("  ");
        break;
    case GOAL:
        set_backcolor(4);
        puts("  ");
        break;
    case BOX:
        set_backcolor(1);
        puts("  ");
        break;
    case BOX | GOAL:
        set_backcolor(5);
        puts("  ");
        break;
    case MAN:
        set_backcolor(2);
        puts("  ");
        break;
    default:
        break;
    }
}

static void show_level(const struct level *lv)
{
    int i, j;
    for (i = 0; i < lv->map_y; i++) {
        for (j = 0; j < lv->map_x; j++) {
            show(j, i, lv->map[i][j]);
        }
    }
    show(lv->man_x, lv->man_y, MAN);
}

static int move_box(struct level *lv, int x, int y, int dx, int dy)
{
    int xx, yy;
    xx = x + dx;
    yy = y + dy;
    if (lv->map[yy][xx] == WALL || (lv->map[yy][xx] & BOX) == BOX)
        return 0;
    if (lv->map[y][x] == (BOX | GOAL))
        lv->count++;
    lv->map[y][x] &= ~BOX;
    show(x, y, lv->map[y][x]);
    lv->map[yy][xx] |= BOX;
    show(xx, yy, lv->map[yy][xx]);
    if (lv->map[yy][xx] == (BOX | GOAL))
        lv->count--;
    return 1;
}

static int move_man(struct level *lv, int dx, int dy)
{
    int xx, yy;
    xx = lv->man_x + dx;
    yy = lv->man_y + dy;
    if (lv->map[yy][xx] == WALL)
        return 0;
    if ((lv->map[yy][xx] & BOX) == BOX && !move_box(lv, xx, yy, dx, dy))
        return 0;
    show(lv->man_x, lv->man_y, lv->map[lv->man_y][lv->man_x]);
    lv->man_x = xx;
    lv->man_y = yy;
    show(lv->man_x, lv->man_y, MAN);
    return 1;
}

int main(int argc, char *argv[])
{
    int quit;
    const char *file = "default.xsb";
    if (argc == 2) {
        file = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Please input XSB file name.\n");
        return -1;
    }
    if (!read_level(&g_level, file)) {
        fprintf(stderr, "Error reading xsb file!\n");
        return -1;
    }
    set_term();
    hide_cursor();
    clear_screen();
    show_level(&g_level);
    for (quit = 0; !quit;) {
        switch (get_key()) {
        case 0x1B:
            quit = 1;
            break;
        case 0x1B5B41: /* up */
            move_man(&g_level, 0, -1);
            break;
        case 0x1B5B42: /* down */
            move_man(&g_level, 0, 1);
            break;
        case 0x1B5B43: /* right */
            move_man(&g_level, 1, 0);
            break;
        case 0x1B5B44: /* left */
            move_man(&g_level, -1, 0);
            break;
        default:
            break;
        }
        if (is_victory(&g_level))
            quit = 1;
    }
    show_cursor();
    reset_term();
    release_level(&g_level);
    return 0;
}
