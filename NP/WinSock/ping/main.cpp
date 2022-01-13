#include<WinSock2.h>
#include<iphlpapi.h>
#include<iostream>
#include"rawping.h"

using namespace std;

//загружаем статические библиотеки:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#define DEFAULT_PACKET_SIZE		32
#define DEFAULT_TTL				30		//IP header TTL
#define MAX_PING_DATA_SIZE		1024	//
#define MAX_PING_PACKET_SIZE	(MAX_PING_DATA_SIZE + sizeof(IPHeader))

int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf, int packet_size);
int cleanup(ICMPHeader*& send_buf, IPHeader*& recv_buf);

int main(int argc, char** argv)
{
	using namespace std;
	//argc (Argument Count) - количество аргументов, переданных программе из комендной строки
	//argv[]	- массив строк, каждая из которых содержит один параметр командной строки
	//Нулевой элемент массива argv[] всегда содердит имя *.exe файла.

	if (argc < 2)
	{
		cerr << "Wrong sytax" << endl;
		return 1;
	}

	int seq_num = 0;
	ICMPHeader* send_buf = 0;
	IPHeader* recv_buf = 0;
	int packet_size = MAX_PING_DATA_SIZE;
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
	if (setup_for_ping(argv[1], ttl, sd, dst) < 0)
	{
		cerr << "Setup for ping failed" << endl;
		return cleanup(send_buf, recv_buf);
	}

	if (allocate_buffers(send_buf, recv_buf, packet_size) < 0)
	{
		return cleanup(send_buf, recv_buf);
	}
	init_ping_packet(send_buf, packet_size, seq_num);
	//Отправка запроса и получение ответа
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
}
int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf,  int packet_size)
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