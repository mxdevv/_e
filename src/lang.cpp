#ifndef _E_LANG_CPP
#define _E_LANG_CPP

namespace _e {
namespace lang {

const std::string no_arguments( "No arguments. Exit." );
const std::string too_arguments( "Too many arguments." );
const std::string dont_have_file( "Don't have file." );

const std::string help(
"Use: _e [FILE TO OPEN] [ARGUMENTS]\n"
"_e - terminal text editor adapted to the code.\n"
"\n"
"Arguments:\n"
"  -h, help                             call help." );

const std::string mode_view( "View" );
const std::string mode_edit( "Edit" );
const std::string mode_replace( "Replace" );

} // lang
} // _e

#endif // _E_LANG_CPP
