#ifndef BIN_TREE_HPP
#define BIN_TREE_HPP

#include <iostream>
#include <string>

/* Реализыция АВЛ-дерева. Дерево состоит из узлов, кождый из который хранит в себе значение (ключ)
   и ссылки на своих детей. Класс шаблонный, для работы с пользовательским типом данных необходимо
   переопределение следующих операторов:
   1. Оператор сравнения "больше" '>'
   2. Оператор сравнения "меньше" '<'
   3. Оператор сравнения "равно" '=='
   4. Оператор вывода '<<'.
*/

template <class Type>
class bin_tree;

template <class Type>
class tree_node {
private:
	/* Переменная хранит высоту дерева с вершиной в данном узле. Просто у вершины (без поддеревьев)
	   высота считается равной 1.
	   Тип unsigned char взят с целью уменьшения занимаемой служебной памяти в узле. Переполнение
	   переменной в теории не произойдет: 10^9 узлов с переменными типа int занимают в памяти около
	   10 Гб данных, при этом высота дерева будет равняться 44. */
	unsigned char _height;
	// Ссылки на левого и правого сыновей узла соответственно.
	tree_node<Type>* _left;
	tree_node<Type>* _right;
public:
	tree_node(Type key = Type()) : _height(1), _left(0), _right(0), _key(key) {}
	~tree_node() {}

	// Класс bin_tree объявлен дружественным, чтобы в рамках класса bin_tree иметь прямой доступ к
	// приватным полям класса tree_node, но при этом из вне к ним доступа не было.
	template <class Type1>
	friend class bin_tree;

	// Переменная хранит ключ узла - значение, которое в него записано.
	Type _key;
};

// Тип данных - указатель на узел дерева.
template <class Type>
using pnode = tree_node<Type>*;

template <class Type>
class bin_tree {
public:
	bin_tree() : _root(0) {}
	// В деструкторе достаточно вызвать метод удаление дерева с вершиной в главном корне.
	~bin_tree() { destroy(_root); }

	// Здесь описаны обертки над основными приватными методами для работы с деревом.

	// Метод вставки ключа в дерево. Вызывает рекурсивную функцию добавление узла в дерево.
	void insert(const Type& key) { _root = add_node(_root, key); }
	// Метод удаления узла с ключем key. Вызывает рекурсивный метод удаления узла.
	void remove(const Type& key) { _root = delete_node(_root, key); }

	// Метод возвращает указатель на узел с переданным ключем. В случае, если такого узла нет,
	// метод вернет нулевой указатель.
	pnode<Type> find(const Type& key) const { return find_node(_root, key); }
	// Метод поиска максимального ключа в дереве.
	Type max() const { return max(_root)->_key; }
	// Метод поиска минимального ключа в дереве.
	Type min() const { return min(_root)->_key; }

	// Метод печати дерева в консоль. Вызывает рекурсивный метод печати дерева в консоль.
	void print() const { print(_root, 0); }

	// Метод печатает дерево в консоль по пути прямого обхода.
	void print_lnr() const { print_lnr(_root); }

	// Указатель на функцию сравнения для печати и поиска определенных ключей.
	using function_ptr = bool(*)(const Type&, const Type&);
	
	// Метод печатает ключе дерева, удовлетворяющие условию check. Внути функции ключи дерева
	// сравниваются с элементом object. Вовзращает число напечатаных объектов.
	int print_lnr(function_ptr check, const Type& object) const 
		{ return print_lnr(_root, check, object); };

private:
	// Корень дерева - главная вершина.
	pnode <Type> _root;

	// Далее идет часть методов, необходимых для балансировка дерева.

