#include<iostream>
using namespace std;

#define tab "\t"

class Fraction
{
	bool minus;//НУЖНО РЕАЛИЗОВАТЬ!!!
	int integer;	//Целая часть
	int numerator;	//Числитель
	int denominator;//Знаменатель
public:
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

	//			Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "Constructor0:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "Constructor1:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor2:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor3:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//				Methods:
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
};
Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	Fraction result;
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numerator(left.get_numerator()*right.get_denominator() + right.get_numerator()*left.get_denominator());
	result.set_denominator(left.get_denominator()*right.get_denominator());
	result.to_proper();
	return result;
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	return Fraction
	(
		left.get_integer() - right.get_integer(),
		left.get_numerator()*right.get_denominator() - right.get_numerator()*left.get_denominator(),
		left.get_denominator()*right.get_denominator()
	).to_proper();
}
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	).to_proper();
}
Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator()*right.get_denominator(),
		right.get_numerator()*left.get_denominator()
	).to_proper();
}


ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator())os << "(";
	if (obj.get_numerator())os << obj.get_numerator() << "/" << obj.get_denominator();
	if (obj.get_integer() && obj.get_numerator())os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0)os << 0;
	return os;
}

//#define CONSTRUCTOR_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTOR_CHECK
	Fraction A;		//Default constructor
	cout << A << endl;
	Fraction B = 5;	//Single-Argument constructor
	cout << B << endl;
	Fraction C(1, 2);
	cout << C << endl;
	Fraction D(2, 3, 4);
	cout << D << endl;
#endif // CONSTRUCTOR_CHECK

	/*Fraction A(7, 2);
	cout << A << " = " << A.to_proper() << endl;
	cout << A << " = " << A.to_improper() << endl;*/

	/*double a = 2.7;
	double b = 3.5;
	cout << a * b << endl;*/

	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);
	cout << A << tab << B << endl;
	cout << A << " + " << B << " = " << A + B << endl;
	cout << B << " - " << B << " = " << B - B << endl;
	cout << B << " - " << A << " = " << B - A << endl;
	cout << A << " - " << B << " = " << A - B << endl;
	cout << A << " * " << B << " = " << A * B << endl;
	cout << A << " / " << B << " = " << A / B << endl;
	cout << A << tab << B << endl;

}