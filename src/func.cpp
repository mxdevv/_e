#ifndef _E_FUNCS_CPP
#define _E_FUNCS_CPP

#include "consts.cpp"

namespace _e {
namespace func {

void cat()
{
	for(auto& v : data::lines) {
		for(auto& ch : v)
			std::cout << ch;
		std::cout << '\n';
	}
}

inline void esc(auto val)
{
	printf("\e[%dm", val);
}

inline void clr_scr()
{
	printf("\e[2J");
}

inline void move_xy(int x, int y)
{
	printf("\e[%d;%dH", y, x);
}

inline int get_cursor_xy(int& width, int& height)
{
	fputs("\e[6n", stdout);
	return scanf("\e[%d;%dR", &height, &width) == 2;
}

inline int get_term_size(int& width, int& height)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	fputs("\e[255;255H\e[6n", stdout);
	return scanf("\e[%d;%dR", &height, &width) == 2;
}

void open()
{
	data::ifs.open(data::file_name);
	data::lines.push_back( { } );

	char ch;
	while(data::ifs) {
		data::ifs.get(ch);
		if (ch == '\n')
			data::lines.push_back( { } );
		else
			data::lines.back().push_back(ch);
	}

	// после удалить //
	esc(esc::fg_color::yellow);
	cat();
	esc(esc::reset);
}

void help()
{
	std::cout << lang::help << '\n';
}

} // funcs
} // _e

#endif
