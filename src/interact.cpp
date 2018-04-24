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
void flash_insert_f();
void insert_f();
void flash_enter_f();
void enter_f();

pattern::Flash hello(flash_hello_f, hello_f);
pattern::Flash view(flash_view_f, view_f);
pattern::Flash edit(flash_edit_f, edit_f);
pattern::Flash insert(flash_insert_f, insert_f);
pattern::Flash enter(flash_enter_f, enter_f);

void flash_view_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_view.c_str();
	term::move_cursor(2, data::term_size.y);
	term::fg_color(term::Fg_color::white);
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
						for(int i=10;i-->0;) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i=10;i-->0;) func::down_pos(); break;
			}
		}
	} else switch(c) {
		case 'e': data::interactive(edit); break;
		case 'i': data::interactive(insert); break;
		case ':': 
			flash_enter_f();
			enter_f();
			flash_view_f(); // чувствую, что это надо переписать
			break;
	}

	term::hide_cursor();	
	func::redraw_text_view();
	func::place_cursor();
	term::show_cursor();
}

void flash_edit_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_edit.c_str();
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
						for(int i=10;i-->0;) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i=10;i-->0;) func::down_pos(); break;
			}
		} else data::interactive(view); // если только esc
	} else
		func::add(c);

	term::hide_cursor();	
	func::redraw_text_view();
	func::place_cursor();
	term::show_cursor();
}

void flash_insert_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_insert.c_str();
	term::move_cursor(2, data::term_size.y);
	term::format(term::Format::bright);
	term::fg_color(term::Fg_color::red);
	fputs(data::status_bar.current(), stdout);
	term::format(term::Format::reset);
	func::clear_previous_status();
}

void insert_f()
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
						for(int i=10;i-->0;) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i=10;i-->0;) func::down_pos(); break;
			}
		} else data::interactive(view); // если только esc
	} else
		func::insert(c);

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
	term::format(term::Format::reset);
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
		"_e - terminal editor." ,
		"e - edit, i - insert," ,
		"v - visual, esc - view," ,
		": - command mode," ,
		"c - copy, p - paste." ,
		"Press any key to continue."
	};
	int y = (data::term_size.y - message.size()) / 2;
	for(int i = 0; i < message.size(); i++)
	{
		term::move_cursor(
				data::term_size.x / 2 - strlen(message[i]) / 2, y + i);
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
