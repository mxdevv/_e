#ifndef _E_FUNCS_H
#define _E_FUNCS_H

namespace _e {
namespace func {

void getch();
void redraw();
void cat();
inline void esc(auto val);
inline void clr_scr();
inline void move_xy(int x, int y);
inline int get_cursor_xy(int& width, int& height);
inline int get_term_size(int& width, int& height);
void open_or_create();
void help();

} // funcs
} // _e

#endif
