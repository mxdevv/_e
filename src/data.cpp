#ifndef _E_DATA_CPP
#define _E_DATA_CPP

namespace _e {
namespace data {

std::ofstream ofs;
std::ifstream ifs;

std::vector<std::vector<char>> lines;
char* file_name;

bool color_mode = 1;

} // data
} // _e

#endif
