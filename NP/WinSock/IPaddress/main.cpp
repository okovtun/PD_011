#define _WINSOCK_DEPRECATED_NO_WARNINGS
#ifdef UNICODE
#undef UNICODE
#endif

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

	//Второй вызов GetAdapterAddress() уже заполняет структуру pAddress всеми данными об интерфейсах.
	DWORD dwRetVal = GetAdaptersAddresses(AF_INET, NULL, NULL, pAddress, &outBufLen);

	if (dwRetVal == NO_ERROR)
	{
		for (PIP_ADAPTER_ADDRESSES pCurAddress = pAddress; pCurAddress; pCurAddress = pCurAddress->Next)
		{
			cout << "Interface Index:\t" << pCurAddress->IfIndex << endl;
			cout << "Interface name:\t" << pCurAddress->AdapterName << endl;
			wcout << "Description:\t" << pCurAddress->Description << endl;

			DWORD dwAddressStringLength = 256;	//Размер строки, содержащей IP-адрес
			//Unicast	- уникальный адрес, который назначается интерфейсу (сетевая карта)
			//Broadcast	- широковещательный адрес, НЕ может быть назначен интерфейсу, 
			//			  вкладывается в широковещательный IP-пакеты.
			//Multicast - групповые адреса, назначаются группе узлов, как правило протоколом высшего уровня.
			//ncpa.cpl

			//		Проход по списку Unicast-адресов текущего адаптера (pCurAddress):
			for (PIP_ADAPTER_UNICAST_ADDRESS_LH pUnicast = pCurAddress->FirstUnicastAddress; pUnicast; pUnicast = pUnicast->Next)
			{
				//Выделяем память для строки, в которой будет хранится полученный IP-адрес.
				LPSTR lpszAddressString = (LPSTR)HeapAlloc(GetProcessHeap(), 0, dwAddressStringLength);
				//Представляем адрес в точечно-десятичной нотации:
				WSAAddressToString(pUnicast->Address.lpSockaddr, pUnicast->Address.iSockaddrLength, NULL, lpszAddressString, &dwAddressStringLength);
				//Буква W в имени функции, или типа данных означает WIDE_CHAR (w_char_t) - символы в кодировке Unicode

				/*cout << "\tIP address:\t" << lpszAddressString;
				wcout << "/" << pUnicast->OnLinkPrefixLength << endl;*/
				//wcout << "\tSubnet prefix:\t" << pUnicast->OnLinkPrefixLength << endl;	
				printf("\tIP address:\t%s/%d\n", lpszAddressString, pUnicast->OnLinkPrefixLength);
				//%s - string
				//TODO:
				/*ULONG lMask = 0;
				if (ConvertLengthToIpv4Mask(pUnicast->OnLinkPrefixLength, &lMask) == NO_ERROR)
				{
					cout << "\tSubnet mask: " << lMask << endl;
				}*/

				HeapFree(GetProcessHeap(), 0, lpszAddressString);
			}

			if (pCurAddress->PhysicalAddressLength)
			{
				cout << "Phisical address (MAC): ";
				for (int i = 0; i < pCurAddress->PhysicalAddressLength; i++)
				{
					cout.width(2);	//Задает ширину поля для вывода
					cout.fill('0');	//Заполняет пустое место в выделенном поле заданным символом
					cout << hex << (int)pCurAddress->PhysicalAddress[i];
					if(i!=pCurAddress->PhysicalAddressLength-1)cout << ":";
				}
			}
			cout << "\n----------------------------------------------------------\n";
		}
	}

	HeapFree(GetProcessHeap(), 0, pAddress);

	//Удаляем сокет:
	WSACleanup();
}