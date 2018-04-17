#ifndef _E_INTERACT_CPP
#define _E_INTERACT_CPP

namespace _e {
namespace interact {

int c = 0;

void flash_hello_f();
void hello_f();
void flash_view_f();
void view_f();
void flash_edit_f();
void edit_f();

pattern::Flash hello(flash_hello_f, hello_f);
pattern::Flash view(flash_view_f, view_f);
pattern::Flash edit(flash_edit_f, edit_f);

void flash_view_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_view;
	term::move_cursor(2, data::term_size.y);
	term::format(term::format::bright);
	fputs(data::status_bar[data::status_bar.current], stdout);
	term::format(term::format::reset);
	func::clear_previous_status();
}

void view_f()
{
	c = getchar();
	if (c == 27) /* esc */ {
		c = getchar();
		if (c == '[') {
			c = getchar();
			switch(c) {
				case 'A': func::up_pos(); break; // up
				case 'B': func::down_pos(); break; // down
				case 'C': func::right_pos(); break; // right
				case 'D': func::left_pos(); break; // left
			}
		}
	} else switch(c) {
		case 'q': func::terminate(); break;
		case 'e': data::interactive(edit); break;
	}

	term::hide_cursor();	
	func::redraw_lines();
	func::place_cursor();
	term::show_cursor();
}

void flash_edit_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_edit;
	term::move_cursor(2, data::term_size.y);
	term::format(term::format::bright);
	term::fg_color(term::fg_color::magenta);
	fputs(data::status_bar[data::status_bar.current], stdout);
	term::format(term::format::reset);
	func::clear_previous_status();
}

void edit_f()
{
	c = getchar();
	if (c == 27) /* esc */ {
		c = getchar();
		if (c == '[') {
			c = getchar();
			switch(c) {
				case 'A': func::up_pos(); break; // up
				case 'B': func::down_pos(); break; // down
				case 'C': func::right_pos(); break; // right
				case 'D': func::left_pos(); break; // left
			}
		} else data::interactive(view);
	} else switch(c) {
		case 'q': func::terminate(); break;
	}

	term::hide_cursor();	
	func::redraw_lines();
	func::place_cursor();
	term::show_cursor();
}

void flash_hello_f()
	{ }

void hello_f()
{
	term::hide_cursor();
	func::redraw_lines();
	term::fg_color(term::fg_color::magenta);

	std::array<const char*, 5> message {
		"_e - терминальный редактор." ,
		"e(edit) - вставка, i(insert) - замена," ,
		"v(visual) - выделение, esc - просмотр," ,
		"c(copy) - копировать, p(paste) - вставить" ,
		"Нажмите любую клавишу, чтобы продолжить."
	};
	int y = (data::term_size.y - message.size()) / 2;
	for(int i = 0; i < message.size(); i++)
	{
		term::move_cursor(
				data::term_size.x / 2 - alg::utf8_strlen(message[i]) / 2, y + i);
		fputs(message[i], stdout);
	}

	term::format(term::format::reset);
	getchar();

	term::clr_scr();

	data::interactive(view);
}

} // interact
} // _e

#endif // _E_INTERACT_CPP
