#ifndef _E_FUNCS_CPP
#define _E_FUNCS_CPP

#include "data.cpp"
#include "keybind.cpp"

namespace _e {
namespace func {

void redraw_lines()
{
	term::hide_cursor();

	for(int i = 0; i < data::text_view_size.y
			&& i < data::lines.size(); i++) {
		term::move_cursor(1, i + 1);
		for(int j = 0; j < data::lines[i].size(); j++) {
			putc(data::lines[i][j], stdout);
		}
	}
	for(int i = data::lines.size(); i <= data::text_view_size.y; i++)
	{
		term::move_cursor(1, i);
		putc('~', stdout);
	}

	term::move_cursor(data::pos.x, data::pos.y);
	term::show_cursor();
}

void open_or_create()
{
	data::ifs.open(data::file_name);
	
	if (data::ifs.is_open()) {
		data::lines.push_back( { } );

		char ch;
		while(data::ifs) {
			data::ifs.get(ch);
			if (ch == '\n')
				data::lines.push_back( { } );
			else
				data::lines.back().push_back(ch);
		}
	} else {
		fputs("Файла нет.\n", stdout);
	}

	data::ifs.close();
}

void help()
{
	fputs(lang::help, stdout);
	putc('\n', stdout);
}

void correct_x()
{
	if (data::lines[data::pos.y - 1].size() < data::pos.x)
		data::pos.x = data::lines[data::pos.y - 1].size();
}

void up_pos()
{
	if (data::pos.y > 1)
		data::pos.y--;
	correct_x();
}

void down_pos()
{
	if (data::lines.size() - 1 > data::pos.y)
		data::pos.y++;
	correct_x();
}

void left_pos()
{
	if (data::pos.x > 1)
		data::pos.x--;
}

void right_pos()
{
	if (data::lines[data::pos.y - 1].size() > data::pos.x)
		data::pos.x++;
}

inline void terminate()
{
	data::interactive.final();
}

} // funcs
} // _e

#endif // _E_FUNCS_CPP
