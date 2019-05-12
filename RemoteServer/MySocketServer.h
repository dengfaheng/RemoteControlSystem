#pragma once
#include <winsock2.h>
#pragma  comment(lib,"ws2_32.lib")

class CMySocketServer
{
public:
	CMySocketServer(void);
	~CMySocketServer(void);
public:
	int SendCommand(SOCKET socket,const char* buf,int bytes);
	int RecvCommand(SOCKET socket,char* buf,int bytes);
	void Clean();
};
