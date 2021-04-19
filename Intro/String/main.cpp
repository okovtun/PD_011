#include"String.h"

//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK
//#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str;
	str.print();

	//String str2 = 5;	//
	String str2(5);
	str2.print();

	cout << typeid("Hello").name() << endl;
	String str3 = "Hello";
	str3.print();
	cout << str3 << endl;

	String str4 = str3;	//CopyConstructor
	cout << "Str4 - " << str4 << endl;

	String str5;
	str5 = str4;
	cout << "Str5 - " << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	String str1 = "Hello";
	String str2;
	str1 = str1;
	cout << str1 << endl;
	cout << str2 << endl;

	char a = '5';
	a = a;
	cout << a << endl;
#endif // ASSIGNMENT_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3;
	str3 = str1 + str2;//Оператор + будет выполнять конкатенацию (слияние) строк
	cout << delimiter << endl;
	cout << str3 << endl;
	/*cout << delimiter << endl;
	str1 += str2;
	cout << str1 << endl;
	cout << delimiter << endl;*/

	int arr[5];
	for (int i = 0; i < 5; i++)
	{
		arr[i] = rand() % 100;
	}
#endif // OPERATOR_PLUS_CHECK

	String str1;	//Default constructor
	str1.print();
	String str2 = "Hello";	//Single argument constructor
	str2.print();
	String str3("World");	//Single argument constructor
	str3.print();
	String str4();	//Объявление функции str4, которая ничего не принимает, 
					//и возвращает значение типа String.
					//String str4(); НЕ вызывает конструктор по умолчанию
	String str5{};	//Явно вызывается конструктор по умолчанию
	str5.print();
	String str6{7};
	str6.print();
	String str7{ "Привет" };
	str7.print();
	String str8 = str7;
	str8.print();
	cout << delimiter << endl;
	cout << str2 + str3 << endl;
	cout << delimiter << endl;
}