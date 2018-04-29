#ifndef _E_FUNCS_CPP
#define _E_FUNCS_CPP

namespace _e {
namespace func {

void clear_text_view()
{
	term::move_cursor(data::text_location.first.x, data::text_location.first.y);
	for(int i = 0; i < data::text_location.second.y; i++)
	for(int j = 0; j < data::text_location.second.x; j++)
		putc(' ', stdout);
}

#ifdef OLD_TERMINAL
	inline void clear_all()
		{ term::clr_scr(); }
#else
	void clear_all()
	{
		term::move_cursor(1, 1);
		for(int i = 0; i < data::term_size.y; i++)
		for(int j = 0; j < data::term_size.x; j++)
			putc(' ', stdout);
	}
#endif

void redraw_text_view()
{
	clear_text_view();

	pattern::Store<struc::Color_ch*> cur_col_ch = new struc::Color_ch;
	term::fg_color(cur_col_ch.current()->colors.fg);
	term::bg_color(cur_col_ch.current()->colors.bg);

	for(int i = data::shift.current();
			i < data::text_location.second.y + data::shift && i < data::text.size();
			i++)
	{
		term::move_cursor(1, i + 1 - data::shift);
		for(int j = 0; j < data::text[i].size(); j++) {
			
			// присваивание, которое можно оптимизировать
			cur_col_ch = &data::text[i][j];
			
			if (cur_col_ch.previous()->colors.fg != cur_col_ch.current()->colors.fg
				|| cur_col_ch.previous()->colors.bg != cur_col_ch.current()->colors.bg)
			{
				term::fg_color(cur_col_ch.current()->colors.fg);
				term::bg_color(cur_col_ch.current()->colors.bg);
			}

			putc(data::text[i][j].ch, stdout);
		}
	}
	for(int i = data::text.size() - data::shift;
			i <= data::text_location.second.y; i++)
	{
		term::move_cursor(1, i);
		putc('~', stdout);
	}
}

void clear_status()
{
	term::move_cursor(2, data::term_size.y);
	for(int i = 0; i < data::term_size.x; i++)
		fputc(' ', stdout);
}

void clear_previous_status()
{
	term::move_cursor(
			2 + strlen(data::status_bar.current()), data::term_size.y);
	for(int i = strlen(data::status_bar.previous())
			- strlen(data::status_bar.current());
			i > 0; i--)
		putc(' ', stdout);
}

void place_cursor()
{
	term::move_cursor(data::pos_cursor.x,
			data::pos_cursor.y - data::shift);
}

void open_or_create()
{
	data::ifs.open(data::file_name);

	if (data::ifs.is_open()) {
		data::text.new_ln();

		char ch;
		while(data::ifs) {
			data::ifs.get(ch);
			if (ch == '\n')
				data::text.new_ln();
			else if (ch == '\t')
				for(int i = data::tab_size; i-->0;)
					data::text.back().push_back( { ' ' } );
			else
				data::text.back().push_back( { ch } );
		}
	} else {
		fputs(lang::dont_have_file.c_str(), stdout);
		putc('\n', stdout);
	}

	// удаляет лишнюю пустую строку
	if (!data::text.empty()) data::text.resize(data::text.size() - 1);

	data::ifs.close();
}

void help()
{
	fputs(lang::help.c_str(), stdout);
	putc('\n', stdout);
}

void correct_x()
{
	if (data::text[data::pos_cursor.y - 1].size() < data::pos_cursor.x)
		data::pos_cursor.x = data::text[data::pos_cursor.y - 1].size() + 1;
}

void up_pos()
{
	if (data::pos_cursor.y > 1)
		data::pos_cursor.y--;
	correct_x();
	if (data::pos_cursor.y - data::up_pos_limit <= data::shift.current())
		if (data::shift > 0) data::shift--;
}

void down_pos()
{
	if (data::text.size() - 1 > data::pos_cursor.y)
		data::pos_cursor.y++;
	correct_x();
	if (data::pos_cursor.y + data::down_pos_limit
			> data::text_location.second.y + data::shift)
		data::shift++;
}

void left_pos()
{
	if (data::pos_cursor.x > 1)
		data::pos_cursor.x--;
}

void right_pos()
{
	if (data::text[data::pos_cursor.y - 1].size() >= data::pos_cursor.x)
		data::pos_cursor.x++;
}

void limit_left_pos()
{
	data::pos_cursor.x = 1;
}

void limit_right_pos()
{
	data::pos_cursor.x = data::text[data::pos_cursor.y - 1].size() + 2;
}

inline void terminate()
{
	data::interactive.final();
}

void add(int ch)
{
	switch(ch) {
	case 127: // backspace
		if (!data::text[data::pos_cursor.y - 1].empty())
			data::text.remove( { data::pos_cursor.x - 2, data::pos_cursor.y - 1 } );
		else {
			data::text.rm_ln(data::pos_cursor.y - 1);
			up_pos();
			limit_right_pos();
		}
		left_pos();
		break;
	case 9: // tab
		for(int i = data::tab_size; i-->0;) {
			data::text.add( { data::pos_cursor.x - 1, data::pos_cursor.y - 1}, ' ');
			right_pos();
		}
		break;
	case 10: // enter
		data::text.new_ln(data::pos_cursor.y);
		down_pos();
		break;
	default:
		data::text.add( { data::pos_cursor.x - 1, data::pos_cursor.y - 1}, ch);
		right_pos();

		// keycode test
		/*func::clear_all();
		term::format(term::Format::reset);
		std::cout << ch;
		sleep(1);*/

		break;
	}
}

void insert(int ch)
{
	switch(ch) {
	case 127: // backspace
		if (!data::text[data::pos_cursor.y - 1].empty())
			data::text.remove( { data::pos_cursor.x - 2, data::pos_cursor.y - 1 } );
		left_pos();
		break;
	case 9: // tab
		for(int i = data::tab_size; i-->0;) {
		data::text.replace(
				{ data::pos_cursor.x - 1, data::pos_cursor.y - 1 }, ' ');
			right_pos();
		}
		break;
	case 10: // enter
		data::text.new_ln(data::pos_cursor.y);
		down_pos();
		break;
	default:
		if (!data::text[data::pos_cursor.y - 1].empty())
			data::text.replace(
					{ data::pos_cursor.x - 1, data::pos_cursor.y - 1 }, ch );
		right_pos();

		// keycode test
		/*func::clear_all();
		term::format(term::Format::reset);
		std::cout << ch;
		sleep(1);*/

		break;
	}
}

void term_read(const char* chs)
{
	/*
	 * считать посимвольно с тек. позиц. курсора до пробела
	*/

	//struc::Coord
}

} // funcs
} // _e

#endif // _E_FUNCS_CPP
