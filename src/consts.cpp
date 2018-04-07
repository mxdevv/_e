#ifndef _E_CONSTS_CPP
#define _E_CONSTS_CPP

namespace _e {

namespace esc {

enum format {
	reset = 0, bright, dim, underscope, blink, reverse, hidden
};

enum struct fg_color {
	black = 30, red, green, yellow, blue, magenta, cyan, white
};

enum struct bg_color {
	black = 40, red, green, yellow, blue, magenta, cyan, white
};

} // esc

} // _e

#endif
