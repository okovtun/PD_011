#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include<list>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define STL_MAP
#define DICTIONARY

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef STL_MAP
	//map - это контейнер, который хранит объекты в виде бинарного дерева. 
	//Каждым элементом map является ПАРА "ключ - значение" ("key - value").
	//Ключи являются уникальными, то есть, в одном map не может быть 2-х элементов
	//с одинаковыми ключами, хотя значения (value) могут повторяться.
	//multimap позволяет хранить 2 и более одинаковых ключа.

	std::unordered_multimap<int, std::string> week =
	{
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(4, "Thursday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(6, "Saturday"),
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(7, "Sunday")
	};
	//week[7] = "Воскресенье";
	for (std::unordered_multimap<int, std::string>::iterator it = week.begin(); it != week.end(); it++)
	{
		cout << it->first << tab;	//first - ключ (key)
		cout << it->second << endl;	//second - значение (value)
	}
#endif // STL_MAP

#ifdef DICTIONARY
	std::map<std::string, std::list<std::string>> dictionary =
	{
		std::pair<std::string, std::list<std::string>>("Hello", {"Привет", "Здрасьте"}),
		std::pair<std::string, std::list<std::string>>("Space", {"Космос", "Пространство", "Пробел"}),
		std::pair<std::string, std::list<std::string>>("Definition", {"Определение"}),
		std::pair<std::string, std::list<std::string>>("Claim", {"Требовать", "Заявлять о своих правах"}),
		std::pair<std::string, std::list<std::string>>("Tie", {"Лента", "Галстук"})
	};
	for (std::map<std::string, std::list<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		cout << it->first << ":";
		for (std::list<std::string>::iterator jt = it->second.begin(); jt != it->second.end(); jt++)
		{
			cout << *jt << ",";
		}
		cout << endl;
	}
#endif
}