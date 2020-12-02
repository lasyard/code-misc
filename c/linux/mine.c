/* Compile it with:
 * gcc -Wall mine.c libs/term_linux.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "libs/term_linux.h"

#define random(x) (rand() % (x))

#define MAP_Y 20
#define MAP_X 40
#define MINE_NUMBER 120

#define BASE_LINE (MAP_Y + 4)

enum COLOR { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };

struct cell {
    int num;
    int mine;
    int opened;
    int marked;
    int exploded;
};

struct game {
    struct cell map[MAP_X][MAP_Y];
    int mine_left;
    int open_count;
    int auto_mark;
    int dead;
};

#define POS_VALID(x, y) (0 <= (x) && (x) < MAP_X && 0 <= (y) && (y) < MAP_Y)

typedef int cell_fun(struct game *, int, int); /* used by around_cell() */

static struct game g_game;

static int open_around(struct game *g, int x, int y);
static int auto_mark(struct game *g, int x, int y);

static void output(char symbol, enum COLOR backcolor, enum COLOR color, int x, int y)
{
    set_backcolor(backcolor);
    set_color(color);
    move_cursor_to(x + 1, y + 1);
    putchar(symbol);
}

static void show_covered_cell(x, y)
{
    output(' ', WHITE, BLUE, x, y);
}

static void show_opened_cell(int x, int y, int num)
{
    static enum COLOR color[9] = {BLUE, WHITE, CYAN, GREEN, YELLOW, RED, PURPLE, PURPLE, PURPLE};
    if (num == 0) {
        output(' ', BLUE, color[num], x, y);
    } else {
        output((char)(0x30 | num), BLUE, color[num], x, y);
    }
}

static void show_marked_cell(int x, int y)
{
    output('P', YELLOW, BLUE, x, y);
}

static void show_exploded_cell(int x, int y)
{
    output('X', RED, GREEN, x, y);
}

static void update_mine_num(int num)
{
    move_cursor_to(1, BASE_LINE - 2);
    set_backcolor(BLACK);
    set_color(RED);
    printf("Bomb left: %3d", num);
}

static void show_auto_mark(int mark)
{
    move_cursor_to(60, BASE_LINE - 2);
    set_backcolor(BLACK);
    set_color(YELLOW);
    printf("%c", mark ? 'A' : ' ');
}

static void failed()
{
    move_cursor_to(20, BASE_LINE - 2);
    set_backcolor(BLACK);
    set_color(RED);
    puts("You have been bombed!");
}

static void victory()
{
    move_cursor_to(20, BASE_LINE - 2);
    set_backcolor(BLACK);
    set_color(GREEN);
    puts("Mission accomplished!");
}

static int marked(struct game *g, int x, int y)
{
    return g->map[x][y].marked;
}

static int covered(struct game *g, int x, int y)
{
    return !g->map[x][y].opened && !g->map[x][y].marked;
}

static int add_mine_number(struct game *g, int x, int y)
{
    if (!g->map[x][y].mine)
        g->map[x][y].num++;
    return 0;
}

static int around_cell(struct game *g, int x, int y, cell_fun *to_do)
{
    int i, j;
    int count = 0;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (POS_VALID(x + i, y + j) && to_do(g, x + i, y + j))
                count++;
        }
    }
    return count;
}

static void init_map(struct game *g)
{
    int i, j;
    for (i = 0; i < MAP_X; i++) {
        for (j = 0; j < MAP_Y; j++) {
            g->map[i][j].num = 0;
            g->map[i][j].mine = 0;
            g->map[i][j].opened = 0;
            g->map[i][j].marked = 0;
            g->map[i][j].exploded = 0;
            show_covered_cell(i, j);
        }
    }
}

static void set_map(struct game *g)
{
    int i;
    int x, y;
    init_map(g);
    for (i = 0; i < MINE_NUMBER;) {
        x = random(MAP_X);
        y = random(MAP_Y);
        if (!g->map[x][y].mine) {
            g->map[x][y].mine = 1;
            around_cell(g, x, y, add_mine_number);
            i++;
        }
    }
    g->open_count = 0;
    g->mine_left = MINE_NUMBER;
    update_mine_num(g->mine_left);
}

