#ifndef _E_DATA_CPP
#define _E_DATA_CPP

namespace _e {
namespace data {

std::ofstream ofs;
std::ifstream ifs;

pattern::Interactive<pattern::Flash> interactive;

char* file_name;

//std::vector<std::vector<struc::Color_ch>> text;
clas::Text text;

struc::Coord pos_cursor { 1, 1 };
pattern::Store<int> shift(0, 0);

struc::Coord term_size;
struc::Location text_location;

pattern::Store<const char*> status_bar(" ", " ");

} // data
} // _e

#endif // _E_DATA_CPP
