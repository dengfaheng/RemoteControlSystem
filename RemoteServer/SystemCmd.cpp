#include "SystemCmd.h"

CSystemCmd::CSystemCmd(void)
{
}

CSystemCmd::~CSystemCmd(void)
{
}

BOOL CSystemCmd::ReSetWindows(DWORD dwFlags,BOOL bForce)
{
	//�������Ƿ���ȷ  
	if(dwFlags!=EWX_LOGOFF&&dwFlags!=EWX_REBOOT&&dwFlags!=EWX_SHUTDOWN)  
		return FALSE;  
	//���ϵͳ�İ汾��Ϣ�������Ǻ���ȷ���Ƿ���Ҫ����ϵͳȨ��  
	OSVERSIONINFO osvi={0};  
	//��ò����Ĵ�С�����ṩ��GetVersionEx���ж�����һ���°汾��OSVERSIONINFO�����Ǿɰ汾��  
	//�°汾��OSVERSIONINFOEX������汾  
	osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);  
	if(!GetVersionEx(&osvi))  
	{  
		return FALSE;  
	}  
	//������ϵͳ�İ汾�������NT���͵�ϵͳ����Ҫ����ϵͳȨ��  
	if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)  
	{  
		EnableShutDownPriv();  
	}  
	//�ж��Ƿ���ǿ�ƹػ���ǿ�ƹر�ϵͳ���̡�  
	dwFlags|=(bForce!=FALSE)?EWX_FORCE:EWX_FORCEIFHUNG;  
	//����API  
	return ExitWindowsEx(dwFlags,0);  
}

BOOL CSystemCmd::EnableShutDownPriv()
{
	HANDLE hToken=NULL;  
	TOKEN_PRIVILEGES tkp={0};  
	//�򿪵�ǰ�����Ȩ������  
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))  
	{  
		return FALSE;  
	}  
	//���ĳһ�ض�Ȩ�޵�Ȩ�ޱ�ʶLUID��������tkp��  
	if (!LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid))  
	{  
		CloseHandle(hToken);  
		return FALSE;  
	}  
	tkp.PrivilegeCount=1;  
	tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;  
	//����AdjustTokenPrivileges������������Ҫ��ϵͳȨ��  
	if(!AdjustTokenPrivileges(hToken,FALSE,&tkp,sizeof(TOKEN_PRIVILEGES),NULL,NULL))  
	{  
		CloseHandle(hToken);  
		return FALSE;  
	}  
	return TRUE;  
}

void CSystemCmd::MyShutDown()
{
	ReSetWindows(EWX_SHUTDOWN,true);
}
void CSystemCmd::MyReboot()
{
	ReSetWindows(EWX_REBOOT,true);
}
void CSystemCmd::MyLogoff()
{
	ReSetWindows(EWX_LOGOFF,true);
}
