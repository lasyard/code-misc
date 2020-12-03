/* Compile it with:
 * gcc -Wall pick.c libs/term_linux.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "libs/term_linux.h"

#define random(x) (rand() % (x))

#define HEIGHT    15
#define BASE_LINE (HEIGHT + 5)
#define COIN      "====="
#define SPACE     "     "
#define WIDTH     5
#define GAP       (WIDTH + 1)

struct game {
    void (*turn)(struct game *g);
    int columns;
    int total;
    int pos;
    int *num;
};

static struct game g_game;

static void player_turn(struct game *g);
static void computer_turn(struct game *g);

static void move(struct game *g, int dx)
{
    g->pos += dx + g->columns;
    g->pos %= g->columns;
    move_cursor_to(g->pos * GAP + WIDTH / 2 + 1, BASE_LINE);
}

static void update_num(const struct game *g, int pos)
{
    move_cursor_to(pos * GAP + WIDTH / 2, BASE_LINE);
    printf("%2d", g->num[pos]);
    move_cursor_to(1, 2);
    set_color(1);
    printf("Total: %3d", g->total);
    move_cursor_to(g->pos * GAP + WIDTH / 2 + 1, BASE_LINE);
}

static void put(struct game *g, int pos, int num)
{
    int i;
    g->num[pos] += num;
    g->total += num;
    set_color(pos % 2 ? 1 : 2);
    for (i = BASE_LINE - 1 - g->num[pos] + num; i > BASE_LINE - 1 - g->num[pos]; i--) {
        move_cursor_to(pos * GAP + 1, i);
        puts(COIN);
    }
    update_num(g, pos);
}

static void pick(struct game *g, int pos, int num)
{
    int i;
    g->num[pos] -= num;
    g->total -= num;
    for (i = BASE_LINE - g->num[pos] - num; i < BASE_LINE - g->num[pos]; i++) {
        move_cursor_to(pos * GAP + 1, i);
        puts(SPACE);
    }
    update_num(g, pos);
}

static void computer_win(struct game *g)
{
    set_color(1);
    move_cursor_to(1, BASE_LINE + 1);
    puts("You lose!");
}

static void player_win(struct game *g)
{
    set_color(2);
    move_cursor_to(1, BASE_LINE + 1);
    puts("You win!");
}

static void computer_turn(struct game *g)
{
    int i;
    int verify;
    verify = 0;
    for (i = 0; i < g->columns; i++)
        verify ^= g->num[i];
    if (verify == 0) {
        i = random(g->columns);
        while (g->num[i] == 0)
            i = random(g->columns);
        pick(g, i, random(g->num[i]) + 1);
    } else {
        for (i = 0; i < g->columns && (verify ^ g->num[i]) >= g->num[i]; i++)
            ;
        pick(g, i, g->num[i] - (verify ^ g->num[i]));
    }
    g->turn = (g->total == 0) ? computer_win : player_turn;
}

static void player_turn(struct game *g)
{
    int num = g->num[g->pos];
    while (g->turn == player_turn) {
        switch (get_key()) {
        case 0x1B:
            g->turn = computer_win;
            break;
        case 0x0A:
            if (g->num[g->pos] < num) {
                g->turn = (g->total == 0) ? player_win : computer_turn;
            }
            break;
        case 0x1B5B41: /* up */
            if (g->num[g->pos] < num)
                put(g, g->pos, 1);
            break;
        case 0x1B5B42: /* down */
            if (g->num[g->pos] > 0)
                pick(g, g->pos, 1);
            break;
        case 0x1B5B43: /* right */
            if (g->num[g->pos] == num) {
                move(g, 1);
                num = g->num[g->pos];
            }
            break;
        case 0x1B5B44: /* left */
            if (g->num[g->pos] == num) {
                move(g, -1);
                num = g->num[g->pos];
            }
            break;
        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    int i;
    int k;
    g_game.columns = 5;
    if (argc == 2) {
        g_game.columns = atoi(argv[1]);
        if (g_game.columns < 3 || g_game.columns > 12) {
            fprintf(stderr, "The number of columns must be within 3 - 12.\n");
            return -1;
        }
    } else if (argc > 2) {
        fprintf(stderr, "Please input number of columns.\n");
        return -1;
    }
    srand(time(NULL));
    set_term();
    g_game.num = malloc(g_game.columns * sizeof(int));
    if (g_game.num == NULL) {
        fprintf(stderr, "Cannot allocate memory!\n");
        return -1;
    }
    do {
        clear_screen();
        for (i = 0; i < g_game.columns; i++)
            g_game.num[i] = 0;
        g_game.total = 0;
        g_game.pos = 0;
        for (i = 0; i < g_game.columns; i++)
            put(&g_game, i, random(HEIGHT) + 1);
        g_game.turn = player_turn;
        while (g_game.turn == computer_turn || g_game.turn == player_turn) {
            g_game.turn(&g_game);
        }
        g_game.turn(&g_game);
        set_color(7);
        printf("Try again? (Y)");
    } while ((k = get_key()) == 0x0A || k == (int)'y' || k == (int)'Y');
    free(g_game.num);
    reset_term();
    printf("\n");
    return 0;
}
