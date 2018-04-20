#ifndef _E_FUNCS_H
#define _E_FUNCS_H

namespace _e {
namespace func {

void redraw_text_view();
void clear_previous_status();
void place_cursor();
inline void esc(auto val);
inline void clr_scr();
inline void move_xy(int x, int y);
inline int get_cursor_xy(int& width, int& height);
inline int get_term_size(int& width, int& height);
void open_or_create();
void help();
void up_pos();
void down_pos();
void left_pos();
void right_pos();
inline void terminate();

} // funcs
} // _e

#endif // _E_FUNCS_H
