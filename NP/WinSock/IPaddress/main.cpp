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

	//������ ����� GetAdapterAddress() ��� ��������� ��������� pAddress ����� ������� �� �����������.
	DWORD dwRetVal = GetAdaptersAddresses(AF_INET, NULL, NULL, pAddress, &outBufLen);

	if (dwRetVal == NO_ERROR)
	{
		for (PIP_ADAPTER_ADDRESSES pCurAddress = pAddress; pCurAddress; pCurAddress = pCurAddress->Next)
		{
			cout << "Interface Index:\t" << pCurAddress->IfIndex << endl;
			cout << "Interface name:\t" << pCurAddress->AdapterName << endl;
			wcout << "Description:\t" << pCurAddress->Description << endl;

			DWORD dwAddressStringLength = 256;	//������ ������, ���������� IP-�����
			//Unicast	- ���������� �����, ������� ����������� ���������� (������� �����)
			//Broadcast	- ����������������� �����, �� ����� ���� �������� ����������, 
			//			  ������������ � ����������������� IP-������.
			//Multicast - ��������� ������, ����������� ������ �����, ��� ������� ���������� ������� ������.
			//ncpa.cpl

			//		������ �� ������ Unicast-������� �������� �������� (pCurAddress):
			for (PIP_ADAPTER_UNICAST_ADDRESS_LH pUnicast = pCurAddress->FirstUnicastAddress; pUnicast; pUnicast = pUnicast->Next)
			{
				//�������� ������ ��� ������, � ������� ����� �������� ���������� IP-�����.
				LPSTR lpszAddressString = (LPSTR)HeapAlloc(GetProcessHeap(), 0, dwAddressStringLength);
				//������������ ����� � �������-���������� �������:
				WSAAddressToString(pUnicast->Address.lpSockaddr, pUnicast->Address.iSockaddrLength, NULL, lpszAddressString, &dwAddressStringLength);
				//����� W � ����� �������, ��� ���� ������ �������� WIDE_CHAR (w_char_t) - ������� � ��������� Unicode

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
					cout.width(2);	//������ ������ ���� ��� ������
					cout.fill('0');	//��������� ������ ����� � ���������� ���� �������� ��������
					cout << hex << (int)pCurAddress->PhysicalAddress[i];
					if(i!=pCurAddress->PhysicalAddressLength-1)cout << ":";
				}
			}
			cout << "\n----------------------------------------------------------\n";
		}
	}

	HeapFree(GetProcessHeap(), 0, pAddress);

	//������� �����:
	WSACleanup();
}