////////////////////////////////////server//////////////////////////////////////////////
#include <iostream>
#include <winsock2.h> // winsock header

#pragma warning	(disable : 4996)
#pragma comment (lib,"ws2_32.lib") // winsock library
#define BUFFER_SIZE 1024 // packet buffer size

using namespace std;

void main(void)
{
	WSADATA wsaData;		// winsock struct
	SOCKET ServerSocket;	// socket
	SOCKADDR_IN ServerInfo; // server info 
	SOCKADDR_IN FromClient; // client info

	int FromClient_Size;	// receive data size from client
	int Recv_Size;			// receive data size
	int Send_Size;			// send data size
	int Count;

	char Buffer[BUFFER_SIZE];
	short ServerPort = 61557;	// server port number 

	// WSAStartup is function that initialize "ws2_32.dll" 
	if (WSAStartup(MAKEWORD(2,2), &wsaData) == SOCKET_ERROR){
		cout << "WSAStartup error" << endl;
		WSACleanup();	// terminate using "ws2_32.dll" library
	}

	// initialize
	memset(&ServerInfo, 0, sizeof(ServerInfo)); 
	memset(&FromClient, 0, sizeof(FromClient));
	memset(Buffer, 0, BUFFER_SIZE);

	ServerInfo.sin_family = AF_INET;					 // IPv4 address
	ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1"); // loop back IP
	ServerInfo.sin_port = htons(ServerPort);			 // port number

	// Creat socket
	ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // socket for udp. SOCK_DGRAM : UDP
	if (ServerSocket == INVALID_SOCKET) 
	{
		cout << "socket() error" << endl;
		closesocket(ServerSocket);
		WSACleanup();
		exit(0);
	}
	else {
		cout << "success to create socket" << endl;
	}

	// bind() - need for server
	// no need for client
	if (bind(ServerSocket, (struct sockaddr*)&ServerInfo, // set server information to socket
		sizeof(ServerInfo)) == SOCKET_ERROR)
	{
		cout << "bind() error" << endl;
		closesocket(ServerSocket);
		WSACleanup();
		exit(0);
	}
	else {
		cout << "success to bind socket" << endl;
	}

	
	FromClient_Size = sizeof(FromClient);
	// recvfrom : UDP.  receive packet
	Recv_Size = recvfrom(ServerSocket, Buffer, BUFFER_SIZE, 0,
		(struct sockaddr*) &FromClient, &FromClient_Size);

	if (Recv_Size < 0)
	{
		cout << "recvfrom() error" << endl;
		exit(0);
	}

	cout << "receive client info " << inet_ntoa(FromClient.sin_addr) << ":" << ntohs(FromClient.sin_port) << endl;
	cout << "received message : " << Buffer << endl;

	//  packet send
	Send_Size = sendto(ServerSocket, Buffer, Recv_Size, 0,
		(struct sockaddr*) &FromClient, sizeof(FromClient));
	if (Send_Size != Recv_Size)
	{
		cout << "sendto() error!" << endl;
		exit(0);
	}
	else {
		cout << "send mesage to client : " << Buffer << endl;
	}
	
	closesocket(ServerSocket); // close socket.
	WSACleanup();
}
