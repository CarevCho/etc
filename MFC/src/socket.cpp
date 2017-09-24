#include "socket.h"
#pragma warning (disable:4996)
#pragma once

ChWinSock::ChWinSock()
{
}

ChWinSock::~ChWinSock()
{
}

bool ChWinSock::ch_open(char* host_IP, int host_port)
{
	// init socket ; version 2.2
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKADDR_IN host;
	memset(&host, 0, sizeof(SOCKADDR_IN));
	host.sin_family = AF_INET;
	host.sin_port = htons(host_port);
	host.sin_addr.s_addr = inet_addr(host_IP);

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) 
		return false;
	
	if (bind(sock, (SOCKADDR*)&host, sizeof(host)) == SOCKET_ERROR)
		return false;

	msg_send.STX = 0x20, msg_send.ETX = 0x21;
	msg_send.Data_Length = htons(40);
	msg_send.Frame_num = htons(0);
	memset(msg_send.S_WORDS, 0, 20 * sizeof(signed short));
	memset(msg_recv.S_WORDS, 0, 40 * sizeof(signed short));
	
	return true;
}

bool ChWinSock::ch_connect(char* client_IP, int client_port)
{
	return true;
}

bool ChWinSock::ch_close()
{
	return true;
}

int ChWinSock::ch_send(SEND_MSG msg)
{
	return 0;
}

int ChWinSock::ch_recv(RECV_MSG recv)
{
	return 0;
}
