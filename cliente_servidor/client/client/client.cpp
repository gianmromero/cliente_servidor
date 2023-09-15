#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib");

int main(){

	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN ServerAddr;
	int port = 6112;
	
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//Función connect
	connect(s, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));.

	WSACleanup();

	//Función WSASend
	WSABUF lpBuffers;
	DWORD  dwBufferCount;
	DWORD lpNumberOfBytesSent;
	DWORD dwFlags;
	WSAOVERLAPPED lpOverlapped;
	WSACOMPLETION Complention;
	
	send = WSASend(s, &lpBuffers, 1, &lpNumberOfBytesSent, 0, &lpOverlapped, (WSACOMPLETION *) &Complention);
	
	if(send != 0)
	{
		printf("Error en la funcion WSASend%d\n", WSAGetLastError());
	
	}

	closesocket(s);

	WSACleanup();
	                  
}