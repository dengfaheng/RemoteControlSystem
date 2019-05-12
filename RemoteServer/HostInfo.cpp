#include "HostInfo.h"

#pragma comment(lib, "User32.lib")

//�����洢eax,ebx,ecx,edx�ĸ��Ĵ�������Ϣ  
DWORD deax;  
DWORD debx;  
DWORD decx;  
DWORD dedx;  


CHostInfo::CHostInfo(void)
{
}

CHostInfo::~CHostInfo(void)
{
}

void CHostInfo::ExeCPUID(DWORD veax)
{
	__asm  
	{  
		mov eax,veax  
		cpuid  
		mov deax,eax  
		mov debx,ebx  
		mov decx,ecx  
		mov dedx,edx  
	}  
}

/*    ��Intel Pentium���ϼ����CPU�У���һ����Ϊ��ʱ�����Time Stamp�����Ĳ����� 
    ����64λ�޷����������ĸ�ʽ����¼����CPU�ϵ�������������ʱ���������� 
    ����Ŀǰ��CPU��Ƶ���ǳ��ߣ��������������Դﵽ���뼶�ļ�ʱ���ȡ� 
    �����ȷ�����������ַ������޷�����ġ� 
    ��Pentium���ϵ�CPU�У��ṩ��һ������ָ��RDTSC��Read Time Stamp Counter�� 
    ����ȡ���ʱ��������֣������䱣����EDX:EAX�Ĵ������� 
*/  

void CHostInfo::GetCPUFreq()
{
	int start,over;  
	_asm   
	{  
		RDTSC  
		mov start,eax  
	}  
	Sleep(50);  
	_asm   
	{  
		RDTSC  
		mov over,eax  
	}  
	HostInfo.CpuFreq =(over-start)/50000;

}

/*   ��eax = 0��Ϊ������������Եõ�CPU����������Ϣ�� 
     cpuidָ��ִ���Ժ󣬻᷵��һ��12�ַ�����������Ϣ�� 
     ǰ�ĸ��ַ���ASC�밴��λ����λ����ebx���м��ĸ�����edx������ĸ��ַ�����ecx�� 
*/  
void CHostInfo::GetManID()   //��ȡ��������Ϣ  
{  
    char ID[25];          
    memset(ID,0,sizeof(ID));  
	memset(HostInfo.CpuMaker,0,sizeof(HostInfo.CpuMaker)); 
      
    ExeCPUID(0);          //��ʼ��  
    memcpy(ID+0,&debx,4); //��������Ϣ���Ƶ�����  
    memcpy(ID+4,&dedx,4);  
    memcpy(ID+8,&decx,4);  
    
	strcpy(HostInfo.CpuMaker, ID);

}


/*  ���ҵĵ����ϵ���Ҽ���ѡ�����ԣ������ڴ��ڵ����濴��һ��CPU����Ϣ�� 
    �����CPU���̱��ַ�����CPU���̱��ַ���Ҳ��ͨ��cpuid�õ��ġ� 
    �����̱���ַ����ܳ�(48���ַ�)�����Բ�����һ��cpuidָ��ִ��ʱȫ���õ��� 
    ����intel�����ֳ���3��������eax����������ֱ���0x80000002,0x80000003,0x80000004�� 
    ÿ�η��ص�16���ַ������մӵ�λ����λ��˳�����η���eax, ebx, ecx, edx�� 
    ��ˣ�������ѭ���ķ�ʽ��ÿ��ִ�����Ժ󱣴�����Ȼ��ִ����һ��cpuid�� 
*/  
void CHostInfo::GetCPUType()  
{  
    const DWORD id = 0x80000002; //��0x80000002��ʼ,��0x80000004����  
    char CPUType[49];//�����洢CPU�ͺ���Ϣ  
    memset(CPUType,0,sizeof(CPUType));//��ʼ������  
      
    for(DWORD t = 0 ; t < 3 ; t++ )  
    {  
        ExeCPUID(id+t);  
        //ÿ��ѭ������,������Ϣ������  
        memcpy(CPUType+16*t+ 0,&deax,4);  
        memcpy(CPUType+16*t+ 4,&debx,4);  
        memcpy(CPUType+16*t+ 8,&decx,4);  
        memcpy(CPUType+16*t+12,&dedx,4);  
    }  
	strcpy(HostInfo.CpuType, CPUType);
 
}  

