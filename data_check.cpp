	#include "data_check.hpp"

// Функция проверяет корректность записи имени работника.
bool check_name(const std::string& name) {
	for (int i = 0; i < name.size(); i++) {
		if (name[i] != ' ')
			continue;
		int chek_size = name.size() - 1 - i;
		if (chek_size != 5)
			return false;
		if (isalpha(name[i + 1]) && name[i + 2] == '.' &&
			name[i + 3] == ' ' &&
			isalpha(name[i + 4]) && name[i + 5] == '.')
			return true;
		else
			return false;
	}
	return false;
}

// Функция проверяет корректность введенного имени работника.
void input_name(std::string& name) {
	std::getline(std::cin, name);
	while (! check_name(name)) {
		std::cout << "Try again: ";
		std::getline(std::cin, name);
	}
}

// Функция проверяет корректность введенного имени файла для чтения.
void input_file_name(std::string& file_name) {
	std::cin >> file_name;
	std::ifstream fin(file_name);
	while (! fin.is_open()) {
		std::cout << "Error, try again: ";
		std::cin >> file_name;
		fin = std::ifstream(file_name);
	}
	fin.close();
}

// Функция проверяет корректность введенного положительного числа.
void input_positiv_int(int& value) {
	std::string number;
	while (true) {
		std::cin >> number;
		try {
			value = stoi(number);
		} catch (...) {
			std::cout << "Try again: ";
			continue;
		}
		if (value <= 0) continue;
		break;
	}
}

// Функция проверяет корректность введенного положительного числа из файла.
void file_input_positiv_int(int& value, std::ifstream& fin) {
	std::string number;
	fin >> number;
	try {
		value = stoi(number);
	} catch (...) {
		std::cout << "Error: not int\n";
	}
	if (value <= 0) {
		std::cout << "Error: not positiv int\n";
		value = 0;
	}
}

// Функция проверяет корректность введенного работника.
void input_worker(worker& object) {
	std::string worker_name, hire_year, work_name;
	int value;
	while (true) {
		std::cout << "Enter worker name: ";
		std::getline(std::cin, worker_name);
		std::cout << "Enter work name: ";
		std::cin >> work_name;
		std::cout << "Enter hire year: ";
		std::cin >> hire_year;
		try {
			value = stoi(hire_year);
		} catch (...) {
			std::cout << "Try again\n";
			continue;
		}
		if (! check_name(worker_name) || value < 0 || value > 2022) {
			std::cout << "Try again: ";
			continue;
		}
		break;
	}
	object = worker(worker_name, work_name, value);
}

// Функция проверяет корректность введенного работника из файла.
void file_input_worker(worker& object, std::ifstream& fin) {
	std::string worker_name, hire_year, work_name;
	int value;
	while (true) {
		std::getline(fin, worker_name);
		std::getline(fin, worker_name);
		fin >> work_name;
		fin >> hire_year;
		try {
			value = stoi(hire_year);
		} catch (...) {
			std::cout << "Error: not number\n";
			continue;
		}
		if (! check_name(worker_name) || value < 0 || value > 2022) {
			std::cout << "Error: bed worker\n";
			continue;
		}
		break;
	}
	object = worker(worker_name, work_name, value);
}