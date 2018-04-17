#ifndef _E_PATTERN_CPP
#define _E_PATTERN_CPP

namespace _e {
namespace pattern {

template<typename F> class Interactive;

class Flash {
	void (*_flash)();
	void (*_func)();
	bool _b = 0;
public:
	Flash(void (*flash)(), void (*func)())
		: _flash(flash), _func(func) { }

	void operator () ()
	{
		if (!_b) {
			_flash();
			_b = 1;
		}
		_func();
	}

	inline void reset()
	{
		_b = 0;
	}

	friend Interactive<Flash>;
};

template<typename F>
class Interactive {
	F _func;
	bool _is_run = 0;
public:
	void operator () (auto f)
	{
		_func = f;
		if (!_is_run) {
			_is_run = 1;
			while(_is_run)
				_func();
		}
	}

	inline void final()
	{
		_is_run = 0;
	}
};

template<>
class Interactive<Flash> {
	Flash* _flash = nullptr;
	bool _is_run = 0;
public:
	void operator () (Flash& fl)
	{
		if (_flash != nullptr) _flash->_b = 0;
		_flash = &fl;
		_flash->_flash();
		_flash->_b = 1;
		if (!_is_run) {
			_is_run = 1;
			while(_is_run)
				_flash->_func();
		}
	}

	inline void final()
	{
		_is_run = 0;
	}
};

template<typename T>
class Store {
	T _previous;
	T _current;
public:
	Store() { }

	Store(T previous, T current)
		: _previous(previous), _current(current) { }

	enum get { previous = 0, current };

	inline void operator = (T t)
	{ 
		_previous = _current;
		_current = t;
	}

	constexpr T& operator [] (get g)
	{
		if (g == previous) return _previous;
		if (g == current) return _current;
	}
};

} // pattern
} // _e

#endif // _E_PATTERN_CPP
