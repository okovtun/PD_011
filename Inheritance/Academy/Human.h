#pragma once
#include<iostream>
#include<string>
#include<ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

#define delimiter "\n------------------------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS	const string& last_name, const string& first_name, unsigned int age
#define STUDENT_GET_PARAMETERS	const string& speciality, const string& group, double rating
#define TEACHER_GET_PARAMETERS	const string& speciality, unsigned int experience

#define HUMAN_GIVE_PARAMETERS	last_name, first_name, age
#define STUDENT_GIVE_PARAMETERS speciality, group, rating
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Human
{
	string last_name;
	string first_name;
	//time_t birth_date;
	unsigned int age;
public:
	const string& get_last_name()const;
	const string& get_first_name()const;
	unsigned int get_age()const;
	void set_last_name(const string& last_name);
	void set_first_name(const string& first_name);
	void set_age(unsigned int age);
	//			Constructors
	Human(const string& last_name, const string& first_name, unsigned int age);
	virtual ~Human();

	//			Methods
	virtual void info()const;
};