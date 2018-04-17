#ifndef _E_DATA_CPP
#define _E_DATA_CPP

namespace _e {
namespace data {

std::ofstream ofs;
std::ifstream ifs;

char* file_name;
std::vector<std::vector<char>> lines;
pattern::Store<const char*> status_bar(" ", " ");
structs::Coord pos { 1, 1 };
pattern::Store<int> shift(0, 0);
structs::Coord term_size;
structs::Coord text_view_size;

pattern::Interactive<pattern::Flash> interactive;

} // data
} // _e

#endif // _E_DATA_CPP
