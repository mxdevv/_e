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

	struc::Color_ch& cur_col_ch = data::text[0][0];
	term::fg_color(cur_col_ch.fg);
	term::bg_color(cur_col_ch.bg);
	
	for(int i = data::shift.current();
			i < data::text_location.second.y + data::shift && i < data::text.size();
			i++)
	{
		term::move_cursor(1, i + 1 - data::shift);
		for(int j = 0; j < data::text[i].size(); j++) {
			// lazy coloring
			if (   data::text[i][j].fg != cur_col_ch.fg
					|| data::text[i][j].bg != cur_col_ch.bg)
			{
				cur_col_ch = data::text[i][j];
				term::fg_color(cur_col_ch.fg);
				term::bg_color(cur_col_ch.bg);
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
			else
				data::text.back().push_back( { ch } );
		}
	} else {
		fputs(lang::dont_have_file.c_str(), stdout);
		putc('\n', stdout);
	}

	data::ifs.close();
}

void highlight_keywords()
{
	std::vector<int> v;
	for(int i = 0; i < highlight::keywords.size(); i++)
	{
		for(int j = 0; j < data::text.size(); j++)
		{
			v = alg::substr(highlight::keywords[i].word, data::text[j]);
			for(int k = 0; k < v.size(); k++)
			for(int w = strlen(highlight::keywords[i].word); w > 0; w--) {
				data::text[j][v[k] - w + 1].bg = highlight::keywords[i].bg;
				data::text[j][v[k] - w + 1].fg = highlight::keywords[i].fg;
			}
		}
	}
}

void highlight_operators()
{
	std::vector<int> v;
	for(int i = 0; i < highlight::operators.size(); i++)
	{
		for(int j = 0; j < data::text.size(); j++)
		{
			v = alg::substr(highlight::operators[i].operat, data::text[j]);
			for(int k = 0; k < v.size(); k++)
			for(int w = strlen(highlight::operators[i].operat); w > 0; w--) {
				data::text[j][v[k] - w + 1].bg = highlight::operators[i].bg;
				data::text[j][v[k] - w + 1].fg = highlight::operators[i].fg;
			}
		}
	}
}

void update_highlight()
{
	highlight_keywords();
	highlight_operators();
}

void help()
{
	fputs(lang::help.c_str(), stdout);
	putc('\n', stdout);
}

void correct_x()
{
	if (data::text[data::pos_cursor.y - 1].size() < data::pos_cursor.x)
		data::pos_cursor.x = data::text[data::pos_cursor.y - 1].size();
}

void up_pos()
{
	if (data::pos_cursor.y > 1)
		data::pos_cursor.y--;
	correct_x();
	if (data::pos_cursor.y <= data::shift.current())
		data::shift--;
}

void down_pos()
{
	if (data::text.size() - 1 > data::pos_cursor.y)
		data::pos_cursor.y++;
	correct_x();
	if (data::pos_cursor.y + 6 > data::text_location.second.y + data::shift)
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

inline void terminate()
{
	data::interactive.final();
}

void add(int ch)
{
	switch(ch) {
	case 127: // backspace
		data::text[data::pos_cursor.y - 1].erase(
				data::text[data::pos_cursor.y - 1].begin()
				+ data::pos_cursor.x - 2);
		left_pos();
		break;
	case 9: // tab
		for(int i = 2; i-->0;) {
			data::text[data::pos_cursor.y - 1].insert(
					data::text[data::pos_cursor.y - 1].begin()
					+ data::pos_cursor.x - 1, { ' ' } );
			right_pos();
		}
		break;
	case 10: // enter // don't work?
		//data::text.insert(
		//		data::text.begin() + data::pos_cursor.y,
		//		{ } );
		break;
	default:
		data::text[data::pos_cursor.y - 1].insert(
				data::text[data::pos_cursor.y - 1].begin()
				+ data::pos_cursor.x - 1, { ch } );
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
		data::text[data::pos_cursor.y - 1].erase(
				data::text[data::pos_cursor.y - 1].begin()
				+ data::pos_cursor.x - 2);
		left_pos();
		break;
	case 9: // tab
		for(int i = 2; i-->0;) {
			data::text[data::pos_cursor.y - 1]
				[data::pos_cursor.x - 1] = { ' ' };
			right_pos();
		}
		break;
	case 10: // enter // don't work?
		//data::text.insert(
		//		data::text.begin() + data::pos_cursor.y,
		//		{ } );
		break;
	default:
		data::text[data::pos_cursor.y - 1]
			[data::pos_cursor.x - 1].ch = ch;
		right_pos();

		// keycode test
		/*func::clear_all();
		term::format(term::Format::reset);
		std::cout << ch;
		sleep(1);*/

		break;
	}
}

} // funcs
} // _e

#endif // _E_FUNCS_CPP
