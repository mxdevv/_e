#ifndef _E_FUNCS_CPP
#define _E_FUNCS_CPP

namespace _e {
namespace func {

void clear_text_view()
{
	term::move_cursor(1, 1);
	for(int i = 0; i < data::text_view_size.y; i++)
	for(int j = 0; j < data::text_view_size.x; j++)
		putc(' ', stdout);
}

void clear_all()
{
	term::move_cursor(1, 1);
	for(int i = 0; i < data::term_size.y; i++)
	for(int j = 0; j < data::term_size.x; j++)
		putc(' ', stdout);
}

void redraw_text_view()
{
	clear_text_view();
	for(int i = data::shift.current(); i < data::text_view_size.y + data::shift
			&& i < data::text.size(); i++) {
		term::move_cursor(1, i + 1 - data::shift);
		for(int j = 0; j < data::text[i].size(); j++) {
			
			//
			term::bg_color(data::highlight[i][j].bg_col);
			term::fg_color(data::highlight[i][j].fg_col);
			//

			putc(data::text[i][j], stdout);
		}
	}
	for(int i = data::text.size() - data::shift;
			i <= data::text_view_size.y; i++)
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
			2 + alg::utf8_strlen(data::status_bar.current()),
			data::term_size.y);
	for(int i = alg::utf8_strlen(data::status_bar.previous())
			- alg::utf8_strlen(data::status_bar.current());
			i > 0; i--)
		putc(' ', stdout);
}

void place_cursor()
{
	term::move_cursor(data::pos.x,
			data::pos.y - data::shift);
}

void open_or_create()
{
	data::ifs.open(data::file_name);
	
	if (data::ifs.is_open()) {
		data::text.push_back( { } );

		char ch;
		while(data::ifs) {
			data::ifs.get(ch);
			if (ch == '\n')
				data::text.push_back( { } );
			else
				data::text.back().push_back(ch);
		}
	} else {
		fputs("Файла нет.\n", stdout);
	}

	data::ifs.close();
}

inline void init_highlight()
{
	data::highlight.resize(data::text.size());
	for(int i = 0; i < data::text.size(); i++)
		data::highlight[i].resize(data::text[i].size());
}

void highlight_keywords()
{
	std::vector<int> v;
	for(int i = 0; i < highlight::keywords.size(); i++)
	{
		for(int j = 0; j < data::text.size(); j++)
		{
			v = alg::substr(highlight::keywords[i], data::text[j]);
			for(int k = 0; k < v.size(); k++)
			for(int w = alg::utf8_strlen(highlight::keywords[i]); w > 0; w--) {
				data::highlight[j][v[k] - w + 1].bg_col = term::Bg_color::yellow;
				data::highlight[j][v[k] - w + 1].fg_col = term::Fg_color::black;
			}
		}
	}
}

void gen_highlight()
{
	init_highlight();
	highlight_keywords();
}

void update_highlight()
{
	highlight_keywords();
}

void help()
{
	fputs(lang::help.cstr(), stdout);
	putc('\n', stdout);
}

void correct_x()
{
	if (data::text[data::pos.y - 1].size() < data::pos.x)
		data::pos.x = data::text[data::pos.y - 1].size();
}

void up_pos()
{
	if (data::pos.y > 1)
		data::pos.y--;
	correct_x();
	if (data::pos.y <= data::shift.current())
		data::shift--;
}

void down_pos()
{
	if (data::text.size() - 1 > data::pos.y)
		data::pos.y++;
	correct_x();
	if (data::pos.y + 6 > data::text_view_size.y + data::shift)
		data::shift++;
}

void left_pos()
{
	if (data::pos.x > 1)
		data::pos.x--;
}

void right_pos()
{
	if (data::text[data::pos.y - 1].size() > data::pos.x)
		data::pos.x++;
}

inline void terminate()
{
	data::interactive.final();
}

} // funcs
} // _e

#endif // _E_FUNCS_CPP