void CHostInfo::GetCPUInfo()
{
	GetCPUFreq();
	GetManID();
	GetCPUType();
}

void  CHostInfo::GetMemoryInfo()   
{   
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	
	HostInfo.dwTotalPhysMem = statex.ullTotalPhys/(1024*1024);
	HostInfo.dwAvailPhysMem = statex.ullAvailPhys/(1024*1024);
	HostInfo.dwTotalVirtualMem = statex.ullTotalVirtual/(1024*1024); 
	HostInfo.dwAvailVirtualMem = statex.ullAvailVirtual/(1024*1024);

}  

void CHostInfo::GetSysDirectory()
{
	memset(HostInfo.SysPath, 0, 80);
	GetSystemDirectoryA(HostInfo.SysPath,80);
}
  
void CHostInfo::MyGetUserName()
{
	int dwSize = 30;
	memset(HostInfo.UserName, 0, 30);
	GetUserNameA(HostInfo.UserName, (LPDWORD)&dwSize);
}

void CHostInfo::MyGetHostName()
{
	int dwSize = 30;
	memset(HostInfo.HostName, 0, 30);
	GetComputerNameA(HostInfo.HostName, (LPDWORD)&dwSize);
}


void CHostInfo::MyGetSysVersion()
{  
    unsigned long nSize = MAXBYTE;  
    OSVERSIONINFO OsVer;  

    OsVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);  
    GetVersionEx(&OsVer);  
	memset(HostInfo.SystemVersion, 0, 80);

    if( OsVer.dwPlatformId == VER_PLATFORM_WIN32_NT )  
    {  
            if( OsVer.dwMajorVersion == 5 )  
            {  
                    switch ( OsVer.dwMinorVersion )  
                    {  
                            case 0:  
									strcpy(HostInfo.SystemVersion, "Windows 2000");
                                    break;  
                            case 1:  
									sprintf(HostInfo.SystemVersion, "Windows XP %s", OsVer.szCSDVersion);
                                    break;  
                            case 2:  
									strcpy(HostInfo.SystemVersion, "Windows 2003 or Windows 2003 R2");
                                    break;  
                            default:  
									strcpy(HostInfo.SystemVersion, "Other System");
                    }  
            }  
            else if ( OsVer.dwMajorVersion == 6 )  
            {  
                    switch(OsVer.dwMinorVersion)  
                    {  
                            case 0:  
									strcpy(HostInfo.SystemVersion, "Windows Vista");
                                    break;  
                            case 1:  
									strcpy(HostInfo.SystemVersion, "Windows 7");
                                    break;  
                            case 2:  
									strcpy(HostInfo.SystemVersion, "Windows 8");
                                    break;  
                            case 3:    
									strcpy(HostInfo.SystemVersion, "Windows 8.1");
                                    break;  
                            default:  
                                    strcpy(HostInfo.SystemVersion, "Other System"); 
									break;
                    }  
            }  
            else if ( OsVer.dwMajorVersion == 10 )  
            {  
                    switch ( OsVer.dwMinorVersion )  
                    {  
                            case 0:  
								   strcpy(HostInfo.SystemVersion, "Windows 10"); 
                                   break;  
                            default:  
									strcpy(HostInfo.SystemVersion, "Other System"); 
									break;
                    }  
            }  
            else  
            {  
				strcpy(HostInfo.SystemVersion, "Unknown System"); 
            }  
    }  


}  

void CHostInfo::GetCamInfo()
{

}

void CHostInfo::GetSysInfo()
{
	GetCPUInfo();    //��ȡCPU����Ϣ
	GetMemoryInfo(); //��ȡ�ڴ���Ϣ
	GetSysDirectory(); //��ȡϵͳĿ¼
	MyGetUserName(); //��ȡ�û���
	MyGetHostName();   //��ȡ������
	MyGetSysVersion(); //��ȡ����ϵͳ�汾��

}