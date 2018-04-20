#ifndef _E_LANG_CPP
#define _E_LANG_CPP

namespace _e {
namespace lang {

constexpr clas::utf8_string no_arguments( "Аргументов нет. Завершение." );
constexpr clas::utf8_string too_arguments( "Слишком много аргументов." );

constexpr clas::utf8_string help(
"Использовать: _e [ФАЙЛ НА ОТКРЫТИЕ] [АРГУМЕНТЫ]\n"
"_e - терминальный редактор текста адаптированный под код.\n"
"\n"
"Аргументы:\n"
"  -h, help                             вызвать справку." );

constexpr clas::utf8_string mode_view( "Просмотр" );
constexpr clas::utf8_string mode_edit( "Вставка" );

} // lang
} // _e

#endif // _E_LANG_CPP
