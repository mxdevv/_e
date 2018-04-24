#ifndef _E_STRUC_CPP
#define _E_STRUC_CPP

namespace _e {
namespace struc {

struct Coord { int x, y; };

struct Location { Coord first, second; };

/*struct Colors { 
	term::Bg_color bg_col = term::Bg_color::black;
	term::Fg_color fg_col = term::Fg_color::white;
};*/

struct Color_ch {
	char ch;
	term::Bg_color bg = term::Bg_color::black;
	term::Fg_color fg = term::Fg_color::white;
};

} // structs
} // _e

#endif // _E_STRUC_CPP
