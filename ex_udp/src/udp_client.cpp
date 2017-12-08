///////////////////////////////////client////////////////////////////////////////
//#include <iostream>
//#include <winsock2.h> // winsock header
//
//#pragma warning (disable:4996)
//#pragma comment (lib,"ws2_32.lib") // winsock library
//#define BUFFER_SIZE 1024 // packet buffer size
//
//using namespace std;
//
//void main(void)
//{
//	WSADATA wsaData;		// winsock struct
//	SOCKET ClientSocket;	// socket
//	SOCKADDR_IN ToServer;   // server info send
//	SOCKADDR_IN FromServer; // server info receive
//
//	int Send_Size;
//	int FromServer_Size;
//	int Recv_Size;
//	ULONG   ServerPort = 61557;		// server port
//
//	double dd = 100.12;
//	char Buffer[BUFFER_SIZE] = {};
//	sprintf_s(Buffer, "STOP,%.2lf\n", dd);
//	if (WSAStartup(MAKEWORD(2,2), &wsaData) == SOCKET_ERROR)
//	{
//		cout << "WSAStarup error " << endl;
//		WSACleanup();
//		exit(0);
//	}
//
//	memset(&ToServer, 0, sizeof(ToServer));
//	memset(&FromServer, 0, sizeof(FromServer));
//
//	ToServer.sin_family = AF_INET;						// IPv4 address
//	ToServer.sin_addr.s_addr = inet_addr("127.0.0.1");	// server IP, loop back IP
//	ToServer.sin_port = htons(ServerPort);				// port number
//
//	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//
//	if (ClientSocket == INVALID_SOCKET)
//	{
//		cout << "socket() error" << endl;
//		closesocket(ClientSocket);
//		WSACleanup();
//		exit(0);
//	}
//	else {
//		cout << "success to create socket" << endl;
//	}
//
//	
//	//- packet send
//	Send_Size = sendto(ClientSocket, Buffer, BUFFER_SIZE, 0,
//		(struct sockaddr*) &ToServer, sizeof(ToServer));
//	cout << "send message : " << Buffer << endl;
//	//printf("%s\n", Buffer);
//	// packet send error
//	if (Send_Size != BUFFER_SIZE)
//	{
//		cout << "sendto() error!" << endl;
//		exit(0);
//	}
//	else {
//		cout << "success to send message to server" << endl;
//	}
//
//	FromServer_Size = sizeof(FromServer);
//	memset(Buffer, 0, BUFFER_SIZE);
//
//	// packet receive, recvfrom : UDP
//	Recv_Size = recvfrom(ClientSocket, Buffer, BUFFER_SIZE, 0,
//		(struct sockaddr*) &FromServer, &FromServer_Size);
//
//	// packet receive error
//	if (Recv_Size < 0)
//	{
//		cout << "recvfrom() error!" << endl;
//		exit(0);
//	}
//
//	// received packet IP andport
//	cout << "Recv from " << inet_ntoa(FromServer.sin_addr) << ":" << ntohs(FromServer.sin_port) << endl;
//	cout << "Received message : " << Buffer << endl;
//
//	closesocket(ClientSocket); // close socket
//	WSACleanup();
//}
