#include<WinSock2.h>
#include<iphlpapi.h>
#include<iostream>
#include"rawping.h"

using namespace std;

//загружаем статические библиотеки:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#define DEFAULT_PACKET_SIZE		32
#define DEFAULT_TTL				128		//IP header TTL
#define MAX_PING_DATA_SIZE		1024	//
//#define MAX_PING_DATA_SIZE		SHRT_MAX-20	//
#define MAX_PING_PACKET_SIZE	(MAX_PING_DATA_SIZE + sizeof(IPHeader))

int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf, int packet_size);
int cleanup(ICMPHeader*& send_buf, IPHeader*& recv_buf);
int ping(char* address, int n, int buffer_size);

int main(int argc, char** argv)
{
	using namespace std;
	setlocale(LC_ALL, "");
	//argc (Argument Count) - количество аргументов, переданных программе из комендной строки
	//argv[]	- массив строк, каждая из которых содержит один параметр командной строки
	//Нулевой элемент массива argv[] всегда содердит имя *.exe файла.

	if (argc < 2)
	{
		cerr << "Wrong sytax" << endl;
		return 1;
	}
	//------------------------------------------
	char* address = nullptr;
	int count = 4;
	int buffer_size = DEFAULT_PACKET_SIZE;
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
		//	ADRESS
		if (strrchr(argv[i], '.'))address = argv[i];

		//NUMBER OF REQUESTS
		if (strcmp(argv[i], "-n") == 0)
		{
			count = atoi(argv[i + 1]);//Преобразуем следующий параметр в число
			if (count < 0)
			{
				cout << "Wrong ping count" << endl;
				return -1;
			}
		}

		//SEND BUFFER SIZE
		if (strcmp(argv[i], "-l") == 0)
		{
			if (atoi(argv[i + 1]) >= DEFAULT_PACKET_SIZE && atoi(argv[i + 1]) <= MAX_PING_DATA_SIZE)
			{
				buffer_size = atoi(argv[i + 1]);
			}
			else
			{
				cout << atoi(argv[i + 1]) << " - Неверный размер буфера, разрешенные значения от "
					<< DEFAULT_PACKET_SIZE << " до " << MAX_PING_DATA_SIZE << ", принят размер по умолчанию\n";
			}
		}
	}

	ping(address, count, buffer_size);
}
int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf, int packet_size)
{
	send_buf = (ICMPHeader*)new char[packet_size] {};
	recv_buf = (IPHeader*)new char[MAX_PING_PACKET_SIZE] {};
	if (send_buf == 0)
	{
		cerr << "Failed to allocate send buffer" << endl;
		return -1;
	}
	if (recv_buf == 0)
	{
		cerr << "Receive buffer allocation failed" << endl;
		return -1;
	}
	return 0;
}
int cleanup(ICMPHeader*& send_buf, IPHeader*& recv_buf)
{
	delete[] send_buf;
	delete[] recv_buf;
	send_buf = nullptr;
	recv_buf = nullptr;
	WSACleanup();
	return 0;
}
int ping(char* address, int n, int buffer_size)
{
	int seq_num = 0;
	ICMPHeader* send_buf = 0;
	IPHeader* recv_buf = 0;
	int packet_size = buffer_size;
	int ttl = DEFAULT_TTL;

	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
	{
		cerr << "Failed to find Winsock 2.1 or better" << endl;
		return 1;
	}

	SOCKET sd;
	sockaddr_in src, dst;
	//src - source_ip (адрес источника)
	//dst - destination_ip (адрес получателя
	if (setup_for_ping(address, ttl, sd, dst) < 0)
	{
		cerr << "Setup for ping failed" << endl;
		return cleanup(send_buf, recv_buf);
	}

	if (allocate_buffers(send_buf, recv_buf, packet_size) < 0)
	{
		return cleanup(send_buf, recv_buf);
	}
	for (size_t i = 0; i < n; i++)
	{
		init_ping_packet(send_buf, packet_size, i);
		//Отправка запроса и получение ответа

			//send_buf->timestamp = GetTickCount();
			//send_buf->checksum = ip_checksum((USHORT*)send_buf, packet_size);
		if (send_ping(sd, dst, send_buf, packet_size) >= 0)
		{
			while (true)
			{
				if (recv_ping(sd, src, recv_buf, MAX_PING_PACKET_SIZE) < 0)
				{
					unsigned short header_len = recv_buf->h_len * 4;
					ICMPHeader* icmphdr = (ICMPHeader*)((char*)recv_buf + header_len);
					if (icmphdr->seq != seq_num)
					{
						cerr << "bad sequence number!" << endl;
						continue;
					}
					else
					{
						break;
					}
				}
				if (decode_reply(recv_buf, packet_size, &src) != -2)break;
			}
		}
		Sleep(1000);
	}
	return cleanup(send_buf, recv_buf);
}