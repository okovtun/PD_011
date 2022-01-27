//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
#include<iostream>
#include<stdio.h>
using namespace std;

//#include<Windows.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"

/*
---------------------------------------------------------
	1. Инициализация WinSock;
	2. Создание сокета;
	3. Привязка сокета к определенному интерфейсу (IP-адресу);
	4. Прослушивание порта;
	5. Прием соединений от клиентов;
	6. Получение и отправка данных;
	7. Отключение;
---------------------------------------------------------
*/

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	/////////////////////////////////////////////////////////////
	//	1. Инициализация WinSock:				/////////////////
	/////////////////////////////////////////////////////////////

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	/////////////////////////////////////////////////////////////
	//	2. Создание сокета:						/////////////////
	/////////////////////////////////////////////////////////////

	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("geaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("socket() failed: %ld", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	/////////////////////////////////////////////////////////////
	//	3. Привязка сокета к IP-адресу:			/////////////////
	/////////////////////////////////////////////////////////////

	iResult = bind(ListenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	/////////////////////////////////////////////////////////////
	//	4. Прослушивание порта:					/////////////////
	/////////////////////////////////////////////////////////////

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("Listen failed: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;
}