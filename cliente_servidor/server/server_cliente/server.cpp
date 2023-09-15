#include <stdio.h>
#include <winsock2.h>

//Instrucci�n de cabecera que enlanza la libreria especificada con el c�digo.
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//Funci�n WSAStartup
	WORD wVersionRequested; /*
							WORD es un tipo de dato binario, por lo que dar� como resultado 0 o 1. 
							Uno como un error y cero siendo correctamente realizada la instrucci�n.
							*/
	
	WSADATA wsaData;       //Es un puntero. Que apunta hac�a una estructura que contiene detalles del 'socket'.
	int error;            /*
						  Para constatar el correcto funcinamiento de la funci�n WSAStartup se tienen que crear mensajes dentro de una condicional.
						  Como se trata de un puntero y tipo de dato binario esta variable tiene que ser de tipo int para verificar con 1 o 0 si
						  se esta ejecutando correctamente.
						  
						  */
	
	wVersionRequested = MAKEWORD(2, 2); /*
										MAKEWORD es un macro que simplifica la tarea de asignar la versi�n m�s alta  y la m�s baja que se desea 
										tomar del socket.
										*/
	error = WSAStartup(wVersionRequested, &wsaData); /*
													 Aqu� se asigna a la variable error las partes de la estructura WSAStartup que se evaluar�n
													 en la condicional.
														 */
	
	if(error != 0)
	{
		printf("WSAStartup fallo %d\n", error);
	}

	if(WSACleanup() == SOCKET_ERROR)
	{
		printf("WSACleanup fallo %d\n", WSAGetLastError());
		
	}

	/*
	Orientado a la 
	
	 comunicaci�n
	*/
	
	
	//Funci�n socket 
	
	SOCKET s; //Socket de escucha; se mantiene siempre abierto.
	
	
	WSAStartup(wVersionRequested, &wsaData); 
	
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /*
													  Protocolo que se usara (TCP), socket que soporta los protocolos, 
													  protocolo de Internet(IP.v4).
													  */
	
	if(s == INVALID_SOCKET)
	{
		printf("El socket fallo %d\n", WSAGetLastError());
	}
	
	
	
	int port = 6112; //El n�mero de puerto se inicializa con '0' para obtener un rango en espec�fico para un cliente din�mico.
	int bind_error;
	SOCKADDR_IN tcpaddr; //Es el tipo de estructura que el puntero apunta espec�ficamente para cada uno de los par�metros.
	
	tcpaddr.sin_family = AF_INET; //Asigna el protocolo TCP/IP en el lugar espec�fico con el puntero que apunta a la estructura en cuesti�n.
	tcpaddr.sin_port = htons(port); /*
									Asigna el puerto que en este caso estar� en un rango de 49152 a 65535.
									La funci�n htons se usa para convertir los bytes a un orden que lo pueda leer el TCP/IP.
									*/ 
	tcpaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Asigna la direcci�n local(host) en este caso es para un cliente din�mico(multihost).

	//Funcion bind
	bind_error = bind(s,(SOCKADDR*)&tcpaddr ,sizeof(tcpaddr)); /*
												  El operador 'sizeof' se usa medir a su operando. En este caso es el puntero 'tcpaddr'
												  que apunta a los parametros requeridos dentro de la estructura 'sockaddr_in'. 
												  
												  '&tcpaddr' devuelve la direcci�n de su operando.
												  '(SOCKADDR*)' Lo interpreta como una direcci�n y nos devuelve su contenido.
												  's' el socket en escucha.
												  */
	if(bind_error == SOCKET_ERROR)
	{
	
		printf("Error en la funci�n bind %d\n", WSAGetLastError());
	}
	
	//Funci�n listen

	int listen_error;

	listen_error = listen(s, SOMAXCONN);
	
	if(listen_error == SOCKET_ERROR)
	{
		printf("La funci�n listen ha fallado%d\n", WSAGetLastError());
	}

	
	
	SOCKET s2; //Socket real que acepta las conexiones.
	SOCKADDR_IN c_address;
	int c_len;
	
	c_len = sizeof(c_address);

	//Funci�n accept
	s2 = accept(s,(SOCKADDR *)&c_address,&c_len);
	
	if(s2 == INVALID_SOCKET)
	{
		printf("La funcion accept ha fallado %d\n", WSAGetLastError());		
	}
	
	closesocket(s);
	closesocket(s2);
	
	WSACleanup();
	
}	