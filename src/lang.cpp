#ifndef _E_LANG_CPP
#define _E_LANG_CPP

namespace _e {
namespace lang {

constexpr char no_arguments[] =
"Аргументов нет. Завершение.";

constexpr char too_arguments[] =
"Слишком много аргументов.";

constexpr char help[] =
"Использовать: _e [ФАЙЛ НА ОТКРЫТИЕ] [АРГУМЕНТЫ]\n\
_e - терминальный редактор текста адаптированный под код.\n\
\n\
Аргументы:\n\
  -h, help                             вызвать справку."
;

} // lang
} // _e

#endif
