#ifndef _E_TERM_CPP
#define _E_TERM_CPP

namespace _e {
namespace term {

// ESC
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

inline void move_cursor(int x, int y)
{
	printf(ESC "%d;%dH", y, x);
}

inline int get_cursor(int& width, int& height)
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

inline void show_cursor()
{
	fputs(ESC "?25h", stdout);
}

inline void hide_cursor()
{
	fputs(ESC "?25l", stdout);
}
// end ESC

struct termios newt, oldt;

void init()
{
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
}

void nocanon_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void default_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

} // term
} // _e

#endif
