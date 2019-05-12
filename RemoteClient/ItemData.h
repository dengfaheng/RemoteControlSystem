#pragma once

#include "Common.h"
#include "MySocket.h"
class CItemData : public CDialog
{
public:
	CItemData(UINT id,SOCKET sock,SOCKADDR_IN *addr,HWND m_hWnd);
	~CItemData(void);

public:
	UINT m_id;
	SOCKET GetSocket();
	CString m_IP;
	CString m_Address;
	CString m_OS;
	CString m_Ver;
	bool Cam;

	SOCKET m_sock;
	CMySocket m_Mysocket;
	HWND m_hWnd;

public:
	void Run();
	void OnBeginListen();
	void GetSysVer(SYSTEMINFO sys);

	static DWORD WINAPI OnListen(LPVOID lp);
};
