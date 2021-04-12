//#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------------\n"

class String
{
	char* str;	//Указатель на строку в динамической памяти
	int size;	//Размер строки
public:
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	int get_size()const
	{
		return size;
	}
	//				Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << (size==80?"Default":"Size") << "Constructor:\t" << this << endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		strcpy(this->str, str);	//String copy
		//strcpy_s(this->str, size, str);
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		strcpy(this->str, other.str);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t\t" << this << endl;
	}

	//			Operators:
	String& operator=(const String& other)
	{
		//0) Проверить, не является другой объект ЭТИМ объектом:
		if (this == &other)return *this;
		delete[] this->str;//1) В первую очередь удавляем старое значение обекта, 
		//и только после этого присваиваем ему нвове значение.
		this->size = other.size;
		this->str = new char[size] {};
		strcpy(this->str, other.str);
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	//			Methods:
	void print()const
	{
		cout << "str:\t" << str << endl;
		cout << "size:\t" << size << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		result[i + left.get_size() - 1] = right[i];
	return result;
}

ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str;
	str.print();

	//String str2 = 5;	//
	String str2(5);
	str2.print();

	cout << typeid("Hello").name() << endl;
	String str3 = "Hello";
	str3.print();
	cout << str3 << endl;

	String str4 = str3;	//CopyConstructor
	cout << "Str4 - " << str4 << endl;

	String str5;
	str5 = str4;
	cout << "Str5 - " << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	String str1 = "Hello";
	String str2;
	str1 = str1;
	cout << str1 << endl;
	cout << str2 << endl;

	char a = '5';
	a = a;
	cout << a << endl;
#endif // ASSIGNMENT_CHECK

	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3 = str1 + " " + str2;//Оператор + будет выполнять конкатенацию (слияние) строк
	cout << delimiter << endl;
	cout << str3 << endl;
}