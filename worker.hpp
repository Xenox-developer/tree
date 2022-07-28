#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>
#include <string>

class worker {
private:
	// В формате фамилия и инициалы (инициалы в виде: И. И.)
	std::string _worker_name;
	// Название работы.
	std::string _work_name;
	// Год найма.
	int _hire_year;

public:
	worker() : _worker_name(""), _work_name(""), _hire_year(0) {}

	worker(std::string worker_name, std::string work_name, int hire_year) :
		_worker_name(worker_name), _work_name(work_name), _hire_year(hire_year) {}

	worker operator=(const worker&);

	int hire_year() const { return _hire_year; }
	std::string work_name() const { return _work_name; }

	int operator<(const worker&) const;
	int operator>(const worker&) const;
	int operator==(const worker&) const;

	friend std::ostream& operator<<(std::ostream&, const worker&);

	worker(const worker& object) :
		_worker_name(object._worker_name),
		_work_name(object._work_name),
		_hire_year(object._hire_year) {}

	~worker() {}
};

#endif // WORKER_HPP