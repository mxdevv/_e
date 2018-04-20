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

	inline void _set(T t)
	{
		_previous = _current;
		_current = t;
	}
public:
	Store() = default;

	Store(T previous, T current)
		: _previous(previous), _current(current) { }

	inline void operator = (T t)
		{ _set(t); }

	inline void operator ++ (auto)
		{ _set(_current + 1); }

	inline void operator -- (auto)
		{ _set(_current - 1); }

	inline const T& previous() const
		{ return _previous; }

	inline const T& current() const
		{ return _current; }

	template<typename U>
		friend U operator + (auto u, Store<U> store);
	template<typename U>
		friend U operator + (Store<U> store, auto u);
	template<typename U>
		friend U operator - (auto u, Store<U> store);
	template<typename U>
		friend U operator - (Store<U> store, auto u);
};

template<typename T>
T operator + (auto t, Store<T> store)
	{ return t + store._current; }

template<typename T>
T operator + (Store<T> store, auto t)
	{ return t + store._current; }

template<typename T>
T operator - (auto t, Store<T> store)
	{ return t - store._current; }

template<typename T>
T operator - (Store<T> store, auto t)
	{ return t - store._current; }

} // pattern
} // _e

#endif // _E_PATTERN_CPP
