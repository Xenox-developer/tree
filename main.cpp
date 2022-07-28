#include "bin_tree.hpp"
#include "worker.hpp"
#include "menu.hpp"

int main() {
	// Cоздаем дерево и вызываем первую функцию меню.
	bin_tree<worker> my_tree;
	build_menu(my_tree);
	return 0;
}