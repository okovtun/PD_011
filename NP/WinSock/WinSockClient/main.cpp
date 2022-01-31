#include<iostream>
#include<stdio.h>
using namespace std;

/*
-------------------------------------------------------------
1. Инициализация WinSock;
2. Содание сокета;
3. Подключение к серверу;
4. Обмен данными с сервером;
5. Отключение от сервера;
6. Освобождение ресурсов, занимаемых сокетом;
-------------------------------------------------------------
*/

#include<WinSock2.h>
#include<WS2tcpip.h>
# pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	/////////////////////////////////////////////////////////////
	//	1. Инициализация WinSock:				/////////////////
	/////////////////////////////////////////////////////////////
	WSAData wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//MAKEWORD(2,2) версия WinSock
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	/////////////////////////////////////////////////////////////
	//	2. Создание сокета для клиента:				/////////////
	/////////////////////////////////////////////////////////////
	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		//Семейство протоколов unspecified (не указано) можно использовать 
										//как IPv6, так и IPv4
	hints.ai_socktype = SOCK_STREAM;	//Потовыковый сокет, с установкой соединения
	hints.ai_protocol = IPPROTO_TCP;	//Протокол верхнего уровня TCP.

	//Получаем IP-адрес сервера по указанному имени сервера:
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	SOCKET ConnectSocket = INVALID_SOCKET;
	ptr = result;
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	/////////////////////////////////////////////////////////////
	//	3. Подключение к серверу:				/////////////////
	/////////////////////////////////////////////////////////////

	iResult = connect(ConnectSocket, ptr->ai_addr, ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server.\n");
		WSACleanup();
		return 1;
	}

	/////////////////////////////////////////////////////////////
	//	4. Обмен данными с сервером:				/////////////
	/////////////////////////////////////////////////////////////

	int recvbuflen = DEFAULT_BUFLEN;	//размер буфера получения
	const char* sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN]{};

	iResult = send(ConnectSocket, sendbuf, strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("%ld bytes sent\n", iResult);

	//Закрываем сокет на отправку, после этого, мы все еще сможем получать сообщения от сервера, 
	//пока он не закроет соединение:
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	//Получаем данные от сервера, пока он не закроет соединение:
	do
	{
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)printf("%d bytes received\n%s\n", iResult, recvbuf);
		else if (iResult == 0)printf("Connection closed");
		else printf("recv failed: %d", WSAGetLastError());
	} while (iResult > 0);

	/////////////////////////////////////////////////////////////
	//	5. Отключение от сервера:				/////////////////
	/////////////////////////////////////////////////////////////

	closesocket(ConnectSocket);

	/////////////////////////////////////////////////////////////
	//	6. Освобождение ресурсов:				/////////////////
	/////////////////////////////////////////////////////////////
	WSACleanup();
	return 0;
}