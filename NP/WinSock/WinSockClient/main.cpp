#include<iostream>
#include<stdio.h>
using namespace std;

/*
-------------------------------------------------------------
1. ������������� WinSock;
2. ������� ������;
3. ����������� � �������;
4. ����� ������� � ��������;
5. ���������� �� �������;
6. ������������ ��������, ���������� �������;
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
	//	1. ������������� WinSock:				/////////////////
	/////////////////////////////////////////////////////////////
	WSAData wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//MAKEWORD(2,2) ������ WinSock
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	/////////////////////////////////////////////////////////////
	//	2. �������� ������ ��� �������:				/////////////
	/////////////////////////////////////////////////////////////
	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		//��������� ���������� unspecified (�� �������) ����� ������������ 
										//��� IPv6, ��� � IPv4
	hints.ai_socktype = SOCK_STREAM;	//����������� �����, � ���������� ����������
	hints.ai_protocol = IPPROTO_TCP;	//�������� �������� ������ TCP.

	//�������� IP-����� ������� �� ���������� ����� �������:
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
	//	3. ����������� � �������:				/////////////////
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
	//	4. ����� ������� � ��������:				/////////////
	/////////////////////////////////////////////////////////////

	int recvbuflen = DEFAULT_BUFLEN;	//������ ������ ���������
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

	//��������� ����� �� ��������, ����� �����, �� ��� ��� ������ �������� ��������� �� �������, 
	//���� �� �� ������� ����������:
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	//�������� ������ �� �������, ���� �� �� ������� ����������:
	do
	{
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)printf("%d bytes received\n%s\n", iResult, recvbuf);
		else if (iResult == 0)printf("Connection closed");
		else printf("recv failed: %d", WSAGetLastError());
	} while (iResult > 0);

	/////////////////////////////////////////////////////////////
	//	5. ���������� �� �������:				/////////////////
	/////////////////////////////////////////////////////////////

	closesocket(ConnectSocket);

	/////////////////////////////////////////////////////////////
	//	6. ������������ ��������:				/////////////////
	/////////////////////////////////////////////////////////////
	WSACleanup();
	return 0;
}