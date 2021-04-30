#include"Student.h"


const string& Student::get_speciality()const
{
	return speciality;
}
const string& Student::get_group()const
{
	return group;
}
double Student::get_rating()const
{
	return rating;
}
void Student::set_speciality(const string& speciality)
{
	this->speciality = speciality;
	//this->set_first_name("Test");
}
void Student::set_group(const string& group)
{
	this->group = group;
}
void Student::set_rating(double rating)
{
	this->rating = rating;
}
//		Constructors
Student::Student
(
	HUMAN_TAKE_PARAMETERS,//Атрибуты базового класса
	STUDENT_GET_PARAMETERS	//Атрибуты нашего класса
) :Human(HUMAN_GIVE_PARAMETERS)
{
	set_speciality(speciality);
	set_group(group);
	set_rating(rating);
	cout << "SConstructor:\t" << this << endl;
}
Student::~Student()
{
	cout << "SDestructor:\t" << this << endl;
}

//			Methods:
void Student::info()const
{
	Human::info();
	cout << speciality << ", " << group << ", успеваемость: " << rating << endl;
}