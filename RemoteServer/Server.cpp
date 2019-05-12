#include "Server.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA data; 
	if(WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	MyInfo.GetSysInfo();
	/*
	//////////////////////////////////////////
	////信息测试
	/////////////////////////////////////////
	MyInfo.GetSysInfo();
	cout<<"--------------本机CPU信息如下--------------"<<endl;  
	cout<<"CPU 主 频: "<<MyInfo.HostInfo.CpuFreq<<" Mhz"<<endl;  
	cout<<"CPU 制造商: "<<MyInfo.HostInfo.CpuMaker<<endl;  
	cout<<"CPU 型 号: "<<MyInfo.HostInfo.CpuType<<endl; 
	cout<<"--------------本机内存信息如下--------------"<<endl;
	cout<<"物理内存大小: "<<MyInfo.HostInfo.dwTotalPhysMem<<" MB"<<endl;
	cout<<"可用物理内存大小: "<<MyInfo.HostInfo.dwAvailPhysMem<<" MB"<<endl;
	cout<<"虚拟内存大小: "<<MyInfo.HostInfo.dwTotalVirtualMem<<" MB"<<endl;
	cout<<"可用虚拟内存大小: "<<MyInfo.HostInfo.dwAvailVirtualMem<<" MB"<<endl;
	cout<<"系统目录:"<<MyInfo.HostInfo.SysPath<<endl;	
	cout<<"用户名:"<<MyInfo.HostInfo.UserName<<endl;	
	cout<<"电脑名称:"<<MyInfo.HostInfo.HostName<<endl;	
	cout<<"操作系统版本:"<<MyInfo.HostInfo.SystemVersion<<endl;
	*/


CONNET:

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sclient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8000);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 

	printf("connecting......\n");

	while(1)
	{
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == -1)
		{
			Sleep(500);
			continue;
		}
		printf("connect successfully!\n");
		break;

	}
	
	memset(sendSysInfo.os,0,80);
	int ret;
	sendSysInfo.Cam = true; //判断摄像头是否存在，待完善
	strcpy(sendSysInfo.os,MyInfo.HostInfo.SystemVersion );
	sendSysInfo.ver = 1.1;
	
	while (1)
	{
		memset(revData, 0, sizeof(revData));
		memset(&revMsgInfo, 0, sizeof(MSGINFO));
		memset(&sendMsgInfo, 0, sizeof(MSGINFO));

		ret = MySocket.RecvCommand(sclient, revData, sizeof(MSGINFO));
		if (ret == 0)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				Sleep(200);
			}
			else
			{
				printf("远程客户端已经关闭！\n");
				closesocket(sclient);
				goto CONNET;
			}
		}
		memcpy(&revMsgInfo, revData, sizeof(MSGINFO));
		switch(revMsgInfo.Msg_id)
		{
		case SYSINFO:
			{
				printf("客户端请求获取上线信息\n");
				sendMsgInfo.Msg_id = SYSINFO;
				memcpy(sendMsgInfo.context, &sendSysInfo, sizeof(SYSTEMINFO));

				MySocket.SendCommand(sclient,(char*)&sendMsgInfo, sizeof(MSGINFO));

				printf("上线信息发送完毕\n");
				break;
			}
		case RHOSTINFO:
			{
				printf("客户端请求获取主机信息\n");
				MyInfo.GetSysInfo();
				memset(&sendMsgInfo, 0, sizeof(MSGINFO));
				sendMsgInfo.Msg_id = RHOSTINFO;
				memcpy(sendMsgInfo.context, &MyInfo.HostInfo, sizeof(HOSTINFO));
				for(int i = 0; i < 3; i++)
				{
					MySocket.SendCommand(sclient,(char*)&sendMsgInfo, sizeof(MSGINFO));
					Sleep(50);
				}
				printf("主机信息发送完毕\n");
				break;
			}
		case TALKMSG:
			{
				printf("主机发送信息\n");
				char msgdata[1024*5];
				memset(msgdata, 0, sizeof(msgdata));
				memcpy(msgdata, revMsgInfo.context, sizeof(msgdata));
				MessageBoxA(NULL,msgdata, "消息提示", MB_OK|MB_ICONINFORMATION);
				break;
			}
		case SHUTDOWN:
			{
				printf("主机发送命令：关机!\n");
				MyCmd.MyShutDown();
				break;
			}
		case REBOOT:
			{
				printf("主机发送命令：重启!\n");
				MyCmd.MyReboot();
				break;
			}
		case LOGOFF:
			{
				printf("主机发送命令：注销!\n");
				MyCmd.MyLogoff();
				break;
			}
		default:
			break;
		}

	}

	closesocket(sclient);
	WSACleanup();
	return 0;
}