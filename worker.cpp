#include "worker.hpp"

worker worker::operator=(const worker& object) {
	if (&object == this)
		return *this;
	_worker_name = object._worker_name;
	_work_name = object._work_name;
	_hire_year = object._hire_year;
	return *this;
}

int worker::operator<(const worker& object) const {
	int size = (_worker_name.size() < object._worker_name.size()) ?
		_worker_name.size() : object._worker_name.size();

	for (int i = 0; i < size; i++) {
		if ((! isalpha(_worker_name[i])) && (! isalpha(object._worker_name[i])))
			continue;
		if (! isalpha(_worker_name[i]))
			return true;
		if (! isalpha(object._worker_name[i]))
			return false;
		if (tolower(_worker_name[i]) == tolower(object._worker_name[i]))
			continue;
		return tolower(_worker_name[i]) < tolower(object._worker_name[i]);
	}
	return false;
}

int worker::operator>(const worker& object) const {
	int size = (_worker_name.size() < object._worker_name.size()) ?
		_worker_name.size() : object._worker_name.size();

	for (int i = 0; i < size; i++) {
		if ((! isalpha(_worker_name[i])) && (! isalpha(object._worker_name[i])))
			continue;
		if (! isalpha(_worker_name[i]))
			return false;
		if (! isalpha(object._worker_name[i]))
			return true;
		if (tolower(_worker_name[i]) == tolower(object._worker_name[i]))
			continue;
		return tolower(_worker_name[i]) > tolower(object._worker_name[i]);
	}
	return false;
}

int worker::operator==(const worker& object) const {
	return _worker_name == object._worker_name;
}

std::ostream& operator<<(std::ostream &output, const worker& object) {
	output << "Worker name: " << object._worker_name <<", "
		   << " Work name: " << object._work_name <<", "
		   << " Hire year: " << object._hire_year << "; ";
	return output;
}