#include"String.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////			CLASS DEFINITION - ОПРЕДЕЛЕНИЕ КЛАССА			///////////////////////

const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
int String::get_size()const
{
	return size;
}
//				Constructors:
String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << (size == 80 ? "Default" : "Size") << "Constructor:\t" << this << endl;
}
String::String(const char* str) :String(strlen(str) + 1)	//Делегирование конструктора с одним параметром типа int
												//для того, чтобы он выделил память
{
	strcpy(this->str, str);	//String copy
	//strcpy_s(this->str, size, str);
	cout << "Constructor:\t\t" << this << endl;
}
String::String(const String& other) :String(other.str)
{
	/*this->size = other.size;
	this->str = new char[size] {};*/
	/*for (int i = 0; i < size; i++)
		this->str[i] = other.str[i];*/
		//strcpy(this->str, other.str);
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other) :size(other.size), str(other.str)
{
	/*this->size = other.size;
	this->str = other.str;*/
	other.str = nullptr;
	cout << "MoveConstructor:\t" << this << endl;
}
String::~String()
{
	delete[] this->str;
	cout << "Destructor:\t\t" << this << endl;
}

//			Operators:
String& String::operator=(const String& other)
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
String& String::operator=(String&& other)
{
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.str = nullptr;
	cout << "MoveAssignment:\t\t" << this << endl;
	return *this;
}

String& String::operator+=(const String& other)
{
	return *this = *this + other;
}

const char& String::operator[](int i)const
{
	return this->str[i];
}
char& String::operator[](int i)
{
	return this->str[i];
}

//			Methods:
void String::print()const
{
	cout << "size:\t" << size << endl;
	cout << "str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	/*for (int i = 0; i < left.get_size(); i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		result[i + left.get_size() - 1] = right[i];*/
	strcpy(result.get_str(), left.get_str());//выполняет копирование строки left в строку result
	strcat(result.get_str(), right.get_str());//выполняет конкатенацию строки right в строку result
	return result;
}

ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//////////////////////////					CLASS DECLARATION END					///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////