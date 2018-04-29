#include <cstring>
#include <fstream>
#include <vector>
#include <array>
#include <termios.h>
#include <unistd.h>

#include "src/config.h"

#include "src/func.h"

#include "src/parse.cpp"
#include "src/term.cpp"
#include "src/struc.cpp"
#include "src/clas.cpp"
#include "src/alg.cpp"
#include "src/lang.cpp"
#include "src/pattern.cpp"
#include "src/data.cpp"
#include "src/highlight.cpp"
#include "src/func.cpp"
#include "src/interact.cpp"

using namespace _e;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		fputs("_e: ", stdout);
		fputs(lang::no_arguments.c_str(), stdout);
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
				highlight::update();
				break;
		}
	} else
		switch(alg::hash(argv[i]))
		{
			case alg::hash("help"): func::help(); return 0;
			default:
				data::file_name = argv[i];
				func::open_or_create();
				highlight::update();
				break;
		}
	
	term::init();
	term::nocanon_mode();
	term::get_term_size(data::term_size.x, data::term_size.y);
	data::text_location.first.x = 1;
	data::text_location.first.y = 1;
	data::text_location.second.x = data::term_size.x;
	data::text_location.second.y = data::term_size.y - 1;
	func::clear_all();

	data::interactive(interact::hello);
	
	func::clear_all();
	term::format(term::Format::reset);
	term::move_cursor(1, 1);
	term::default_mode();
}
