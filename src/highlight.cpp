#ifndef _E_HIGHLIGHT_CPP
#define _E_HIGHLIGHT_CPP

namespace _e {
namespace highlight {

struct Keyword { const char* word; struc::Colors colors; };
struct Operator { const char* word; struc::Colors colors; };

std::vector<Keyword> keywords {
	{ "using",     { term::Bg_color::black, term::Fg_color::yellow } },
	{ "namespace", { term::Bg_color::black, term::Fg_color::yellow } },
	{ "return",    { term::Bg_color::black, term::Fg_color::yellow } },
	{ "else",      { term::Bg_color::black, term::Fg_color::yellow } },
	{ "if",        { term::Bg_color::black, term::Fg_color::yellow } },
	{ "while",     { term::Bg_color::black, term::Fg_color::yellow } },
	{ "for",       { term::Bg_color::black, term::Fg_color::yellow } },
	{ "default",   { term::Bg_color::black, term::Fg_color::yellow } },
	{ "break",     { term::Bg_color::black, term::Fg_color::yellow } },
	{ "switch",    { term::Bg_color::black, term::Fg_color::yellow } },
	{ "case",      { term::Bg_color::black, term::Fg_color::yellow } },
	{ "inline",    { term::Bg_color::black, term::Fg_color::yellow } },
	{ "const",     { term::Bg_color::black, term::Fg_color::yellow } },
	{ "constexpr", { term::Bg_color::black, term::Fg_color::yellow } },
	{ "mutable",   { term::Bg_color::black, term::Fg_color::yellow } },
	{ "template",  { term::Bg_color::black, term::Fg_color::yellow } },
	{ "typename",  { term::Bg_color::black, term::Fg_color::yellow } },
	{ "goto",      { term::Bg_color::black, term::Fg_color::yellow } },
	
	{ "void",      { term::Bg_color::black, term::Fg_color::green } },
	{ "char",      { term::Bg_color::black, term::Fg_color::green } },
	{ "int",       { term::Bg_color::black, term::Fg_color::green } },
	{ "float",     { term::Bg_color::black, term::Fg_color::green } },
	{ "double",    { term::Bg_color::black, term::Fg_color::green } },
	{ "size_t",    { term::Bg_color::black, term::Fg_color::green } },
	{ "auto",      { term::Bg_color::black, term::Fg_color::green } },
	
	{ "main",      { term::Bg_color::black, term::Fg_color::magenta } },
	{ "cout",      { term::Bg_color::black, term::Fg_color::magenta } },
	{ "cin",       { term::Bg_color::black, term::Fg_color::magenta } },
	{ "std",       { term::Bg_color::black, term::Fg_color::magenta } },

	{ "#include",  { term::Bg_color::black, term::Fg_color::cyan } },
	{ "#define",   { term::Bg_color::black, term::Fg_color::cyan } },
	{ "#else",     { term::Bg_color::black, term::Fg_color::cyan } },
	{ "#ifndef",   { term::Bg_color::black, term::Fg_color::cyan } },
	{ "#ifdef",    { term::Bg_color::black, term::Fg_color::cyan } },
	{ "#endif",    { term::Bg_color::black, term::Fg_color::cyan } },
};

std::vector<Operator> operators {
	{ "<", { term::Bg_color::black, term::Fg_color::red } },
	{ ">", { term::Bg_color::black, term::Fg_color::red } },
	{ "[", { term::Bg_color::black, term::Fg_color::red } },
	{ "]", { term::Bg_color::black, term::Fg_color::red } },
	{ "(", { term::Bg_color::black, term::Fg_color::red } },
	{ ")", { term::Bg_color::black, term::Fg_color::red } },
	{ "=", { term::Bg_color::black, term::Fg_color::red } },
	{ ":", { term::Bg_color::black, term::Fg_color::red } },
	{ "!", { term::Bg_color::black, term::Fg_color::red } },
	{ "*", { term::Bg_color::black, term::Fg_color::red } },
	{ "/", { term::Bg_color::black, term::Fg_color::red } },
	{ "+", { term::Bg_color::black, term::Fg_color::red } },
	{ "-", { term::Bg_color::black, term::Fg_color::red } },
	{ ",", { term::Bg_color::black, term::Fg_color::red } },
	{ ".", { term::Bg_color::black, term::Fg_color::red } },
	{ ";", { term::Bg_color::black, term::Fg_color::red } },
};

void clear()
{
	for(auto& line : data::text)
	for(auto& cl_ch : line)
		cl_ch.colors = { term::Bg_color::black, term::Fg_color::white };
}

void keywords_f()
{
	std::vector<int> v;
	for(auto& keyword : highlight::keywords)
	for(auto& line : data::text) {
		v = alg::substr(keyword.word, line);
		for(auto& el : v)
		if (!parse::is_literal(line[el - strlen(keyword.word)].ch)
				&& !parse::is_literal(line[el + 1].ch))
			for(int i = strlen(keyword.word); i --> 0;)
				line[el - i].colors = keyword.colors;
	}
}

void operators_f()
{
	std::vector<int> v;
	for(auto& operat : highlight::operators)
	for(auto& line : data::text) {
		v = alg::substr(operat.word, line);
		for(auto& el : v)
		for(size_t i = strlen(operat.word); i --> 0;)
			line[el - i].colors = operat.colors;
	}
}

void update()
{
	clear();
	keywords_f();
	operators_f();
}

} // highlight
} // _e

#endif // _E_HIGHLIGHT_CPP
