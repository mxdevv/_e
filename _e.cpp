#include <cstring>
#include <fstream>
#include <vector>
#include <array>
#include <termios.h>
#include <unistd.h>

#include "src/func.h"

#include "src/alg.cpp"
#include "src/lang.cpp"
#include "src/structs.cpp"
#include "src/pattern.cpp"
#include "src/term.cpp"
#include "src/func.cpp"
#include "src/data.cpp"
#include "src/interact.cpp"
#include "src/keybind.cpp"

using namespace _e;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		fputs("_e: ", stdout);
		fputs(lang::no_arguments, stdout);
		putc('\n', stdout);
		return -1;
	}

	for(int i = 1; i < argc; i++)
	if (argv[i][0] == '-') {
		for(size_t j = 1, len = strlen(argv[i]); j < len; j++)
		switch(argv[i][j])
		{
			case 'h': func::help(); return 0;
			default:
				data::file_name = argv[i];
				func::open_or_create();
				break;
		}
	} else
		switch(alg::hash(argv[i]))
		{
			case alg::hash("help"): func::help(); return 0;
			default:
				data::file_name = argv[i];
				func::open_or_create();
				break;
		}
	
	term::init();
	term::nocanon_mode();
	term::get_term_size(data::term_size.x, data::term_size.y);
	data::text_view_size.x = data::term_size.x;
	data::text_view_size.y = data::term_size.y - 1;
	term::clr_scr();

	data::interactive(interact::hello);
	
	term::default_mode();
	term::clr_scr();
	term::move_cursor(1, 1);
}
