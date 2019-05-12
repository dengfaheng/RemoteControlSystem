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
	void ExeCPUID(DWORD veax);  //初始化CPU  
	void GetCPUFreq();       //获取CPU频率,单位: MHZ  
	void GetManID();         //获取制造商信息  
	void GetCPUType();      //获取CPU型号

public:
	void GetCPUInfo();    //获取CPU总信息
	void GetMemoryInfo(); //获取内存信息
	void GetSysDirectory(); //获取系统目录
	void MyGetUserName(); //获取用户名
	void MyGetHostName();   //获取主机名
	void MyGetSysVersion(); //获取操作系统版本号
	void GetCamInfo();

public:
	void GetSysInfo();
};
