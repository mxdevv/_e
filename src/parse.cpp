#ifndef _E_PARSE_CPP
#define _E_PARSE_CPP

namespace _e {
namespace parse {

constexpr bool is_alpha(char ch) {
	return ((ch >= 'a' && ch <= 'z')
			||  (ch >= 'A' && ch <= 'Z'));
}

constexpr bool is_digit(char ch)
	{ return (ch >= '0' && ch <= '9'); }

constexpr bool is_alpha_or_digit(char ch) {
	return ((ch >= 'a' && ch <= 'z')
			||  (ch >= 'A' && ch <= 'Z')
			||  (ch >= '0' && ch <= '9'));
}

constexpr bool is_literal(char ch) {
	return ((ch >= 'a' && ch <= 'z')
			||  (ch >= 'A' && ch <= 'Z')
			||  (ch == '_')
			||  (ch >= '0' && ch <= '9'));
}

} // parse
} // _e

#endif // _E_PARSE_CPP
