#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include "bin_tree.hpp"
#include "data_check.hpp"
#include "worker.hpp"

// Цикл первого меню (после завершения работы вызывает второе).
void build_menu(bin_tree<worker>&);

#endif // MENU_HPP