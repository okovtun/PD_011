#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<map>
#include<algorithm>
#include<Windows.h>

const std::string base_name = "base.txt";

void print_base(const std::map<std::string, std::list<std::string>>& base);
void save_base(const std::map<std::string, std::list<std::string>>& base);
void load_base(std::map<std::string, std::list<std::string>>& base);

void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 120,50 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);

	std::map<std::string, std::list<std::string>> base/* =
	{
		std::pair<std::string, std::list<std::string>>("m123ru777", {"Проезд на красный", "Привышение скорости"}),
		std::pair<std::string, std::list<std::string>>("m446rs011", {"Парковка в неположенном месте"}),
		std::pair<std::string, std::list<std::string>>("k848vk011", {"Езда в нетрезвом состоянии", "Оскорбление сотрудника полиции", "Оказание сопротивления при аресте"}),
	}*/;
	load_base(base);
	print_base(base);
	/*for (std::list<std::string>::iterator it = base["k848vk011"].begin(); it != base["k848vk011"].end(); it++)
		std::cout << *it << "\n";
	std::cout << std::endl;*/
	//save_base(base);
}

void print_base(const std::map<std::string, std::list<std::string>>& base)
{
	for (std::map<std::string, std::list<std::string>>::const_iterator it = base.begin(); it != base.end(); it++)
	{
		std::cout << it->first << ":\t";
		for (std::list<std::string>::const_iterator l_it = it->second.begin(); l_it != it->second.end(); l_it++)
		{
			std::cout << *l_it;// << ", ";
			if (l_it != --(it->second.end()))std::cout << ", ";
		}
		/*std::cout << "\b \b";
		std::cout << "\b \b;\n";*/
		std::cout << ";\n";
	}
}
void save_base(const std::map<std::string, std::list<std::string>>& base)
{
	std::ofstream fout(base_name);
	for (std::map<std::string, std::list<std::string>>::const_iterator it = base.begin(); it != base.end(); it++)
	{
		fout << it->first << ":";
		for (std::list<std::string>::const_iterator l_it = it->second.begin(); l_it != it->second.end(); l_it++)
		{
			fout << *l_it;// << ", ";
			if (l_it != --(it->second.end()))fout << ",";
		}
		/*fout << "\b \b";
		fout << "\b \b;\n";*/
		fout << ";\n";
	}
	fout.close();
	std::string command = "start notepad " + base_name;
	system(command.c_str());
}

void load_base(std::map<std::string, std::list<std::string>>& base)
{
	std::ifstream fin(base_name);
	std::string id;
	//std::string crime;
	std::string crimes;
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::getline(fin, id, ':');
			//if (id.size() < 2)continue;
			/*while (std::getline(fin, crime, ','))
			{
				base[id].push_back(crime);
			}*/
			std::getline(fin, crimes, ';');
			fin.ignore();
			for (int i = 0, next_comma = i; i < crimes.size(); i = next_comma)
			{
				next_comma = crimes.find(',', i+1);
				std::string crime(crimes, i+1, (next_comma>0?next_comma - i - 1:crimes.size()-i));
				base[id].push_back(crime);
			}
		}
	}
	else
	{
		std::cerr << "File not found" << std::endl;
	}
	fin.close();
}