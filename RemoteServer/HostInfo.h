#pragma once
#include "CommonServer.h"
#include <Windows.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

class CHostInfo
{
public:
	CHostInfo(void);
	~CHostInfo(void);

public:
	HOSTINFO HostInfo;

public:
	void ExeCPUID(DWORD veax);  //��ʼ��CPU  
	void GetCPUFreq();       //��ȡCPUƵ��,��λ: MHZ  
	void GetManID();         //��ȡ��������Ϣ  
	void GetCPUType();      //��ȡCPU�ͺ�

public:
	void GetCPUInfo();    //��ȡCPU����Ϣ
	void GetMemoryInfo(); //��ȡ�ڴ���Ϣ
	void GetSysDirectory(); //��ȡϵͳĿ¼
	void MyGetUserName(); //��ȡ�û���
	void MyGetHostName();   //��ȡ������
	void MyGetSysVersion(); //��ȡ����ϵͳ�汾��
	void GetCamInfo();

public:
	void GetSysInfo();
};
