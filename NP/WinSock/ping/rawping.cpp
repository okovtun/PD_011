#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>

#include"rawping.h"
#include"ip_checksum.h"

extern int setup_for_ping(char* host, int ttl, SOCKET& sd, sockaddr_in& dest)
{
	using namespace std;
	//Create socket:
	sd = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, 0, 0);
	//AF_INET - семейство протоколов IPv4
	//SOCK_RAW 
	if (sd == INVALID_SOCKET)
	{
		//cout - Console Out
		//cerr - Console Error
		cerr << "Invalid socket: " << WSAGetLastError() << endl;
		return -1;
	}

	if (setsockopt(sd, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl)) == SOCKET_ERROR)
	{
		cerr << "TTL sockopt failed: " << WSAGetLastError() << endl;
		return -1;
	}

	//Инициализируем хост получатель:
	memset(&dest, 0, sizeof(dest));

	unsigned int addr = inet_addr(host);	//Получаем адрес пингуемого хоста (узла)
	if (addr != INADDR_NONE)	//Если полученное число является адресом
	{
		//Записываем этот адрес в получатеся
		dest.sin_addr.s_addr = addr;
		dest.sin_family = AF_INET;	//IPv4
	}
	else
	{
		//В противном случае, предполагаем что host задан по имени, и пытаемся разрешить имя в адрес:
		hostent* hp = gethostbyname(host);
		if (hp != 0)
		{
			//Если имя разрешилось в IP-адрес, записываем этот адрес в dest
			memcpy(&dest.sin_addr, hp->h_addr, hp->h_length);
			dest.sin_family = hp->h_addrtype;
		}
		else
		{
			//Имя НЕ разрешилось в адрес
			cerr << "Failed to resolve " << host << endl;
			return -1;
		}
	}
	return 0;
}
extern void init_ping_packet(ICMPHeader* icmp_hdr, int packet_size, int seq_no)
{
	//Инициализируем поля ICMP-заголовка:
	icmp_hdr->type = ICMP_ECHO_REQUEST;
	icmp_hdr->code = 0;
	icmp_hdr->checksum = 0;
	icmp_hdr->id = (USHORT)GetCurrentProcessId();	//Для того, чтобы отличать ICMP-сообщения, 
													//если запущено несколько экземплярв программы
	icmp_hdr->seq = seq_no;
	icmp_hdr->timestamp = GetTickCount();

	const unsigned int dead = 0xDEADBEEF;
	char* deadpart = (char*)icmp_hdr + sizeof(ICMPHeader);
	int bytes_left = packet_size - sizeof(ICMPHeader);
	while (bytes_left)
	{
		memcpy(deadpart, &dead, min(sizeof(dead), bytes_left));
		bytes_left -= sizeof(dead);
		deadpart += sizeof(dead);
	}

	icmp_hdr->checksum = ip_checksum((USHORT*)icmp_hdr, packet_size);
}
extern int send_ping(SOCKET sd, const sockaddr_in& dest, ICMPHeader* send_buf, int packet_size)
{
	using namespace std;
	cout << "Sending " << packet_size << " bytes to " << inet_ntoa(dest.sin_addr) << "..." << flush;
	int bwrote = sendto(sd, (char*)send_buf, packet_size, 0, (sockaddr*)&dest, sizeof(dest));
	if (bwrote == SOCKET_ERROR)
	{
		cerr << "send failed: " << WSAGetLastError() << endl;
		return -1;
	}
	else if (bwrote < packet_size)
	{
		cout << "sent " << bwrote << " bytes..." << flush;
	}
	return 0;
}
extern int recv_ping(SOCKET sd, sockaddr_in& source, IPHeader* recv_buf, int packet_size)
{
	using namespace std;
	//Ожидаем ответ
	int fromlen = sizeof(source);
	int bread = recvfrom
	(
		sd,
		(char*)recv_buf,
		packet_size + sizeof(IPHeader),
		0,
		(sockaddr*)&source,
		&fromlen
	);
	if (bread == SOCKET_ERROR)
	{
		cerr << "read failed: ";
		DWORD last_error = WSAGetLastError();
		if (last_error == WSAEMSGSIZE)cerr << "buffer too small";
		else cerr << " error #" << last_error << endl;
		return -1;
	}
	return 0;
}
extern int decode_reply(IPHeader* reply, int bytes, sockaddr_in* from)
{
	using namespace std;
	unsigned short header_len = reply->h_len * 4;
	ICMPHeader* icmphdr = (ICMPHeader*)((char*)reply + header_len);
	//При помощи арифметики указателей переходим с начала IP-заголовка на начало ICMP-заголовка

	if (bytes < header_len + ICMP_MIN)
	{
		cerr << "too few bytes from " << inet_ntoa(from->sin_addr) << endl;
		return -1;
	}
	else if (icmphdr->type != ICMP_ECHO_REPLY)
	{
		if (icmphdr->type != ICMP_TTL_EXPIRE)
		{
			if (icmphdr->type == ICMP_DEST_UNREACH)
			{
				cerr << "Destination unreachable" << endl;
			}
			else
			{
				cerr << "Unknown ICMP-packet type" << (int)icmphdr->type << endl;
			}
			return -1;
		}
	}
	else if (icmphdr->id != (USHORT)GetCurrentProcessId())
	{
		return -2;
	}

	int nHops = 128 - reply->ttl;
	if (nHops == 192)nHops = 1;
	else if (nHops == 128)nHops = 0;

	cout << bytes << " bytes from " << inet_ntoa(from->sin_addr) << ", icmp_seq " << icmphdr->seq << ", ";
	if (icmphdr->type == ICMP_TTL_EXPIRE)
	{
		cout << "TTL expired." << endl;
	}
	else
	{
		cout << nHops << " hops";
		cout << ", time: " << (GetTickCount() - icmphdr->timestamp) << " ms.";
	}

	return 0;
}