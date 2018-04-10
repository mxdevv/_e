#ifndef _E_ESC_CPP
#define _E_ESC_CPP

namespace _e {
namespace esc {

#define ESC "\e["

enum struct format {
	reset = 0, bright, dim, underscope, blink, reverse, hidden };

enum struct fg_color {
	black = 30, red, green, yellow, blue, magenta, cyan, white };

enum struct bg_color {
	black = 40, red, green, yellow, blue, magenta, cyan, white };

inline void fg_color(fg_color clr)
{
	printf(ESC "%dm", clr);
}

inline void bg_color(bg_color clr)
{
	printf(ESC "%dm", clr);
}

inline void format(format frmt)
{
	printf(ESC "%dm", frmt);
}

inline void clr_scr()
{
	printf(ESC "2J");
}

inline void move_xy(int x, int y)
{
	printf(ESC "%d;%dH", y, x);
}

inline int get_cursor_xy(int& width, int& height)
{
	fputs(ESC "6n", stdout);
	return scanf(ESC "%d;%dR", &height, &width) == 2;
}

inline int get_term_size(int& width, int& height)
{
	//setvbuf(stdout, NULL, _IONBF, 0);
	fputs(ESC "255;255H" ESC "6n", stdout);
	return scanf(ESC "%d;%dR", &height, &width) == 2;
}

} // esc
} // _e

#endif
