#ifndef _E_CLAS_CPP
#define _E_CLAS_CPP

namespace _e {
namespace clas {

/*class Text {
public:
	using value_type = std::vector<struc::Color_ch>;

private:
	std::vector<value_type> data;

public:
	inline auto back()
		{ return data.back(); }

	inline auto begin()
		{ return data.begin(); }

	inline auto& operator [] (size_t n)
		{ return data[n]; }

	inline size_t size()
		{ return data.size(); }

	inline void push_back(std::vector<struc::Color_ch> val)
		{ data.push_back(val); }
};*/

class Text : public std::vector<std::vector<struc::Color_ch>> { 
public:
	inline void new_ln()
		{ this->push_back( { } ); }
};

} // clas
} // _e

#endif // _E_CLAS_CPP
