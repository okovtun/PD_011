#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------------------------\n"

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;	//Инициализация статической переменной

class ForwardList
{
	Element* Head;
	int size;
public:
	ForwardList()
	{
		//DefaultConstructor создает пустой список.
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		//Этот метод НЕ умеет работать с пустым списком
		if (Head == nullptr)	//ЕСЛИ список пуст
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void insert(int Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++, Temp = Temp->pNext)
			if (Temp->pNext == nullptr)break;
		//Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//		Erasing elements:
	void pop_front()
	{
		//1) Прежде чем исключить элемент из списка, нужно запомнить его адрес, для того, чтобы можно было удалить его из памяти.
		Element* Temp = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти:
		delete Temp;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
			Temp = Temp->pNext;	//Переход на следующий элемент
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//			Methods:
	void print()
	{
		Element* Temp = Head;	//Temp - это итератор.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов:    " << Element::count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	/*cout << delimiter << endl;
	list.pop_front();
	list.pop_back();
	list.print();*/
	int value;
	int index;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << "Введите индекс добавляемого значения: "; cin >> index;
	list.insert(value, index);
	list.print();

	cout << "Еще один список:\n";
	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();
}