#pragma once
#include <Windows.h>
#include <string.h>
#define SYSINFO  0x01
#define RHOSTINFO 0x02
#define TALKMSG 0x04
#define SHUTDOWN 0x05
#define REBOOT 0x06
#define LOGOFF 0x07

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
	char SysPath[80];
	char UserName[30];
	char HostName[30];
	char SystemVersion[80];
	bool CamInfo;

	//CString OperSys;

}HOSTINFO;