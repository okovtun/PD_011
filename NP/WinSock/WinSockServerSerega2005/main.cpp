#define _CRT_SECURE_NO_WARNINGS
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif // WIN32_LIN_AND_MEAN

#include<iostream>
#include<stdio.h>
using namespace std;

//#include<Windows.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	//////////////////////////////////////////////
	// 1.Инициализация WinSock
	//////////////////////////////////////////////

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	//////////////////////////////////////////////
	// 2.Создание сокета:
	//////////////////////////////////////////////

	struct  addrinfo* result = NULL;
	struct  addrinfo* ptr = NULL;
	struct  addrinfo hints;

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

	///////////////////////////////////////////////////
	// 3.привязка сокета к IP-адресу:
	////////////////////////////////////////////////////

	iResult = bind(ListenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	///////////////////////////////////////////////////
	// 4.Прослушивание порта:
	////////////////////////////////////////////////////

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("Listen failed: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	///////////////////////////////////////////////////
	// 5.Прием соединений от клиентов:
	////////////////////////////////////////////////////

	SOCKET ClientSocket = INVALID_SOCKET;
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	///////////////////////////////////////////////////
	// 6.Получение и отправка данных:
	///////////////////////////////////////////////////

	char recvbuffer[DEFAULT_BUFLEN]{};
	int iSendResult = 0;
	int recvBufLen = DEFAULT_BUFLEN;
	do
	{
		iResult = recv(ClientSocket, recvbuffer, recvBufLen, 0);
		if (iResult > 0)
		{
			printf("%d Bytes received\n", iResult);
			printf("%s\n", recvbuffer);
			strcat(recvbuffer, " received");

			//отправляем полученный буффер обратно клиенту:
			iSendResult = send(ClientSocket, recvbuffer, iResult, 0);
			if (iSendResult == SOCKET_ERROR)
			{
				printf("send failed: %d", WSAGetLastError());
				closesocket(ListenSocket);
				WSACleanup();
				return 1;
			}
			printf("%d Bytes sent.\n", iSendResult);
		}
		else if (iResult == 0)
		{
			printf("Connection closing...\n");
		}
		else
		{
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);

	///////////////////////////////////////////////////
	// 7. Отключение сервера:
	///////////////////////////////////////////////////

	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	closesocket(ClientSocket);



	closesocket(ListenSocket);
	WSACleanup();
	return 0;
}