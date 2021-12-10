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
	//1) ������������� WinSock:
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//MAKEWORD(2,2) ������ �������� ������ WinSock - 2.2
	if (iResult != 0)
	{
		cout << "������������� �� �������" << endl;
		return;
	}

	////////////////////////////////////////////////////////////

	//��������� IP-������ �����������:
	ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
	PIP_ADAPTER_ADDRESSES pAddress = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, outBufLen);//�������� ������, ��� �������� new
	//IP_ADAPTER_ADDRESS - ��� ������ ����������� � ������� �� ����� �� ����������.

	//�������� ������ �����������:
	//������ ����� GetAdapterAddress ����� ��� ����������� ������� ������ outBufLen
	if (GetAdaptersAddresses(AF_INET, NULL, NULL, pAddress, &outBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		HeapFree(GetProcessHeap(), 0, pAddress);//� ��� ������������ ��������� ������
		pAddress = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, outBufLen);
	}
	if (pAddress == NULL)
	{
		cout << "������ �� ��������" << endl;
		return;
	}

	//������ ����� GetAdapterAddress() ��� �������� ��������� pAddress ����� ������� �� �����������.
	GetAdaptersAddresses(AF_INET, NULL, NULL, pAddress, &outBufLen);

	HeapFree(GetProcessHeap(), 0, pAddress);

	//������� �����:
	WSACleanup();
}