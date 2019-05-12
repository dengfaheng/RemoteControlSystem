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
//11��ռ
#define ID_ADDREMARK WM_USER+12

typedef struct tagMSGINFO //������Ϣ�ṹ��
{
	int Msg_id;
	BYTE context[1024*5];
}MSGINFO;

typedef struct tagSYSTEMINFO //������Ϣ
{
	char os[80];
	bool Cam; //����ͷ
	double ver;
}SYSTEMINFO;

typedef struct tagHOSTINFO //Զ��������Ϣ
{
	unsigned long CpuFreq; //CPU��Ƶ
	char CpuMaker[30];     //CPU������
	char CpuType[50];      //CPU�ͺ�
	DWORDLONG dwTotalPhysMem; //�����ڴ�
	DWORDLONG dwAvailPhysMem;//���������ڴ�
	DWORDLONG dwTotalVirtualMem; //�����ڴ�
	DWORDLONG dwAvailVirtualMem; //���������ڴ�
	char SysPath[80];           //ϵͳ·��
	char UserName[30];			//�û���
	char HostName[30];			//������
	char SystemVersion[80];		//ϵͳ�汾

}HOSTINFO;

