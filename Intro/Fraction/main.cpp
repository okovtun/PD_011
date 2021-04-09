#include<iostream>
using namespace std;

#define tab "\t"

#define DEBUG

class Fraction;		//Class declaration - Объявление класса
Fraction operator+(Fraction left, Fraction right);	//Прототип оператора +
Fraction operator-(Fraction left, Fraction right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
class Fraction
{
	int integer;	//Целая часть
	int numerator;	//Числитель
	int denominator;//Знаменатель
	bool minus;//НУЖНО РЕАЛИЗОВАТЬ!!!
	bool plus;
public:
	bool get_minus()const
	{
		return minus;
	}
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_minus(bool minus)
	{
		this->minus = minus;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//////////////////////////////////////////////////////////
	Fraction& set_minus_to_number()
	{
		if (minus)
		{
			integer = -integer;
			numerator = -numerator;
			minus = false;
		}
		return *this;
	}
	Fraction& get_minus_from_number()
	{
		if (integer < 0)
		{
			integer = -integer;
			minus = true;
		}
		if (numerator < 0)
		{
			numerator = -numerator;
			minus = true;
		}
		return *this;
	}
	////////////////////////////////////////////////////////////

	//			Constructors:
	Fraction()
	{
		this->minus = false;
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "Constructor0:\t" << this << endl;
	}
	explicit Fraction(int integer)	//explicit - явный
	{
		this->minus = false;
		this->plus = false;
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		if (integer < 0)
		{
			minus = true;
			this->integer = -integer;
		}
#ifdef DEBUG
		cout << "Constructor1:\t" << this << endl;
#endif // DEBUG
	}
	Fraction(double decimal)
	{
		decimal += 1e-10;
		minus = false;
		if (decimal < 0)
		{
			minus = true;
			decimal = -decimal;
		}
		integer = decimal;
		decimal -= integer;
		denominator = 1e+9;
		numerator = decimal * denominator;
		reduce();
#ifdef DEBUG
		cout << "Constructor double:\t" << this << endl;
#endif // DEBUG

	}
	Fraction(int numerator, int denominator)
	{
		this->minus = false;
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		if (numerator < 0)
		{
			minus = true;
			this->numerator = -numerator;
		}
#ifdef DEBUG
		cout << "Constructor2:\t" << this << endl;
#endif // DEBUG

	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->minus = false;
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		if (integer < 0)
		{
			minus = true;
			this->integer = -integer;
		}
		if (numerator < 0)
		{
			minus = true;
			this->numerator = -numerator;
		}
#ifdef DEBUG
		cout << "Constructor3:\t" << this << endl;
#endif // DEBUG
	}
	~Fraction()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}

	Fraction& operator=(const Fraction& other)
	{
		this->minus = other.minus;
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG
		return *this;
	}

	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//				Increment/Decrement
	Fraction& operator++()
	{
		this->integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		this->integer++;
		return old;
	}

	//				Type cast operators:
	explicit operator int()const
	{
		return minus ? -integer : integer;
	}
	explicit operator double()const
	{
		double number = integer + (double)numerator / denominator;
		if (minus)number = -number;
		return number;
	}

	//				Methods:
	Fraction& to_proper()
	{
		/*if(integer>=0)	integer += numerator / denominator;
		else integer -= numerator / denominator;*/
		get_minus_from_number();
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		get_minus_from_number();
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& reduce()
	{
		if (numerator == 0)return *this;
		int more, less, rest;
		//Выясняем кто больше, числитель, или знаменатель:
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		//Находим наибольший общий делитель:
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;	//Greatest Common Divisor
		//Собственно сокращаем дробь:
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
};
Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	left.set_minus_to_number();
	right.set_minus_to_number();

	Fraction result;
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numerator(left.get_numerator()*right.get_denominator() + right.get_numerator()*left.get_denominator());
	result.set_denominator(left.get_denominator()*right.get_denominator());
	result.to_proper().get_minus_from_number();
	return result.reduce();
}
Fraction operator-(Fraction left, Fraction right)
{
	/*left.to_proper().set_minus_to_number();
	right.to_proper().set_minus_to_number();
	Fraction result
	(
		left.get_integer() - right.get_integer(),
		left.get_numerator()*right.get_denominator() - right.get_numerator()*left.get_denominator(),
		left.get_denominator()*right.get_denominator()
	);
	return result.to_proper().get_minus_from_number().reduce();*/
	left.to_improper().set_minus_to_number();
	right.to_improper().set_minus_to_number();
	return Fraction
	(
		left.get_numerator()*right.get_denominator() - right.get_numerator()*left.get_denominator(),
		left.get_denominator()*right.get_denominator()
	).to_proper().reduce();
}
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper().set_minus_to_number();
	right.to_improper().set_minus_to_number();
	return Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	).to_proper().get_minus_from_number().reduce();
}
Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction result
	(
		left.get_numerator()*right.get_denominator(),
		right.get_numerator()*left.get_denominator()
	);
	result.to_proper();
	if (left.get_minus() || right.get_minus())result.set_minus(true);
	if (left.get_minus() && right.get_minus())result.set_minus(false);
	return result.reduce();
}


ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_minus())os << "(-";
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator())os << "(";
	if (obj.get_numerator())os << obj.get_numerator() << "/" << obj.get_denominator();
	if (obj.get_integer() && obj.get_numerator())os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0)os << 0;
	if (obj.get_minus())os << ")";
	return os;
}