	// Метод вычисляет баланс высот (разницу высоты правого поддерева с левым) у узла.
	int bal_factor(pnode<Type>) const;
	// Метод восттанавливает значение высоты у узла (берет высоту максимального из поддеревьев
	// плюс один).
	void fix_height(pnode<Type>);
	// Метод выполняет правый поворот вокруг узла pos.
	pnode<Type> rotate_right(pnode<Type>);
	// Метод выполняет левый поворот вокруг узла pos.
	pnode<Type> rotate_left(pnode<Type>);
	// Метод балансировки узла pos.
	pnode<Type> balance(pnode<Type>);

	// Далее идут основные методы для работы с деревом

	// Метод рекурсивного добавления элемента в бинарное дерево.
	pnode<Type> add_node(pnode<Type>, const Type&);
		// Рекурсивный метод удаления узла дерева.
	pnode<Type> delete_node(pnode<Type>, const Type&);
	// Метод рекурсивно удаляет дерево с корнем pos.
	void destroy(pnode<Type>);

	// Метод ищет указатель на узел с ключем key. Если такого узла нет, будет возвращен нулевой
	// указатель.
	pnode<Type> find_node(pnode<Type>, const Type&) const;
	// Рекурсивный поиск максимального ключа в дереве с корнем pos.
	pnode<Type> max(pnode<Type>) const;
	// Рекурсивный поиск минимального ключа в дереве с корнем pos.
	pnode<Type> min(pnode<Type>) const;

	// Рекурсивный метод печати дерева со сдвигами по уровню.
	// Дерево печатается в консоль лежащим на своем левом боку.
	void print(pnode<Type>, const int) const;

	// Метод печатает дерево в консоль по пути прямого обхода.
	void print_lnr(pnode<Type>) const;

	/* Метод печатает только те элементы дерева, которые удавлетворяют функции.
	   Функция сравнивает значение ключа с переданным значением типа Type. Способ сравнения задается
	   функцией. Возвращает число напечатаных объектов. */
	int print_lnr(pnode<Type>, function_ptr, const Type&) const;
};

// Метод вычисляет баланс высот (разницу высоты правого поддерева с левым) у узла.
template <class Type>
int bin_tree<Type>::bal_factor(pnode<Type> pos) const {
	if (! pos) return 0;
	// Если узел пустой, значит его высота ноль.
	int height_l = (pos->_left) ? pos->_left->_height : 0;
	int height_r = (pos->_right) ? pos->_right->_height : 0;
	return height_r - height_l;
}

// Метод восттанавливает значение высоты у узла (берет высоту максимального из поддеревьев
// плюс один).
template <class Type>
void bin_tree<Type>::fix_height(pnode<Type> pos) {
	if (! pos) return;
	int height_l = (pos->_left) ? pos->_left->_height : 0;	
	int height_r = (pos->_right) ? pos->_right->_height : 0;
	pos->_height = ((height_l > height_r) ? height_l : height_r) + 1;
}

// Метод выполняет правый поворот вокруг узла pos.
template <class Type>
pnode<Type> bin_tree<Type>::rotate_right(pnode<Type> pos) {
	// В случае нулевого pos будет ошибка. Но поворот никогда не вызывается от пустого узла.
	pnode<Type> temp = pos->_left;
	pos->_left = temp->_right;
	temp->_right = pos;
	fix_height(pos);
	fix_height(temp);
	return temp;
}

// Метод выполняет левый поворот вокруг узла pos.
template <class Type>
pnode<Type> bin_tree<Type>::rotate_left(pnode<Type> pos) {
	// В случае нулевого pos будет ошибка. Но поворот никогда не вызывается от пустого узла.
	pnode<Type> temp = pos->_right;
	pos->_right = temp->_left;
	temp->_left = pos;
	fix_height(pos);
	fix_height(temp);
	return temp;
}

