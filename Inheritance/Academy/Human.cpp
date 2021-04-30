#include"Human.h"

const string& Human::get_last_name()const
{
	return last_name;
}
const string& Human::get_first_name()const
{
	return first_name;
}
/*const time_t& get_birth_date()const
{
	return birth_date;
}*/
unsigned int Human::get_age()const
{
	return age;
}
void Human::set_last_name(const string& last_name)
{
	this->last_name = last_name;
}
void Human::set_first_name(const string& first_name)
{
	this->first_name = first_name;
}
/*void set_birth_date(const time_t& birth_date)
{
	this->birth_date = birth_date;
}*/
void Human::set_age(unsigned int age)
{
	this->age = age;
}

//			Constructors
Human::Human(const string& last_name, const string& first_name, unsigned int age)
{
	set_last_name(last_name);
	set_first_name(first_name);
	//set_birth_date(birth_date);
	set_age(age);
	cout << "HConstructor:\t" << this << endl;
}
Human::~Human()
{
	cout << "HDestructor:\t" << this << endl;
}

//			Methods
void Human::info()const
{
	/*cout << "Last name: " << last_name << endl;
	cout << "First name:" << first_name << endl;
	cout << "Age:\t\t" << age << " years" << endl;*/
	//cout << "Birth date:" << birth_date << endl;
	cout << last_name << " " << first_name << ", " << age << " лет" << endl;
}