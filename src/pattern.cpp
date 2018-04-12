#ifndef _E_PATTERN_CPP
#define _E_PATTERN_CPP

namespace _e {
namespace pattern {

class Interactive {
	void (*func)();
	bool is_run = 0;
public:
	void operator () (auto f)
	{
		func = f;
		if (!is_run) {
			is_run = 1;
			while(is_run)
				func();
		}
	}

	inline void final()
	{
		is_run = 0;
	}
};

// не дописано, в процессе
template<typename T>
class Store {
	T current;
public:
	T previous;

	void operator = (T t)
	{ 
		previous = current;
		current = t;
	}
};

} // pattern
} // _e

#endif
