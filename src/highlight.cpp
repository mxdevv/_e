#ifndef _E_HIGHLIGHT_CPP
#define _E_HIGHLIGHT_CPP

namespace _e {
namespace highlight {

struct Keyword { const char* word; term::Bg_color bg; term::Fg_color fg; };
struct Operator { const char* operat; term::Bg_color bg; term::Fg_color fg; };

std::vector<Keyword> keywords {
	{ "hello", term::Bg_color::black, term::Fg_color::green },
	{ "end", term::Bg_color::black, term::Fg_color::blue },
	{ "int", term::Bg_color::black, term::Fg_color::yellow },
	{ "cout", term::Bg_color::black, term::Fg_color::red }
};

std::vector<Operator> operators {
	{ "\"", term::Bg_color::black, term::Fg_color::red }
};

} // highlight
} // _e

#endif // _E_HIGHLIGHT_CPP
