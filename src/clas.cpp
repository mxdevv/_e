#ifndef _E_CLAS_CPP
#define _E_CLAS_CPP

namespace _e {
namespace clas {

class utf8_string {
	const char* _cstr;
	size_t _size;
public:
	constexpr utf8_string(const char* cstr)
		: _cstr(cstr), _size(alg::utf8_strlen(cstr))
		{ }

	inline void operator = (const char* cstr)
	{
		_cstr = cstr;
		_size = alg::utf8_strlen(_cstr);
	}

	inline size_t size() const
		{ return _size; }

	inline const char* cstr() const
		{ return _cstr; }

	inline const char operator [] (size_t n) const
		{ return _cstr[n]; }
};

} // clas
} // _e

#endif // _E_CLAS_CPP
