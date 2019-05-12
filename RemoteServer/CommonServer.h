#pragma once
#include <Windows.h>
#include <string.h>
#define SYSINFO  0x01
#define RHOSTINFO 0x02
#define TALKMSG 0x04
#define SHUTDOWN 0x05
#define REBOOT 0x06
#define LOGOFF 0x07

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
	char SysPath[80];
	char UserName[30];
	char HostName[30];
	char SystemVersion[80];
	bool CamInfo;

	//CString OperSys;

}HOSTINFO;