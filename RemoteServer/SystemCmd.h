#pragma once
#include <windows.h>

class CSystemCmd
{
public:
	CSystemCmd(void);
	~CSystemCmd(void);

public:
	BOOL ReSetWindows(DWORD dwFlags,BOOL bForce);
	BOOL EnableShutDownPriv();
	void MyShutDown();
	void MyReboot();
	void MyLogoff();

};
