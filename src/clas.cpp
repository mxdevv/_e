#ifndef _E_CLAS_CPP
#define _E_CLAS_CPP

namespace _e {
namespace clas {

class Text {
public:
	using value_type = std::vector<struc::Color_ch>;

private:
	std::vector<value_type> data;

public:
	inline auto begin()
		{ return data.begin(); }
	
	inline auto end()
		{ return data.end(); }

	inline auto& back()
		{ return data[data.size() - 1]; }

	inline size_t size()
		{ return data.size(); }

	inline bool empty()
		{ return data.size() == 0; }

	inline void resize(size_t size)
		{ data.resize(size); }

	inline value_type& operator [] (size_t i)
		{ return data[i]; }

	//////////////////////////////////////////////////////////////////////////

	inline void new_ln()
		{ data.push_back( { } ); }

	inline void new_ln(size_t i)
		{ data.insert(data.begin() + i, std::move(*new value_type()) ); }

	inline void remove(struc::Coord coord) {
		if (coord.x < 0) coord.x = 0; // -_- situation is don't controlling
		data[coord.y].erase(data[coord.y].begin() + coord.x);
	}

	inline void rm_ln(size_t y)
		{ data.erase(data.begin() + y); }

	inline void replace(struc::Coord coord, int ch)
		{ data[coord.y][coord.x].ch = ch; }

	inline void add(struc::Coord coord, int ch)
		{ data[coord.y].insert(data[coord.y].begin() + coord.x, { ch } ); }
};

} // clas
} // _e

#endif // _E_CLAS_CPP
