#ifndef _E_KEYBIND_CPP
#define _E_KEYBIND_CPP

namespace _e {
namespace keybind {

void nothing() { }

template<void (*f)() = nothing>
class Keybind {
public:
	void operator () () {
		f(); }
};

Keybind<func::up_pos> up_arrow;
Keybind<func::down_pos> down_arrow;
Keybind<func::left_pos> left_arrow;
Keybind<func::right_pos> right_arrow;
Keybind<func::terminate> q;

} // keybind
} // _e

#endif
