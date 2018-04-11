#ifndef _E_DATA_CPP
#define _E_DATA_CPP

#include "pattern.cpp"
#include "func.cpp"

namespace _e {
namespace data {

std::ofstream ofs;
std::ifstream ifs;

char* file_name;
std::vector<std::vector<char>> lines;
structs::Coord pos { 1, 1 };
structs::Coord term_size { 80, 36 };

pattern::Interactive<func::getch, func::redraw> interactive;

} // data
} // _e

#endif
