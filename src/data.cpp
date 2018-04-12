#ifndef _E_DATA_CPP
#define _E_DATA_CPP

namespace _e {
namespace data {

std::ofstream ofs;
std::ifstream ifs;

char* file_name;
std::vector<std::vector<char>> lines;
const char* status;
structs::Coord pos { 1, 1 };
structs::Coord term_size;;

pattern::Interactive interactive;

} // data
} // _e

#endif
