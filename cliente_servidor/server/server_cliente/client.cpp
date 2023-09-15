#include <winsock2.h>

int main()
{
	
	WSAData wsaData;
	SOCKET socket;
	SOCKADDR_IN ServerAddr;
	int port = 6112;
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	socket =(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	//Función connect
	connect(socket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));

	closesocket(socket);

	WSACleanup();

}