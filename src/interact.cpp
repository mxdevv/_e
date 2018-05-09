#ifndef _E_INTERACT_CPP
#define _E_INTERACT_CPP

namespace _e {
namespace interact {

int c = 0;
const char* cstr;
std::string str;

int save_y;
std::vector<std::vector<struc::Color_ch>>* buf;

void flash_hello_f();
void hello_f();
void flash_view_f();
void view_f();
void flash_edit_f();
void edit_f();
void flash_replace_f();
void replace_f();
void flash_visual_f();
void visual_f();
void flash_enter_f();
void enter_f();
void flash_find_f();
void find_f();

pattern::Flash hello(flash_hello_f, hello_f);
pattern::Flash view(flash_view_f, view_f);
pattern::Flash edit(flash_edit_f, edit_f);
pattern::Flash replace(flash_replace_f, replace_f);
pattern::Flash visual(flash_visual_f, visual_f);
pattern::Flash enter(flash_enter_f, enter_f);
pattern::Flash find(flash_find_f, find_f);

void flash_hello_f()
	{ }

void hello_f()
{
	term::hide_cursor();
	func::redraw_text_view();
	term::fg_color(term::Fg_color::magenta);

	std::array<const char*, 6> message {
		"_e - terminal editor." ,
		"e - edit, r - replace," ,
		"v - visual, esc - view," ,
		": - command mode, / - find," ,
		"c - copy, p - paste, d - delete." ,
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
						for(int i = data::page_step; i-->0;) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i = data::page_step ;i-->0;) func::down_pos(); break;
			}
		}
	} else switch(c) {
		case 'e': data::interactive(edit); break;
		case 'r': data::interactive(replace); break;
		case 'v': data::interactive(visual); break;
		case 'p': func::paste(data::pos_cursor.y, buf); break;
		case 'd':
			func::remove(data::pos_cursor.y - 1);
			func::up_pos();
			break;
		case ':': 
			flash_enter_f();
			enter_f();
			flash_view_f(); // чувствую, что это надо переписать
			break;
		case '/':
			flash_find_f();
			find_f();
			flash_view_f();
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
						for(int i = data::page_step; i-->0;) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i = data::page_step; i-->0;) func::down_pos(); break;
			}
		} else data::interactive(view); // если только esc
	} else {
		func::add(c);
		highlight::update();
	}

	term::hide_cursor();	
	func::redraw_text_view();
	func::place_cursor();
	term::show_cursor();
}

void flash_replace_f()
{
	term::hide_cursor();
	data::status_bar = lang::mode_replace.c_str();
	term::move_cursor(2, data::term_size.y);
	term::format(term::Format::bright);
	term::fg_color(term::Fg_color::red);
	fputs(data::status_bar.current(), stdout);
	term::format(term::Format::reset);
	func::clear_previous_status();
}

void replace_f()
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
	} else {
		func::insert(c);
		highlight::update();
	}

	term::hide_cursor();	
	func::redraw_text_view();
	func::place_cursor();
	term::show_cursor();
}

void flash_visual_f()
{
	save_y = data::pos_cursor.y;
	
	term::hide_cursor();
	data::status_bar = lang::mode_visual.c_str();
	term::move_cursor(2, data::term_size.y);
	term::format(term::Format::bright);
	term::fg_color(term::Fg_color::green);
	fputs(data::status_bar.current(), stdout);
	term::format(term::Format::reset);
	func::clear_previous_status();
}

void visual_f()
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
						for(int i = data::page_step; i-->0;) func::up_pos(); break;
				case '6':
					c = getchar();
					if (c == '~') // pg_down
						for(int i = data::page_step; i-->0;) func::down_pos(); break;
			}
		}	else { // esc
			data::interactive(view);
		}
	} else switch(c) {
		case 'c':
			buf = func::copy(save_y - 1, data::pos_cursor.y - 1);
			data::interactive(view);
			break;
		case 'd':
			func::remove(save_y - 1, data::pos_cursor.y - 1);
			data::interactive(view);
			break;
	}

	term::hide_cursor();	
	highlight::update();
	// этот участок кода отвратительный по смыслу в плане производительности
	for(int i = save_y - 1; i < data::pos_cursor.y; i++)
	for(int j = 0; j < data::text[i].size(); j++)
	{
		data::text[i][j].colors
			= { term::Bg_color::white, term::Fg_color::black };
	}

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
	std::cin >> str; // о боже нет, со временем отказаться от потоков!!!

	switch(alg::hash(str)) {
		case alg::hash("q"): func::terminate(); break;
		case alg::hash("w"): func::save(); break;
		case alg::hash("x"): func::save(); func::terminate(); break;
	}

	term::hide_cursor();	
	func::place_cursor();
	term::show_cursor();
	term::nocanon_mode();
}

void flash_find_f()
{
	term::hide_cursor();
	func::clear_status();
	term::move_cursor(2, data::term_size.y);
	term::format(term::Format::reset);
	putc('/', stdout);
}

void find_f()
{
	term::default_mode();
	term::move_cursor(3, data::term_size.y);
	term::show_cursor();
	std::cin >> str; // о боже нет, со временем отказаться от потоков!!!

	for(int i = data::pos_cursor.y - 1; i < data::text.size(); i++)
		for(auto& el : alg::substr(str.c_str(), data::text[i])) {
			if ((data::pos_cursor.y - 1 != i)
					| (el - str.size() > data::pos_cursor.x))
			{
				func::move_pos( { el + 2 - str.size(), i + 1 } );
				goto next;
			}
		}
next:

	term::hide_cursor();	
	func::place_cursor();
	term::show_cursor();
	term::nocanon_mode();
}

} // interact
} // _e

#endif // _E_INTERACT_CPP
