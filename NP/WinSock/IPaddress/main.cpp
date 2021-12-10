#include<iostream>
#include<WinSock2.h>
#include<iphlpapi.h>

using namespace std;
//WinSock - Windows Socket

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

void main()
{
	setlocale(LC_ALL, "");
	//1) Инициализация WinSock:
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//MAKEWORD(2,2) задает желаемую версию WinSock - 2.2
	if (iResult != 0)
	{
		cout << "Инициализация не удалась" << endl;
		return;
	}

	////////////////////////////////////////////////////////////

	//Определим IP-адреса интерфейсов:
	ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
	PIP_ADAPTER_ADDRESSES pAddress = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, outBufLen);//Выделяет память, как оператор new
	//IP_ADAPTER_ADDRESS - это список интерфейсов в системе со всеми их свойствами.

	//Получаем список интерфейсов:
	//Первый вызов GetAdapterAddress нужен для определения размера буфера outBufLen
	if (GetAdaptersAddresses(AF_INET, NULL, NULL, pAddress, &outBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		HeapFree(GetProcessHeap(), 0, pAddress);//И для последующего выделения памяти
		pAddress = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, outBufLen);
	}
	if (pAddress == NULL)
	{
		cout << "Память не выделена" << endl;
		return;
	}

	//Второй вызов GetAdapterAddress() уже заолняет структуру pAddress всеми данными об интерфейсах.
	GetAdaptersAddresses(AF_INET, NULL, NULL, pAddress, &outBufLen);

	HeapFree(GetProcessHeap(), 0, pAddress);

	//Удаляем сокет:
	WSACleanup();
}