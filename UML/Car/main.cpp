#include<iostream>
#include<conio.h>
#include<thread>
using namespace std;
using namespace std::literals::chrono_literals;

const unsigned int DEFAULT_TANK_VOLUME = 60;
const unsigned int MIN_FUEL_LEVEL = 5;
const double DEFAULT_ENGINE_CONSUMPTION = 8;
const unsigned int DEFAULT_MAX_SPEED = 250;

enum Keys
{
	Escape = 27,
	Enter = 13,
	Space = 32,
	ArrowUp = 72,
	ArrowDown = 80,
	ArrowLeft = 75,
	ArrowRight = 77
};

class Tank
{
	//Топливный бак:
	const unsigned int VOLUME;	//объем бака
	double fuel_level;			//уровень топлива
public:
	unsigned int get_volume()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(double amount)
	{
		//amount - количество топлива
		if (amount < 0)return;
		if (fuel_level + amount < VOLUME)fuel_level += amount;
		else fuel_level = VOLUME;
	}
	double give_fuel(double amount)
	{
		if (fuel_level - amount > 0)fuel_level -= amount;
		else fuel_level = 0;
		return fuel_level;
	}
	Tank(const unsigned int VOLUME) :VOLUME(VOLUME >= 20 && VOLUME <= 80 ? VOLUME : DEFAULT_TANK_VOLUME), fuel_level(0)
	{
		cout << "Tank is ready\t" << this << endl;
	}
	~Tank()
	{
		cout << "Tank is over\t" << this << endl;
	}
	void info()const
	{
		cout << "Tank volume: " << VOLUME << " liters\n";
		cout << "Fuel level:  " << fuel_level << " liters\n";
	}
};

class Engine
{
	//Этот класс описывает двигатель

	const double CONSUMPTION;	//расход 100 км.
	double consumtion_per_second;	//расход за одну секунду

	bool started;

public:
	const double get_consumption()const
	{
		return CONSUMPTION;
	}
	double get_consumption_per_second()const
	{
		return consumtion_per_second;
	}
	bool is_started()const
	{
		return started;
	}
	void start()
	{
		started = true;
	}
	void stop()
	{
		started = false;
	}
	Engine(double consumption) :CONSUMPTION(consumption >= 4 && consumption <= 25 ? consumption : DEFAULT_ENGINE_CONSUMPTION)
	{
		this->consumtion_per_second = this->CONSUMPTION*5e-5;
		started = false;
		cout << "Engine is ready\t" << this << endl;
	}
	~Engine()
	{
		cout << "Engine is over\t" << this << endl;
	}
	void info()const
	{
		cout << "Engine consumes " << CONSUMPTION << " liters per 100 km" << endl;
		cout << "Engine consumes " << consumtion_per_second << " liters per 1 second in idle" << endl;
		cout << "Engine is " << (started ? "started" : "stopped") << endl;
	}
};

class Car
{
	Tank tank;
	Engine engine;
	unsigned int speed;	//текущая скорость
	unsigned int MAX_SPEED;

	bool driver_inside;

	struct Control
	{
		std::thread main_thread;
		std::thread panel_thread;
		std::thread idle_thread;
	}control;
public:
	/*Car(unsigned int MAX_SPEED) :
		speed(0),
		MAX_SPEED(MAX_SPEED >= 100 && MAX_SPEED <= 350 ? MAX_SPEED : DEFAULT_MAX_SPEED),
		engine(this->MAX_SPEED / 15),
		tank(this->MAX_SPEED / 5)
	{
		cout << "Your car is ready to go. Press Enter to get in." << this << endl;
	}*/
	Car(double engine_consumption, unsigned int tank_volume, unsigned int MAX_SPEED = DEFAULT_MAX_SPEED) :
		engine(engine_consumption),
		tank(tank_volume),
		speed(0),
		MAX_SPEED(MAX_SPEED >= 100 && MAX_SPEED <= 350 ? MAX_SPEED : DEFAULT_MAX_SPEED),
		driver_inside(false)
	{
		cout << "Your car is ready to go. Press Enter to get in." << this << endl;
	}
	~Car()
	{
		cout << "Your car is over :-(" << this << endl;
	}
	void get_in()
	{
		driver_inside = true;
		control.panel_thread = thread(&Car::panel, this);	//Запускаем метод panel в потоке
	}
	void get_out()
	{
		driver_inside = false;
		if (control.panel_thread.joinable())control.panel_thread.join();	//Останавливаем поток, отображающий панель приборов
	}
	void panel() const
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Engine is " << (engine.is_started() ? "started" : "stopped") << endl;
			cout << "Fuel level: " << tank.get_fuel_level() << " liters";
			if (tank.get_fuel_level() < MIN_FUEL_LEVEL)cout << "LOW FUEL";
			cout << endl;
			cout << "Speed: " << speed << " km/h" << endl;
			std::this_thread::sleep_for(1s);
		}
		system("CLS");
		cout << "This is your car, press Enter to get in" << endl;
	}
	void control_car()
	{
		char key;
		do
		{
			key = _getch();
			//cout << (int)key << "\t" << key << endl;
			switch (key)
			{
			case Enter:	//Вход/Выход из машины
				if (driver_inside)get_out();
				else get_in();
				break;
			case 'F':case 'f'://Fill - заправка
				double amount;
				cout << "How much?"; cin >> amount;
				tank.fill(amount);
				break;
			case 'I':case 'i'://Ignition - зажигание.
				break;
			case 'W':case 'w':case ArrowUp://Gas - газ, разгон
				break;
			case ArrowDown:case Space:case 'S':case 's':
				break;
			case Escape:
				get_out();
			}
		} while (key != Escape);
	}
	void info()const
	{
		tank.info();
		cout << endl;
		engine.info();
		cout << endl;
		cout << "Max speed:\t" << MAX_SPEED << " km/h" << endl;;
		cout << "Current speed: " << speed << " km/h" << endl;;
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef TANK_CHECK
	Tank tank(11);
	tank.info();
	tank.fill(3);
	tank.info();
	tank.fill(30);
	tank.info();
	tank.fill(30);
	tank.info();
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(6);
	engine.info();
	engine.start();
	engine.info();
#endif // ENGINE_CHECK

	Car car(8, 40);
	car.info();
	car.control_car();
}