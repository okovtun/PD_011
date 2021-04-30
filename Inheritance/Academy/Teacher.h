#pragma once
#include"Human.h"
class Teacher :public Human
{
	string speciality;
	unsigned int experience;
public:
	const string& get_speciality()const;
	unsigned int get_experience()const;
	void set_speciality(const string& speciality);
	void set_experience(unsigned int experience);
	//			Constructurs:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_GET_PARAMETERS);
	~Teacher();

	//			Methods:
	void info()const;
};

ostream& operator<<(ostream& os, const Teacher& obj);