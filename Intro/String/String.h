#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------------\n"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////			CLASS DECLARATION - ОБЪЯВЛЕНИЕ КЛАССА			///////////////////////

class String;
String operator+(const String& left, const String& right);
ostream& operator<<(ostream& os, const String& obj);

class String
{
	char* str;	//Указатель на строку в динамической памяти
	size_t size;	//Размер строки
public:
	const char* get_str()const;
	char* get_str();
	int get_size()const;
	//				Constructors:
	explicit String(int size = 80);
	String(const char* str);
	String(const String& other);
	String(String&& other);
	~String();
	//			Operators:
	String& operator=(const String& other);
	String& operator=(String&& other);
	String& operator+=(const String& other);

	const char& operator[](int i)const;
	char& operator[](int i);

	//			Methods:
	void print()const;
};

//////////////////////////					CLASS DECLARATION END					///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////