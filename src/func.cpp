#ifndef _E_FUNCS_CPP
#define _E_FUNCS_CPP

#include "data.cpp"
#include "keybind.cpp"

namespace _e {
namespace func {

void redraw_lines()
{
	term::clr_scr();
	for(int i = data::shift[data::shift.current];
			i < data::text_view_size.y + data::shift[data::shift.current]
			&& i < data::lines.size(); i++) {
		term::move_cursor(1, i + 1 - data::shift[data::shift.current]);
		for(int j = 0; j < data::lines[i].size(); j++) {
			putc(data::lines[i][j], stdout);
		}
	}
	for(int i = data::lines.size() - data::shift[data::shift.current];
			i <= data::text_view_size.y; i++)
	{
		term::move_cursor(1, i);
		putc('~', stdout);
	}
}

void clear_previous_status()
{
	term::move_cursor(
			2 + alg::utf8_strlen(data::status_bar[data::status_bar.current]),
			data::term_size.y);
	for(int i = alg::utf8_strlen(data::status_bar[data::status_bar.previous])
			- alg::utf8_strlen(data::status_bar[data::status_bar.current]);
			i > 0; i--)
		putc(' ', stdout);
}

void place_cursor()
{
	term::move_cursor(data::pos.x,
			data::pos.y - data::shift[data::shift.current]);
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
	if (data::pos.y <= data::shift[data::shift.current])
		data::shift[data::shift.current]--;
}

void down_pos()
{
	if (data::lines.size() - 1 > data::pos.y)
		data::pos.y++;
	correct_x();
	if (data::pos.y > data::text_view_size.y + data::shift[data::shift.current])
		data::shift[data::shift.current]++;
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
