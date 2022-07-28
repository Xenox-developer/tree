#ifndef DATA_CHECK_HPP
#define DATA_CHECK_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "worker.hpp"

// Функция проверяет корректность записи времени.
bool check_name(const std::string&);
// Функция проверяет корректность введенного времени.
void input_name(std::string&);

// Функция проверяет корректность введенного имени файла для чтения.
void input_file_name(std::string&);

// Функция проверяет корректность введенного положительного числа.
void input_positiv_int(int&);
// Функция проверяет корректность введенного положительного числа из файла.
void file_input_positiv_int(int&, std::ifstream&);

// Функция проверяет корректность введенного работника.
void input_worker(worker&);
// Функция проверяет корректность введенного работника из файла.
void file_input_worker(worker&, std::ifstream&);

#endif // DATA_CHECK_HPP