#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>

static struct termios g_orig_term_attr;

void set_term()
{
    struct termios term_attr;
    tcgetattr(fileno(stdin), &g_orig_term_attr);
    memcpy(&term_attr, &g_orig_term_attr, sizeof(struct termios));
    term_attr.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(fileno(stdin), TCSANOW, &term_attr);
}

void reset_term()
{
    tcsetattr(fileno(stdin), TCSANOW, &g_orig_term_attr);
    printf("\x1B[m");
}

int get_key()
{
    int k;
    int key;
    int flag;
    key = fgetc(stdin);
    if (key != 0x1B)
        return key;
    flag = fcntl(fileno(stdin), F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fileno(stdin), F_SETFL, flag);
    while ((k = fgetc(stdin)) != EOF) {
        key = ((key << 8) | (k & 0x000000FF));
    }
    flag &= ~O_NONBLOCK;
    fcntl(fileno(stdin), F_SETFL, flag);
    return key;
}

void move_cursor_to(int x, int y)
{
    printf("\x1B[%d;%dH", y, x);
}

void set_color(int color)
{
    printf("\x1B[%dm", 30 + color);
}

void set_backcolor(int color)
{
    printf("\x1B[%dm", 40 + color);
}

void hide_cursor()
{
    printf("\x1B[?25l");
}

void show_cursor()
{
    printf("\x1B[?25h");
}

void clear_screen()
{
    printf("\x1B[2J");
}

void del_to_end()
{
    printf("\x1B[K");
}
