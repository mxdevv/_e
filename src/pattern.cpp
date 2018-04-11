#ifndef _E_PATTERN_CPP
#define _E_PATTERN_CPP

namespace _e {
namespace pattern {

template<void (*prec_func)(), void (*post_func)()>
class Interactive {
	void (*func)();
	bool is_run = 0;
public:
	void operator () (auto f)
	{
		func = f;
		if (!is_run) {
			is_run = 1;
			while(is_run) {
				prec_func();
				func();
				post_func();
			}
		}
	}

	void final()
	{
		is_run = 0;
	}
};

} // pattern
} // _e

#endif