// Метод балансировки узла pos.
template <class Type>
pnode<Type> bin_tree<Type>::balance(pnode<Type> pos) {
	fix_height(pos);
	/* Разность в высотах поддеревьев у узла никогда не будет больше 2 по модулю.
	   Если баланс положительный, значит высота правого поддерева больше левого, нужно выполнить
	   поворот налево вокруг pos. */
	if (bal_factor(pos) == 2) {
		/* Если высота левого поддерева у правого сына pos больше правого поддерева, то
		   необходимо выполнить большой поворот. Для этого перед левым поворотом pos нужно
		   выполнить правый поворот вокруг правого сына pos. */
		if (bal_factor(pos->_right) < 0) pos->_right = rotate_right(pos->_right);
		return rotate_left(pos);
	}
	// Если баланс отрицательный, значит высота левого поддерева больше правого, нужно выполнить
	// поворот направо вокруг pos.
	if (bal_factor(pos) == -2) {
		/* Если высота правого поддерева у левого сына pos больше левого поддерева, то
		   необходимо выполнить большой поворот. Для этого перед правым поворотом pos нужно
		   выполнить левый поворот вокруг левого сына pos. */
		if (bal_factor(pos->_left) > 0) pos->_left = rotate_left(pos->_left);
		return rotate_right(pos);
	}
	return pos;
}

// Метод рекурсивного добавления элемента в сбалансированное бинарное дерево.
template <class Type>
pnode<Type> bin_tree<Type>::add_node(pnode<Type> pos, const Type& key) {
	// Если позиция пустая, то вставляем в нее узел.
	if (! pos) return new tree_node<Type>(key);
	// Иначе смотрим, больше или меньше ключ вставляемого узла текущего.
	if (pos->_key < key)
		// Если больше, то вставляем в правое поддерево.
		pos->_right = add_node(pos->_right, key);
	else if (pos->_key > key)
		// Если меньше, то вставляем в левое поддерево.
		pos->_left = add_node(pos->_left, key);
	// В случае равенства ключей, узел не добавляется.
	// Выполняем балансировку возвращаемого узла.
	return balance(pos);
}

// Рекурсивный метод удаления узла сбалансированного бинарного дерева.
template <class Type>
pnode<Type> bin_tree<Type>::delete_node(pnode<Type> pos, const Type& key) {
	// Если узел пустой, удалять нечего.
	if (! pos) return pos;
	/* Дальше необходимо рассмотреть два случая:
	   1. Ключ удаляемого узла меньше ключа текущего узла.
	      Тогда удаляем узел в левом поддереве.
	   2. Ключ удаляемого узла больше ключа текущего узла.
	      Тогда удаляем узел в правом поддереве. */
	if (key < pos->_key)
		pos->_left = delete_node(pos->_left, key);
	else if (key > pos->_key)
		pos->_right = delete_node(pos->_right, key);
	/* Дальше рассмотрим вариант, когда ключ удаляемого узла равен ключу текущего. В данном
	   случае сначала проверим, не пустые ли правый и левый узлы. Если они оба не пустые, тогда
	   заменяем ключ в текущем узле минимальным ключем из правого поддерева и вызываем удаление
	   этого ключа из правого поддерева.
	   Также можно заменять на максимум из левого поддерева.
	*/
	else if (pos->_right and pos->_left) {
		pos->_key = min(pos->_right)->_key;
		pos->_right = delete_node(pos->_right, pos->_key);
	}
	// Дальше по очереди рассматриваем случаи, когда какой то из детей пустой, а другой нет.
	// Дальше идут операции удаления узла, ВАЖНО не забывать занулять указатели.
	else
		if (pos->_left) {
			pos->_key = pos->_left->_key;
			delete pos->_left;
			pos->_left = 0;
		}
		else if (pos->_right) {
			pos->_key = pos->_right->_key;
			delete pos->_right;
			pos->_right = 0;
		}
		// В случае если оба пустые, удаляем текущий узел.
		else {
			delete pos;
			pos = 0;
		}
	// Выполняем балансировку возвращаемого узла.
	return balance(pos);
}

