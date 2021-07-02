#include<iostream>
#include<array>
#include<vector>
#include<list>

//using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define STL_ARRAY
//#define STL_VECTOR
//#define EXCEPTIONS_IN_VECTOR
#define STL_LIST

template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;	//Вместительность - сколько элементов может вместить в себя вектор без переопределения памяти.
	cout << "MaxSize: " << vec.max_size() << endl;
}
template<typename T>void vector_print(const std::vector<T>& vec)
{
	for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T>void vector_reverse_print(const std::vector<T>& vec)
{
	for (typename std::vector<T>::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
	{
		cout << *it << tab;
	}
	std::cout << std::endl;
}
template<typename T>void list_print(const std::list<T>& list)
{
	for (typename std::list<T>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	const int n = 5;
	std::array<int, n> arr = { 3,5,8,13,21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива.
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	vector_properties(vec);
	vec.push_back(55);
	vector_properties(vec);

#ifdef EXCEPTIONS_IN_VECTOR
	try
	{
		for (int i = 0; i < vec.size(); i++)
		{
			//try...catch...
			//[] - index operator (subscript operator)
			//cout << vec[i] << tab;	//Оператор [] НЕ бросает исключение при выходе за пределы вектора.
			cout << vec.at(i) << tab;	//Метод at() бросает исключение (out of range exception) при выходе за пределы вектора.
		}
		cout << endl;
		//throw 123;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	catch (int e)
	{
		std::cerr << "Error number: " << e << endl;
	}
#endif // EXCEPTIONS_IN_VECTOR

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	std::vector<int>::iterator position = vec.begin() + index;
	vec.insert(position, value);

	vector_print(vec);
	vector_reverse_print(vec);

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	vec.erase(vec.begin() + index);
	vector_print(vec);
	vector_properties(vec);
	vec.assign({ 1024, 2048, 3072 });
	vector_print(vec);
	vector_properties(vec);
	vec.shrink_to_fit();
	vector_properties(vec);


#endif // STL_VECTOR

#ifdef STL_LIST
	//list - это контейнер, который хранит объекты в виде двусвязного списка.
	std::list<int> list = { 3,5,8,13,21 };
	/*for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << tab;	//Оператор [] недопустим в списках, поскольку он очень сильно снижает производительность.
	}
	cout << endl;*/
	list_print(list);
	/*std::vector<int> vec = { 3,5,8,13,21 };
	cout << "VectorSize:   " << vec.size() << endl;
	cout << "VectorMaxSize:" << vec.max_size() << endl;

	cout << "ListSize:     " << list.size() << endl;
	cout << "ListMaxSize:  " << list.max_size() << endl;*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	std::list<int>::iterator position = list.begin();
	for (int i = 0; i < index; i++)position++;
	list.insert(position, value);
	list_print(list);
#endif // STL_LIST


}