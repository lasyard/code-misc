#ifndef _TERM_LINUX_H_
#define _TERM_LINUX_H_

#ifdef __cplusplus
extern "C" {
#endif

void set_term();
void reset_term();

int get_key();

void move_cursor_to(int x, int y);
void set_color(int color);
void set_backcolor(int color);
void hide_cursor();
void show_cursor();
void clear_screen();
void del_to_end();

#ifdef __cplusplus
}
#endif

#endif