// Метод рекурсивно удаляет дерево с корнем pos.
template <class Type>
void bin_tree<Type>::destroy(pnode<Type> pos) {
	// Если дошли до нулевого указателя, то удалять нечего
	if (! pos) return;
	// Сначала даляем левое поддерево.
	destroy(pos->_left);
	// Потом удаляем правое поддерево.
	destroy(pos->_right);
	// Теперь можно удалить сам корень дерева.
	delete pos;
}

// Метод ищет указатель на узел с ключем key. Если такого узла нет, будет возвращен нулевой
// указатель.
template <class Type>
pnode<Type> bin_tree<Type>::find_node(pnode<Type> pos, const Type& key) const {
	if (! pos) return 0;
	if (pos->_key == key) return pos;
	// Если в текущем узле ключ отличается, то смотрим в каком поддереве его нужно искать.
	if (key < pos->_key)
		return find_node(pos->_left, key);
	else
		return find_node(pos->_right, key);
}

// Рекурсивный поиск максимального ключа в дереве с корнем pos.
template <class Type>
pnode<Type> bin_tree<Type>::max(pnode<Type> pos) const {
	// Максимальный ключ в дереве - это самый правый ключ.
	// Если передан нулевой корень, кидаем исключение.
	if (! pos) throw std::string("error:bin_tree_empty");
	// Если правый узел нулевой, значит максимальный ключ в текущем узле.
	if (! pos->_right) return pos;
	// Иначе вызываем поиск максимального ключа в правом поддереве.
	return max(pos->_right);
}

// Рекурсивный поиск минимального ключа в дереве с корнем pos.
template <class Type>
pnode<Type> bin_tree<Type>::min(pnode<Type> pos) const {
	// Минимальный ключ в дереве - это самый левый ключ.
	// Если передан нулевой корень, кидаем исключение.
	if (! pos) throw std::string("error:bin_tree_empty");
	// Если левый узел нулевой, значит минимальный ключ в текущем узле.
	if (! pos->_left) return pos;
	// Иначе вызываем поиск минимального ключа в правом поддереве.
	return min(pos->_left);
}

// Рекурсивный метод печати дерева со сдвигами по уровню.
// Дерево печатается в консоль лежащим на своем левом боку.
template <class Type>
void bin_tree<Type>::print(pnode<Type> pos, const int level) const {
	// Переменная level нужна, чтобы до печати ключа сдвинуть его на соответствующий уровень.
	// Если узел пуст, то выходим
	if (! pos) return;
	// Иначе вызываем печать правого поддерева.
	print(pos->_right, level + 1);
	// После печати правого поддерева, сдвигаемся на level знаков табуляции и выводим ключ.
	for (int i = 0; i < level; i++) std::cout << '\t';
	std::cout << pos->_key << '\n';
	// После вызываем печать левого поддерева.
	print(pos->_left, level + 1);
}

// Метод печатает дерево в консоль по пути прямого обхода.
template <class Type>
void bin_tree<Type>::print_lnr(pnode<Type> pos) const {
	if (! pos) return;
	// Сначала печатаем левое поддерево.
	print_lnr(pos->_left);
	// Потом выводим ключ узла.
	std::cout << pos->_key << '\n';
	// Потом выводим правое поддерево.
	print_lnr(pos->_right);
}

// Метод печатает только те элементы дерева, которые удавлетворяют функции check.
// Возвращает число напечатаных объектов.
template <class Type>
int bin_tree<Type>::print_lnr(pnode<Type> pos, function_ptr check, const Type& object) const {
	if (! pos) return 0;
	// Переменная хранит колличество напечатаных ключей.
	int ans = 0;
	// Сначала печатаем левое поддерево и прибавляем число напечатаных ключей в нем.
	ans += print_lnr(pos->_left, check, object);
	// Потом выводим ключ узла, если он подходит.
	if (check(pos->_key, object)) {
		std::cout << pos->_key << '\n';
		++ans;
	}
	// Потом выводим правое поддерево и прибавляем число напечатаных ключей в нем.
	ans += print_lnr(pos->_right, check, object);
	return ans;
}

#endif // BIN_TREE_HPP