//#define CONSTRUCTOR_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define COMPAUND_ASSIGNMENTS_CHECK
//#define INCREMENTS_CHECK
#define TYPE_CONVERSIONS

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTOR_CHECK
	Fraction A;		//Default constructor
	cout << A << endl;
	Fraction B = -5;	//Single-Argument constructor
	cout << B << endl;
	Fraction C(-1, 2);
	cout << C << endl;
	Fraction D(-2, 3, 4);
	cout << D << endl;
#endif // CONSTRUCTOR_CHECK

	/*Fraction A(7, 2);
	cout << A << " = " << A.to_proper() << endl;
	cout << A << " = " << A.to_improper() << endl;*/

	/*double a = 2.7;
	double b = 3.5;
	cout << a * b << endl;*/

	/*Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);
	cout << A << endl;
	cout << B << endl;*/

#ifdef ARITHMETICAL_OPERATORS_CHECK
	cout << A << tab << B << endl;
	cout << A << " + " << B << " = " << A + B << endl;
	cout << B << " - " << B << " = " << B - B << endl;
	cout << B << " - " << A << " = " << B - A << endl;
	cout << A << " - " << B << " = " << A - B << endl;
	cout << A << " * " << B << " = " << A * B << endl;
	cout << A << " / " << B << " = " << A / B << endl;
	cout << A << tab << B << endl;
#endif // OPERATORS_CHECK

#ifdef COMPAUND_ASSIGNMENTS_CHECK
	A += B;
	cout << A << endl;
	A -= B;
	cout << A << endl;;
	A *= B;
	cout << A << endl;
	A /= B;
	cout << A << endl;
#endif // COMPAUND_ASSIGNMENTS_CHECK

#ifdef INCREMENTS_CHECK
	Fraction reduce(840, 3600);
	cout << reduce.reduce() << endl;
	cout << Fraction(30, 7).reduce() << endl;

	for (double i = .3; i < 10; i++)
		cout << i << tab;
	cout << endl;
	for (Fraction i(1, 2); i.get_integer() < 10; i++)
		cout << i << tab;
	cout << endl;
	cout << typeid(3 + 2.5).name() << endl;
#endif // INCREMENTS_CHECK


#ifdef TYPE_CONVERSIONS
	/*
	-------------------------------------------
	TYPE CONVERSIONS:

	1. From less to more:
	char --> int
	int  --> double

	2. From more to less:	//may cause a loss of data.
	int    --> char
	double --> int
	-------------------------------------------
	*/

	//int a = 2;		//No coversion
	//double b = 2;	//From less to more
	//int c = b;		//From more to less without loosing data
	//double d = 2.5;	//No converion
	//int e = d;		//From more to less with loosing data  

	//Fraction A = (Fraction)5;	//From other to this. Это преобразование выполняет SINGLE ARGUMENT CONSTRUCTOR
	Fraction A(5);	//Если конструктор explicit, то его можно вызвать только так.
	cout << "Fraction A = " << A << endl;
	/*cout << sizeof(int) << endl;
	cout << sizeof(Fraction) << endl;*/
	//Type cast operator
	int a = (int)A;	//From more to less, possible loss of data (operator int)
	cout << "int a = " << a << endl;
	//Type cast operators
	/*
	-----------------------------------------
	Type cast operator syntax:
	operator type()
	{
		.......
		.......
	}
	-----------------------------------------
	*/

	/*Fraction B(-3, 4, 5);
	cout << B << endl;
	double b = (double)B;
	cout << b << endl;

	int c = (int)B;
	cout << c << endl;*/

	Fraction C = 2.3;
	cout << C << endl;
	cout << (double)C << endl;
#endif // TYPE_CONVERSIONS

}