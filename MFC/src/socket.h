#pragma once

#include <WinSock2.h>

// packet protocol
#pragma pack(push)
#pragma pack(1)
typedef struct {
	unsigned char STX;
	unsigned short int Frame_num;
	unsigned short int Data_Length;
	signed short S_WORDS[40];
	unsigned short int BCS;
	unsigned char ETX;
} RECV_MSG;
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct {
	unsigned char STX;
	unsigned short int Frame_num;
	unsigned short int Data_Length;
	signed short S_WORDS[20];
	unsigned short int BCS;
	unsigned char ETX;
} SEND_MSG;
#pragma pack(pop)

class ChWinSock
{
public:
	SOCKET sock;
	SOCKADDR_IN clientaddr;
	RECV_MSG msg_recv;
	RECV_MSG msg_send;
public:
	ChWinSock();
	~ChWinSock();
protected:
	bool ch_open(char* host_IP, int host_port);
	bool ch_connect(char* client_IP, int client_port);
	bool ch_close();
	int ch_send(SEND_MSG msg);
	int ch_recv(RECV_MSG recv);
};
