#ifndef _E_DATA_CPP
#define _E_DATA_CPP

namespace _e {
namespace data {

std::ofstream ofs;
std::ifstream ifs;

pattern::Interactive<pattern::Flash> interactive;

                               char* file_name;
                          clas::Text text;
         pattern::Store<const char*> status_bar (" ");

                        struc::Coord pos_cursor { 1, 1 };
                 pattern::Store<int> shift      (0);

                        struc::Coord term_size;
                     struc::Location text_location;

///////////////////////////////////////////////////////////////////////////////

const size_t page_step = 20;
const size_t tab_size  = 2;
const size_t down_pos_limit = 6;
const size_t up_pos_limit = 6;

} // data
} // _e

#endif // _E_DATA_CPP
