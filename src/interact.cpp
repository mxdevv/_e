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
void flash_enter_f();
void enter_f();

pattern::Flash hello(flash_hello_f, hello_f);
pattern::Flash view(flash_view_f, view_f);
pattern::Flash edit(flash_edit_f, edit_f);
pattern::Flash enter(flash_enter_f, enter_f);

void flash_view_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_view.cstr();
	term::move_cursor(2, data::term_size.y);
	term::format(term::Format::bright);
	fputs(data::status_bar.current(), stdout);
	term::format(term::Format::reset);
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
				case '5':
					c = getchar();
					if (c == '~') // pg_up
						for(int i=5; i>0; i--) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i=5; i>0; i--) func::down_pos(); break;
			}
		}
	} else switch(c) {
		case 'e': data::interactive(edit); break;
		case ':': data::interactive(enter); break;
	}

	term::hide_cursor();	
	func::redraw_text_view();
	func::place_cursor();
	term::show_cursor();
}

void flash_edit_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_edit.cstr();
	term::move_cursor(2, data::term_size.y);
	term::format(term::Format::bright);
	term::fg_color(term::Fg_color::magenta);
	fputs(data::status_bar.current(), stdout);
	term::format(term::Format::reset);
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
				case '5':
					c = getchar();
					if (c == '~') // pg_up
						for(int i=5; i>0; i--) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i=5; i>0; i--) func::down_pos(); break;
			}
		} else data::interactive(view); // если только esc
	} else switch(c) {
		case ':': data::interactive(enter); break;
	}

	term::hide_cursor();	
	func::redraw_text_view();
	func::place_cursor();
	term::show_cursor();
}

void flash_enter_f()
{
	term::hide_cursor();
	func::clear_status();
	term::move_cursor(2, data::term_size.y);
	putc(':', stdout);
}

void enter_f()
{
	term::default_mode();
	term::move_cursor(3, data::term_size.y);
	term::show_cursor();
	c = getchar();

	if (c == 'q') func::terminate();

	term::hide_cursor();	
	func::place_cursor();
	term::show_cursor();
	term::nocanon_mode();
}

void flash_hello_f()
	{ }

void hello_f()
{
	term::hide_cursor();
	func::redraw_text_view();
	term::fg_color(term::Fg_color::magenta);

	std::array<const char*, 6> message {
		"_e - терминальный редактор." ,
		"e(edit) - вставка, i(insert) - замена," ,
		"v(visual) - выделение, esc - просмотр," ,
		": - командный режим," ,
		"c(copy) - копировать, p(paste) - вставить." ,
		"Нажмите любую клавишу, чтобы продолжить."
	};
	int y = (data::term_size.y - message.size()) / 2;
	for(int i = 0; i < message.size(); i++)
	{
		term::move_cursor(
				data::term_size.x / 2 - alg::utf8_strlen(message[i]) / 2, y + i);
		fputs(message[i], stdout);
	}

	term::format(term::Format::reset);
	getchar();

	func::clear_all();
	func::redraw_text_view();

	data::interactive(view);
}

} // interact
} // _e

#endif // _E_INTERACT_CPP
