#ifndef _E_FUNCS_CPP
#define _E_FUNCS_CPP

#include "data.cpp"

namespace _e {
namespace func {

void getch() { };
void redraw() { };

void cat()
{
	for(auto& v : data::lines) {
		for(auto& ch : v)
			std::cout << ch;
		std::cout << '\n';
	}
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
		
		// после удалить //
		/**/esc::fg_color(esc::fg_color::yellow);
		/**/esc::format(esc::format::bright);
		/**/cat();
		/**/esc::format(esc::format::reset);
		// ------------- //
	} else {
		std::cout << "Файла нет.\n";
	}

	data::ifs.close();
}

void help()
{
	std::cout << lang::help << '\n';
}

} // funcs
} // _e

#endif
