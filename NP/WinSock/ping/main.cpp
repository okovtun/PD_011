#include<WinSock2.h>
#include<iostream>

//загружаем статические библиотеки:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#define DEFAULT_PACKET_SIZE		32
#define DEFAULT_TTL				30		//IP header TTL
#define MAX_PING_DATA_SIZE		1024	//
#define MAX_PING_PACKET_SIZE	(MAX_PING_DATA_SIZE + sizeof(IPHeader))

int main(int argc, char** argv)
{
	//argc (Argument Count) - количество аргументов, переданных программе из комендной строки
	//argv[]	- массив строк, каждая из которых содержит один параметр командной строки
	//Нулевой элемент массива argv[] всегда содердит имя *.exe файла.
}