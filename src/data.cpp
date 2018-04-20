#ifndef _E_DATA_CPP
#define _E_DATA_CPP

namespace _e {
namespace data {

std::ofstream ofs;
std::ifstream ifs;

pattern::Interactive<pattern::Flash> interactive;

char* file_name;

std::vector<std::vector<char>> text;
std::vector<std::vector<struc::Cols>> highlight;

//pattern::Store< std::vector<std::vector<char>> > gbuf_text;
//pattern::Store< std::vector<std::vector<struc::Cols>> > gbuf_highlight;

pattern::Store<const char*> status_bar(" ", " ");

struc::Coord pos { 1, 1 };
pattern::Store<int> shift(0, 0);

struc::Coord term_size;
struc::Coord text_view_size;

} // data
} // _e

#endif // _E_DATA_CPP
