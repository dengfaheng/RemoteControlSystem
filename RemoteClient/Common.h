#pragma once
#include "stdafx.h"
#define SYSINFO  0x01
#define RHOSTINFO 0x02
#define TALKMSG 0x04
#define SHUTDOWN 0x05
#define REBOOT 0x06
#define LOGOFF 0x07

#define ID_ONLINE WM_USER+1
#define ID_OFFLINE WM_USER+2
#define ID_TALKMSG WM_USER+3
#define ID_SENDMSGALL WM_USER+4
#define ID_SHUTDOWNSINGLE WM_USER+5
#define ID_REBOOTSINGLE WM_USER+6
#define ID_LOGOFFSINGLE WM_USER+7

#define ID_SHUTDOWNALL WM_USER+8
#define ID_REBOOTALL WM_USER+9
#define ID_LOGOFFALL WM_USER+10
//11被占
#define ID_ADDREMARK WM_USER+12

typedef struct tagMSGINFO //传输消息结构体
{
	int Msg_id;
	BYTE context[1024*5];
}MSGINFO;

typedef struct tagSYSTEMINFO //上线信息
{
	char os[80];
	bool Cam; //摄像头
	double ver;
}SYSTEMINFO;

typedef struct tagHOSTINFO //远程主机信息
{
	unsigned long CpuFreq; //CPU主频
	char CpuMaker[30];     //CPU制造商
	char CpuType[50];      //CPU型号
	DWORDLONG dwTotalPhysMem; //物理内存
	DWORDLONG dwAvailPhysMem;//可用物理内存
	DWORDLONG dwTotalVirtualMem; //虚拟内存
	DWORDLONG dwAvailVirtualMem; //可用虚拟内存
	char SysPath[80];           //系统路径
	char UserName[30];			//用户名
	char HostName[30];			//主机名
	char SystemVersion[80];		//系统版本

}HOSTINFO;

