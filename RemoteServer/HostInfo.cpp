#include "HostInfo.h"

#pragma comment(lib, "User32.lib")

//用来存储eax,ebx,ecx,edx四个寄存器的信息  
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

/*    在Intel Pentium以上级别的CPU中，有一个称为“时间戳（Time Stamp）”的部件， 
    它以64位无符号整型数的格式，记录了自CPU上电以来所经过的时钟周期数。 
    由于目前的CPU主频都非常高，因此这个部件可以达到纳秒级的计时精度。 
    这个精确性是上述两种方法所无法比拟的。 
    在Pentium以上的CPU中，提供了一条机器指令RDTSC（Read Time Stamp Counter） 
    来读取这个时间戳的数字，并将其保存在EDX:EAX寄存器对中 
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

/*   把eax = 0作为输入参数，可以得到CPU的制造商信息。 
     cpuid指令执行以后，会返回一个12字符的制造商信息， 
     前四个字符的ASC码按低位到高位放在ebx，中间四个放在edx，最后四个字符放在ecx。 
*/  
void CHostInfo::GetManID()   //获取制造商信息  
{  
    char ID[25];          
    memset(ID,0,sizeof(ID));  
	memset(HostInfo.CpuMaker,0,sizeof(HostInfo.CpuMaker)); 
      
    ExeCPUID(0);          //初始化  
    memcpy(ID+0,&debx,4); //制造商信息复制到数组  
    memcpy(ID+4,&dedx,4);  
    memcpy(ID+8,&decx,4);  
    
	strcpy(HostInfo.CpuMaker, ID);

}


/*  在我的电脑上点击右键，选择属性，可以在窗口的下面看到一条CPU的信息， 
    这就是CPU的商标字符串。CPU的商标字符串也是通过cpuid得到的。 
    由于商标的字符串很长(48个字符)，所以不能在一次cpuid指令执行时全部得到， 
    所以intel把它分成了3个操作，eax的输入参数分别是0x80000002,0x80000003,0x80000004， 
    每次返回的16个字符，按照从低位到高位的顺序依次放在eax, ebx, ecx, edx。 
    因此，可以用循环的方式，每次执行完以后保存结果，然后执行下一次cpuid。 
*/  
void CHostInfo::GetCPUType()  
{  
    const DWORD id = 0x80000002; //从0x80000002开始,到0x80000004结束  
    char CPUType[49];//用来存储CPU型号信息  
    memset(CPUType,0,sizeof(CPUType));//初始化数组  
      
    for(DWORD t = 0 ; t < 3 ; t++ )  
    {  
        ExeCPUID(id+t);  
        //每次循环结束,保存信息到数组  
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
	GetCPUInfo();    //获取CPU总信息
	GetMemoryInfo(); //获取内存信息
	GetSysDirectory(); //获取系统目录
	MyGetUserName(); //获取用户名
	MyGetHostName();   //获取主机名
	MyGetSysVersion(); //获取操作系统版本号

}