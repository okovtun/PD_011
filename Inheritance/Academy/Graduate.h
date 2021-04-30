#pragma once
#include"Student.h"
class Graduate :public Student
{
	string topic;	//Тема дипломного проекта
public:
	const string& get_topic()const;
	void set_topic(const string& topic);

	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_GET_PARAMETERS, const string& topic);
	~Graduate();
	void info()const;
};

ostream& operator<<(ostream& os, const Graduate& obj);