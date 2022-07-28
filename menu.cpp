#include "menu.hpp"

#include <iostream>
#include <fstream>

// Функция считываем нажатие клавиши enter пользователем.
void read_enter() {
	// Так как нельзя запретить пользователю нажимать другие клавиши, как метод защиты счтываем
	// все что введет пользователь.
	std::string buff;
	getline(std::cin, buff);
}

// Функция считывает один элемент и добавляет его в древо.
void input_one_item(bin_tree<worker>& my_tree) {
	worker item;
	std::cout << "Enter one worker\n";
	input_worker(item);
	// Убираем мусор из потока.
	std::cin.get();
	my_tree.insert(item);
}

// Функция ввода всего дерева с клавиатуры.
void input_tree(bin_tree<worker>& my_tree) {
	int num;
	std::cout << "Enter item number: ";
	input_positiv_int(num);
	// Убираем мусор из потока.
	std::cin.get();
	for (int i = 0; i < num; i++) {
		worker item;
		std::cout << "Enter worker\n";
		input_worker(item);
		// Убираем мусор из потока.
		std::cin.get();
		my_tree.insert(item);
	}
}

// Функция ввода всего дерева из файла.
// Неккоректно считаные элементы пропускаются.
void file_input_tree(bin_tree<worker>& my_tree) {
	std::string file_name;
	std::cout << "Enter file name: ";
	input_file_name(file_name);
	// Убираем мусор из потока.
	std::cin.get();
	std::ifstream fin(file_name);
	int num;
	file_input_positiv_int(num, fin);
	for (int i = 0; i < num; i++) {
		worker item;
		file_input_worker(item, fin);
		my_tree.insert(item);
	}
	fin.close();
}

// Функция удаляет введенный элемент из дерева.
void delete_item(bin_tree<worker>& my_tree) {
	worker item;
	std::cout << "Enter worker\n";
	input_worker(item);
	// Убираем мусор из потока.
	std::cin.get();
	my_tree.remove(item);
}

// Функция определяет, есть ли введенный элемент в дереве.
void find_item(bin_tree<worker>& my_tree) {
	worker item;
	std::cout << "Enter worker\n";
	input_worker(item);
	pnode<worker> pos = my_tree.find(item);
	if (pos) {
		std::cout << "Item found\n";
		// Убираем мусор из потока.
		std::cin.get();
		return;
	}
	std::cout << "Item not found\n";
	// Убираем мусор из потока.
	std::cin.get();
}

// Функция редактирования запрошенного пользователем элемента.
void edit_item(bin_tree<worker>& my_tree) {
	worker item;
	std::cout << "Enter worker\n";
	input_worker(item);
	pnode<worker> pos = my_tree.find(item);
	if (! pos) {
		std::cout << "Item not found\n";
		// Убираем мусор из потока.
		std::cin.get();
		return;
	}
	my_tree.remove(item);
	std::cout << "Enter new worker\n";
	std::cin.get();
	input_worker(item);
	// Убираем мусор из потока.
	std::cin.get();
	my_tree.insert(item);
}

// Функция сравнивает имена двух работников.
bool cmp_work_name(const worker& first, const worker& second) {
	return first.work_name() == second.work_name();
}

// Функция выводит всех работников с введенным названинем работы.
void print_with_same_work_name(bin_tree<worker>& my_tree) {
	std::string work_name;
	std::cout << "Enter work name: ";
	std::cin >> work_name;
	// Убираем мусор из потока.
	std::cin.get();
	int count_item = my_tree.print_lnr(cmp_work_name, worker("", work_name, 0));
	if (! count_item) std::cout << "No items\n";
}

// Функция сравнивает стаж работы.
bool cmp_hire_year(const worker& first, const worker& second) {
	return first.hire_year() > second.hire_year();
}

// Функция выводит всех работников, которые наняты после введенного года.
void print_after_set_year(bin_tree<worker>& my_tree) {
	int year;
	std::cout << "Enter hire year: ";
	input_positiv_int(year);
	// Убираем мусор из потока.
	std::cin.get();
	int count_item = my_tree.print_lnr(cmp_hire_year, worker("", "", year));
	if (! count_item) std::cout << "No items\n";
}

// Вывод пунктов первого меню и выбор пункта.
int choise_build_menu() {
	int choice;
	system("clear");
	std::cout << "Build Tree Menu\n"
			  << "1 - Keyboard input\n"
			  << "2 - File input\n"
			  << "3 - Quit\n"
			  << "Please choose: ";
	input_positiv_int(choice);
	// Убираем мусор из потока.
	std::cin.get();
	return choice;
}

// Вывод пунктов второго меню и выбор пункта.
int choise_main_menu() {
	int choice;
	system("clear");
	std::cout << "Main Menu\n"
			  << "1 - Add item\n"
			  << "2 - Delete item\n"
			  << "3 - Find item\n"
			  << "4 - Edit item\n"
			  << "5 - Print tree\n"
			  << "6 - Print with the same work name\n"
			  << "7 - Print after a set year\n"
			  << "8 - Quit\n"
			  << "Please choose: ";
	input_positiv_int(choice);
	// Убираем мусор из потока.
	std::cin.get();
	return choice;
}

// Цикл второго меню.
void main_menu(bin_tree<worker>& my_tree) {
	int choice;
	while (true) {
		choice = choise_main_menu();
		switch(choice) {
			case 1:
				input_one_item(my_tree);
				break;
			case 2:
				delete_item(my_tree);
				break;
			case 3:
				find_item(my_tree);
				std::cout << "Press enter...";
				read_enter();
				break;
			case 4:
				edit_item(my_tree);
				std::cout << "Press enter...";
				read_enter();
				break;
			case 5:
				my_tree.print();
				std::cout << "Press enter...";
				read_enter();
				break;
			case 6:
				print_with_same_work_name(my_tree);
				std::cout << "Press enter...";
				read_enter();
				break;
			case 7:
				print_after_set_year(my_tree);
				std::cout << "Press enter...";
				read_enter();
				break;
			case 8:
				system("clear");
				return;
			default:
				std::cout << "No such item\nPress enter...";
				read_enter();
				continue;
		}
	}
}

// Цикл первого меню.
void build_menu(bin_tree<worker>& my_tree) {
	int choice;
	while (true) {
		choice = choise_build_menu();
		switch (choice) {
			case 1:
				input_tree(my_tree);
				break;
			case 2:
				file_input_tree(my_tree);
				std::cout << "Press enter...";
				read_enter();
				break;
			case 3:
				system("clear");
				return;
			default:
				std::cout << "No such item\nPress enter...";
				read_enter();
				continue;
		}
		break;
	}
	main_menu(my_tree);
}