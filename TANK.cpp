#include "TANK.h"

Node::Node(DATA* data) {	//Конструктор
	this->data = *data;
	this->prev = this->next = NULL;
}

LincedList::LincedList() {	//Конструктор
	head = tail = NULL;
}

LincedList::~LincedList() {	//Деструктор для удаления всех эл-тов списка
	while (head != NULL) {	//Пока существуют объекты
		pop_front();
	}
}

Node* LincedList::push_front(DATA* data) {	//Метод добавления объекта в начало списка
	Node* ptr = new Node(data);	//Создание нового объекта Node
	//Настройка связей
	ptr->next = head;
	if (head != NULL) {	//Если head указывает на сущ. объект
		head->prev = ptr;
	}
	if (tail == NULL) {	//Означает, что мы добавляем самый первый эл-т в список
		tail = ptr;
	}
	head = ptr;	//Т.к. добавили в начало, то head - новый объект
	return ptr;	//Возвращаем ссылку на созданный объект
}

Node* LincedList::push_back(DATA* data) {	//Метод добавления объекта в конец списка
	Node* ptr = new Node(data);	//Создание нового объекта Node
	//Настройка связей
	ptr->prev = tail;
	if (tail != NULL) {	//Если tail указывает на сущ. объект
		tail->next = ptr;
	}
	if (head == NULL) {	//Означает, что мы добавляем самый первый эл-т в список
		head = ptr;
	}
	tail = ptr;	//Т.к. добавили в конец, то tail - новый объект
	return ptr;	//Возвращаем ссылку на созданный объект
}

void LincedList::pop_front() {	//Метод удаления сначала
	if (head == NULL) {	//Если эл-тов нет - нечего удалять
		return;
	}
	Node* ptr = head->next;
	if (ptr != NULL) {	//Если сущ. 2-ой эл-т
		ptr->prev = NULL;
	}
	else {	//Если всего 1 объект
		tail = NULL;
	}
	delete head;
	head = ptr;
}

void LincedList::pop_back() {	//Метод удаления с конца
	if (tail == NULL) {	//Если эл-тов нет - нечего удалять
		return;
	}
	Node* ptr = tail->prev;
	if (ptr != NULL) {	//Если сущ. 2-ой эл-т
		ptr->next = NULL;
	}
	else {	//Если всего 1 объект
		head = NULL;
	}
	delete tail;
	tail = ptr;
}

Node* LincedList::getAt(int index) {	//Метод поиска произвольного объекта по индексу
	Node* ptr = head;	//Указатель на head ("индекс 0")
	int n = 0;	//Счетчик индексов
	while (n != index) {	//Пока не дойдем до нужного индекса
		if (ptr == NULL) {	//Если не сущ. объектов или дошли до конца списка
			return NULL;
		}
		ptr = ptr->next;	//Перемещаем на след. объект
		n++;	//Увеличиваем счетчик
	}
	return ptr;	//Возвращаем эл-т
}

Node* LincedList::operator [] (int index) {//Оператор, который возвр. эл-т по опр. индексу (квадратные скобки)
	return getAt(index);
}

Node* LincedList::insert(int index, DATA* data) { //Вставка эл-та в произвольное место
	Node* right = getAt(index);
	if (right == NULL) {	//Если нет эл-та справа
		return push_back(data); //Значит добавляем новый эл-т в конец списка
	}
	Node* left = right->prev;
	if (left == NULL) {	//Если мы добавляем первый эл-т
		return push_front(data);
	}

	//В остальных случаях добавляем объект между 2-мя существующими

	Node* ptr = new Node(data);
	//Настроим связи
	ptr->prev = left;
	ptr->next = right;
	left->next = ptr;
	right->prev = ptr;
}

void LincedList::erase(int index) {	//Удаление промежуточного эл-та
	Node* ptr = getAt(index);	//Получаем указатель эл-та, который собираемся удалить
	if (ptr == NULL) {	//Если такого эл-та нет
		return;	//Прекратить
	}
	if (ptr->prev == NULL) {	//Если в списке 1 эл-т
		pop_front();
		return;
	}
	if (ptr->next == NULL) {	//Если нет эл-та справа
		pop_back();
		return;
	}
	//В остальных случаях удаляем промежуточный эл-т
	Node* left = ptr->prev;
	Node* right = ptr->next;
	//Настройка связей
	left->next = right;
	right->prev = left;
	delete ptr; // Удаление объекта
}