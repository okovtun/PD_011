#include<iostream>
using namespace std;

#define tab "\t"

using std::cin;
using std::cout;
using std::endl;

//Создание структуры:
class Point
{
	//Структура Point описывает точки на плоскости.
	double x;//Координата по X
	double y;//Координата по Y
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//			Constructors:
	/*Point()
	{
		//Конструктор по умолчанию создает точку в начале коорлинат
		x = y = int();	//Якобы вызываем констуктор по умолчанию для 'int', и он возвращает значение по умолчанию
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Point(double x)
	{
		//Конструктор с одним параметром создает точку на прямой.
		this->x = x;
		this->y = 0;
		cout << "SingleArgumentConstructor:" << this << endl;
	}*/
	Point(double x = 0, double y = 0)
	{
		//Конструктор с параметрами создает точку на плоскости
		//Этот кнструктор с параметрами может быть вызван 
		//-без парамтеров;
		//-с одним параметром;
		//-с двумя параметрами;
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		//other - это другой объект, копию которого мы создаем
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//			Operators:
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	//				Methods:
	void print()
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
	double distance(const Point& other)const
	{
		double x_distance = this->x - other.x;
		double y_distance = other.y - this->y;
		double distance = sqrt(x_distance*x_distance + y_distance * y_distance);//sqrt - Square Root (Квадратный корень)
		return distance;
	}
};
//Создавая структуру или класс, мы создаем новый тип данных, 
//а объявляя объекты этого класса или структуры мы создаем переменные нашего типа.
//			КЛАСС - ЭТО ТИП ДАННЫХ
//		СТРУКТУРА - ЭТО ТИП ДАННЫХ
//		ОБЪЕКТ - ЭТО САМАЯ ОБЫЧНАЯ ПЕРЕМЕННАЯ.

double distance(const Point& A, const Point& B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
	return distance;
}

//#define INTRO
//#define CONSTRUCTORS
#define ASSIGNMENT_CHECK
//#define DISTANCE
//#define OPERATOR_EXAMPLES

void main()
{
	
	setlocale(LC_ALL, "Rus");
#ifdef INTRO
	int a;	//Объявление переменной 'a', типа 'int'
	Point A;//Объявление объекта 'A' структуры 'Point'
			//Объявление переменной 'A' типа 'Point'
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point* pA = &A;	//Создаем указатель на объект
	cout << pA->get_x() << "\t" << pA->get_y() << endl;
#endif // INTRO

#ifdef CONSTRUCTORS
	Point A;//Default constructor
	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point B = 5;//Single-Argument constructor
	B.print();

	Point C(8);	//Single-Argument constructor
	C.print();

	Point D{ 12 };//Single-Argument constructor
	D.print();

	int a(2);
	int b{ 3 };
	cout << a << tab << b << endl;

	Point E(5, 3);//Parametrized constructor
	E.print();

	Point F = E;//CopyConstructor. Здесь мы создаем объект, и инициализируем его другим объектом
	Point G;	//DefaultConstructor
	G = D;	//CopyAssignment - operator=
	G.print();
#endif // CONSTRUCTORS

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	Point A, B, C;
	A = B = C = Point();
#endif // ASSIGNMENT_CHECK

#ifdef DISTANCE
	Point A(2, 3);
	Point B(4, 5);
#ifdef OPERATOR_EXAMPLES
	cout << A + B << endl;	//Неявный вызов оператора '+'
	cout << A.operator+(B) << endl;//Явный вызов оператора '+', перегруженного в классе
	cout << operator+(A, B) << endl;//Явный вызов оператора '+', перегруженного за классом  
#endif // OPERATOR_EXAMPLES


	A.print();
	B.print();
	cout << A.distance(B) << endl;
	cout << distance(A, B) << endl;
	int();
	A.print();
	B.print();
#endif // DISTANCE

}

/*
-------------------------------------
.  - Оператор прямого доступа (Point operator) используется для доступа к полям объекта по имени объекта
-> - Оператор косвенного доступа (Arrow operator) используется для доступа к полям объекта по адресу объекта
this - это указатель на объект, для которого вызывается метод.
-------------------------------------
*/

/*
-------------------------------------
1. Encapsulation - это сокрытие определенной части класса от внешнего мира;
	Модификаторы доступа:
		private: закрытые поля (члены) класса, доступные только изнутри класса
				 и недоступны за его пределами.Здесь обязательно должны находиться ПЕРЕМЕННЫЕ ЧЛЕНЫ КЛАССА!!!
		public:	 открытые поля, доступные из любого места программы, где доступен объект.
				 В public-секции обычно размещают методы.
		protected: использется только при наследовании.
	get/set-методы
	get - взять
	set - задать + отфильтровать некорректные значения.
2. Inheritance;
3. Polymorphism;
-------------------------------------
*/

/*
-------------------------------------
Constructor - это метод, который создает объект.
			  Выделяет память под объект и инициализирует его поля при создании.
Destructor  - это метод, который уничтожает объект по истечении его времени жизни.
~
class Class
{
	Class()
	{
		//Constructor
	}
	~Class()
	{
		//Destructor
	}
};
for(Point A = 0; A < 10; A++)
{

}
if(четотам)
{
	Point A;
	...
	./...
}Здесь точки A уже нет, ее время жизни истекло.
-------------------------------------
*/

/*
------------------------------------------
			OPERATOR OVERLOADS
1) Перегрузить можно только существующие операторы:
	+  - перегружается;
	++ - перегружается;
	*  - перегружаетсяж
	** - НЕ перегружается;
2) Не все существующие операторы можно перегрузить. 
   Не перегружаются:
    :: - scope operator (оператор разрешения видимости);
    ?: - тернарный оператор;
    .  - оператор прямого доступа;
    .* - 
    #  - preprocessor directive
    ## - preprocessor concatenation
3) Перегруженные операторы сохраняют приоритет;
4) Нельзя переопределить поведение операторов со встроенными типами;
------------------------------------------
*/