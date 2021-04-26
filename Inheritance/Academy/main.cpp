#include<iostream>
#include<string>
#include<ctime>
using namespace std;

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
	const string& get_last_name()const
	{
		return last_name;
	}
	const string& get_first_name()const
	{
		return first_name;
	}
	/*const time_t& get_birth_date()const
	{
		return birth_date;
	}*/
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	/*void set_birth_date(const time_t& birth_date)
	{
		this->birth_date = birth_date;
	}*/
	void set_age(unsigned int age)
	{
		this->age = age;
	}
	//			Constructors
	Human(const string& last_name, const string& first_name, unsigned int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		//set_birth_date(birth_date);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//			Methods
	virtual void info()const
	{
		/*cout << "Last name: " << last_name << endl;
		cout << "First name:" << first_name << endl;
		cout << "Age:\t\t" << age << " years" << endl;*/
		//cout << "Birth date:" << birth_date << endl;
		cout << last_name << " " << first_name << ", " << age << " лет" << endl;
	}
};

class Student :public Human
{
	string speciality;
	string group;
	double rating;
public:
	const string& get_speciality()const
	{
		return speciality;
	}
	const string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
		//this->set_first_name("Test");
	}
	void set_group(const string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	//		Constructors
	Student
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
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//			Methods:
	void info()const
	{
		Human::info();
		cout << speciality << ", " << group << ", успеваемость: " << rating << endl;
	}
};

class Teacher :public Human
{
	string speciality;
	unsigned int experience;
public:
	const string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}
	//			Constructurs:
	Teacher
	(
		HUMAN_TAKE_PARAMETERS,
		TEACHER_GET_PARAMETERS
	) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//			Methods:
	void info()const
	{
		Human::info();
		cout << speciality << ", опыт преподавания " << experience << " лет." << endl;
	}
};

class Graduate :public Student
{
	string topic;	//Тема дипломного проекта
public:
	const string& get_topic()const
	{
		return this->topic;
	}
	void set_topic(const string& topic)
	{
		this->topic = topic;
	}

	Graduate
	(
		HUMAN_TAKE_PARAMETERS,//Атрибуты базового класса
		STUDENT_GET_PARAMETERS,	//Атрибуты нашего класса
		const string& topic
	) :Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS),
		topic(topic)
	{
		cout << "GConstroctor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestroctor:\t" << this << endl;
	}
	void info()const
	{
		Student::info();
		cout << "Тема дипломного проекта: " << topic << endl;
	}
};

//#define INHERITANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE_CHECK
	/*Human human("Тупенко", "Василий", 18);
human.info();*/
	Student vasya("Тупенко", "Василий", 18, "Программирование", "BV_011", 4.5);
	vasya.info();

	Teacher teacher("Einstein", "Albert", 150, "Phisics", 120);
	teacher.info();

	Graduate Tony(
		"Montana", "Antonio", 25,
		"Современные технологии продаж", "BV_011", 80,
		"Распространение кокаина");
	Tony.info();
#endif // INHERITANCE_CHECK
	/*
	//Polymorphism (Многоформенность - poly - много, morphis - форма) - это спопсобность объектов вести себя по разному,
	  в зависимости от того, КЕМ ОНИ ЯВЛЯЮТСЯ.
	1. Pointer to base class; Указатель на базовый класс может хранить адрес дочернего объекта. (Generalization)
	2. Vitual methods;	(Specialization)
	*/

	//1. Generalization:
	Human* group[] =
	{
		new Student("Батодалаев", "Даши", 16, "РПО", "PD_011", 5),
		new Student("Загидуллин", "Линар", 32, "РПО", "PD_011", 5),
		new Graduate("Шугани", "Сергей", 15, "РПО", "PD_011", 5, "Защита персональных данных"),
		new Teacher("Einstein", "Albert", 141, "Atrophisics", 110),
		new Student("Маркин", "Даниил", 17, "РПО", "BV_011", 5),
		new Teacher("Richter", "Jeffrey", 45, "Windows development", 20)
	};


	cout << sizeof(group) << endl;
	//2. Specialization:
	cout << delimiter << endl;;
	for (int i = 0; i < sizeof(group)/sizeof(Human*); i++)
	{
		group[i]->info();
		cout << delimiter << endl;;
	}

	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)
	{
		delete group[i];
	}
}

/*int bin_to_dec(char str[])
{
	if (!is_bin_number(str))return 0;
	int decimal = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] != ' ')
		{
			decimal *= 2;
			decimal += str[i] - '0';
		}
	}
	return decimal;
}*/