static void init_game(struct game *g)
{
    set_backcolor(BLACK);
    set_color(WHITE);
    clear_screen();
    move_cursor_to(1, BASE_LINE);
    printf("ESC=Quit | Enter=Open | Insert=Mark | Delete=Erase Mark | A=Auto");
    set_map(g);
    g->auto_mark = 0;
    show_auto_mark(g->auto_mark);
    g->dead = 0;
}

static int open_cell(struct game *g, int x, int y)
{
    if (covered(g, x, y)) {
        if (g->map[x][y].mine) {
            g->map[x][y].exploded = 1;
            show_exploded_cell(x, y);
            g->dead = 1;
        } else {
            g->map[x][y].opened = 1;
            show_opened_cell(x, y, g->map[x][y].num);
            open_around(g, x, y);
            if (g->auto_mark)
                around_cell(g, x, y, auto_mark);
            g->open_count++;
        }
    }
    return 0;
}

static int open_around(struct game *g, int x, int y)
{
    if (g->map[x][y].opened) {
        if (g->map[x][y].num == around_cell(g, x, y, marked)) {
            around_cell(g, x, y, open_cell);
        }
    }
    return 0;
}

static int mark_cell(struct game *g, int x, int y)
{
    if (covered(g, x, y)) {
        g->mine_left--;
        update_mine_num(g->mine_left);
        g->map[x][y].marked = 1;
        show_marked_cell(x, y);
        if (g->auto_mark) {
            around_cell(g, x, y, open_around);
            around_cell(g, x, y, auto_mark);
        }
    }
    return 0;
}

static void erase_mark(struct game *g, int x, int y)
{
    if (g->map[x][y].marked) {
        g->mine_left++;
        update_mine_num(g->mine_left);
        g->map[x][y].marked = 0;
        show_covered_cell(x, y);
    }
}

static int auto_mark(struct game *g, int x, int y)
{
    if (g->map[x][y].opened) {
        int a = around_cell(g, x, y, marked);
        int b = around_cell(g, x, y, covered);
        if (g->map[x][y].num - a == b)
            around_cell(g, x, y, mark_cell);
    }
    return 0;
}

int main(void)
{
    int k;
    int x, y;
    int quit;
    srand(time(NULL));
    set_term();
    while (1) {
        init_game(&g_game);
        x = MAP_X / 2;
        y = MAP_Y / 2;
        move_cursor_to(x + 1, y + 1);
        quit = 0;
        while (!quit && !g_game.dead && g_game.open_count < MAP_Y * MAP_X - MINE_NUMBER) {
            switch (k = get_key()) {
            case 0x1B:
                quit = 1;
                break;
            case 0x0A:
                if (covered(&g_game, x, y)) {
                    open_cell(&g_game, x, y);
                } else {
                    open_around(&g_game, x, y);
                }
                break;
            case 0x1B5B41: /* up */
                if (y > 0)
                    y--;
                break;
            case 0x1B5B42: /* down */
                if (y < MAP_Y - 1)
                    y++;
                break;
            case 0x1B5B43: /* right */
                if (x < MAP_X - 1)
                    x++;
                break;
            case 0x1B5B44: /* left */
                if (x > 0)
                    x--;
                break;
            case 0x1B5B327E: /* insert */
                mark_cell(&g_game, x, y);
                break;
            case 0x1B5B337E: /* delete */
                erase_mark(&g_game, x, y);
                break;
            case 'a':
            case 'A':
                g_game.auto_mark = !g_game.auto_mark;
                show_auto_mark(g_game.auto_mark);
                break;
            default:
                break;
            }
            move_cursor_to(x + 1, y + 1);
        }
        if (!quit) {
            if (g_game.dead) {
                failed();
            } else {
                victory();
            }
        }
        move_cursor_to(1, BASE_LINE);
        set_backcolor(BLACK);
        set_color(WHITE);
        del_to_end();
        puts("ESC to quit. Any key else to play again.");
        if (get_key() == 0x1B)
            break;
    }
    reset_term();
    return 0;
}
