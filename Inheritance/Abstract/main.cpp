#include<iostream>
using namespace std;

#define delimiter "\n-----------------------------------------------\n"

class Vehicle	//Абстрактный класс
{
	int speed;
public:
	virtual void move() = 0;	//Чисто виртуальная функция
};

class AirVehicle :public Vehicle	//Тоже абстрактный класс
{
	int height;
public:
	virtual void takeoff() = 0;
	virtual void land() = 0;
};

class Airplain :public AirVehicle	//Конкретный класс
{
public:
	void move()
	{
		cout << "Летит по воздуху" << endl;
	}
	void takeoff()
	{
		cout << "Для взлета нужна взлетная полоса" << endl;
		cout << "Взлетаем" << endl;
	}
	void land()
	{
		cout << "Для посадки нужна влетная полоса" << endl;
		cout << "Захожу на посадку" << endl;
	}
};

class HeliCopter :public AirVehicle
{
public:
	void takeoff()
	{
		cout << "Могу взлететь где угодно" << endl;
	}
	void move()
	{
		cout << "Плавненько перемещаюсь по воздуху" << endl;
	}
	void land()
	{
		cout << "Могу сесть хоть в поле" << endl;
	}
};

class LandVehicle :public Vehicle
{

};

class Car :public LandVehicle
{
public:
	void move()
	{
		cout << "Едет по дороге на четырех колесах" << endl;
	}
};

class Bike :public LandVehicle
{
public:
	void move()
	{
		cout << "Едет по дороге на двух колесах" << endl;
	}
};

class WaterVehicle :public Vehicle
{
public:
	void move()
	{
		cout << "Плывет по воде" << endl;
	}
};

class Boat :public WaterVehicle
{
public:

};

void main()
{
	setlocale(LC_ALL, "");
	//Vehicle v;	//Невозможно создать экземпляр абстрактоного класса
	//AirVehicle av;//Этот класс так же является абстрактным, 
					//поскольку наследует чисто виртуальный метод move(),
					//и не реализует его
	Airplain plain;
	plain.takeoff();
	plain.move();
	plain.land();
	
	cout << delimiter << endl;

	HeliCopter chopper;
	chopper.takeoff();
	chopper.move();
	chopper.land();

	cout << delimiter << endl;

	Car car;
	car.move();

	Bike bike;
	bike.move();

	cout << delimiter << endl;

	Boat boat;
	boat.move();
}