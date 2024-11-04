#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#ifndef TANK.h

struct DATA
{
	bool mine = false; //Свой или вражеский
	int a;	//Ячейка по горизонтали
	int b;	//Ячейка по вертикали
	float rotation = 1;
	int hp = 100;
};

class Node {	//Класс одного элемента списка
public:
	DATA data; //Данные
	Node* prev, * next;	//Указатели на пред. и след. эл-ты списка
public:
	Node(DATA* data);	//Конструктор
};

class LincedList {	//Класс списка элементов
public:

	Node* head, * tail;
public:
	LincedList();	//Конструктор
	~LincedList();	//Деструктор для удаления всех эл-тов списка

	Node* push_front(DATA* data);	//Метод добавления объекта в начало списка

	Node* push_back(DATA* data);	//Метод добавления объекта в конец списка

	void pop_front();	//Метод удаления сначала

	void pop_back();	//Метод удаления с конца

	Node* getAt(int index);	//Метод поиска произвольного объекта по индексу

	Node* operator [] (int index);	//Оператор, который возвр. эл-т по опр. индексу (квадратные скобки)

	Node* insert(int index, DATA* data); //Вставка эл-та в произвольное место

	void erase(int index);	//Удаление промежуточного эл-та
};

#endif TANK.h;