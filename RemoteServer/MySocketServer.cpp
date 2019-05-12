#include "MySocketServer.h"
#include <stdio.h>

CMySocketServer::CMySocketServer(void)
{
}

CMySocketServer::~CMySocketServer(void)
{
}
int CMySocketServer::SendCommand(SOCKET socket,const char* buf,int bytes)
{
	const char *b = buf;
	while(bytes > 0) 
	{ 
		int r = send(socket,b,bytes,0); 
		if(r < 0) 
		{ 
			printf("Socket_Error\n");
			return r; 
		} 
		else if(r == 0)
		{
			printf("Socket_Error\n");
			break;
		} 
		bytes -= r; 
		b += r; 
	} 
	return b - (char*)buf;
	
}

int CMySocketServer::RecvCommand(SOCKET socket,char* buf,int bytes)
{
	char *b = (char*)buf;
	while(bytes > 0)
	{
		int r = recv(socket,b,bytes,0);
		if(r < 0)
		{
			printf("Socket_Error\n");
			return 0;
		}
		else if(r == 0)
		{
			printf("Socket_Error\n");
			break;
		}
		bytes = bytes - r;
		b = b + r;
	}
	return b - (char*)buf;
}


void CMySocketServer::Clean()
{
	::WSACleanup();
}