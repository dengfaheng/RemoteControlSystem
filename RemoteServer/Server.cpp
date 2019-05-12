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
	////��Ϣ����
	/////////////////////////////////////////
	MyInfo.GetSysInfo();
	cout<<"--------------����CPU��Ϣ����--------------"<<endl;  
	cout<<"CPU �� Ƶ: "<<MyInfo.HostInfo.CpuFreq<<" Mhz"<<endl;  
	cout<<"CPU ������: "<<MyInfo.HostInfo.CpuMaker<<endl;  
	cout<<"CPU �� ��: "<<MyInfo.HostInfo.CpuType<<endl; 
	cout<<"--------------�����ڴ���Ϣ����--------------"<<endl;
	cout<<"�����ڴ��С: "<<MyInfo.HostInfo.dwTotalPhysMem<<" MB"<<endl;
	cout<<"���������ڴ��С: "<<MyInfo.HostInfo.dwAvailPhysMem<<" MB"<<endl;
	cout<<"�����ڴ��С: "<<MyInfo.HostInfo.dwTotalVirtualMem<<" MB"<<endl;
	cout<<"���������ڴ��С: "<<MyInfo.HostInfo.dwAvailVirtualMem<<" MB"<<endl;
	cout<<"ϵͳĿ¼:"<<MyInfo.HostInfo.SysPath<<endl;	
	cout<<"�û���:"<<MyInfo.HostInfo.UserName<<endl;	
	cout<<"��������:"<<MyInfo.HostInfo.HostName<<endl;	
	cout<<"����ϵͳ�汾:"<<MyInfo.HostInfo.SystemVersion<<endl;
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
	sendSysInfo.Cam = true; //�ж�����ͷ�Ƿ���ڣ�������
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
				printf("Զ�̿ͻ����Ѿ��رգ�\n");
				closesocket(sclient);
				goto CONNET;
			}
		}
		memcpy(&revMsgInfo, revData, sizeof(MSGINFO));
		switch(revMsgInfo.Msg_id)
		{
		case SYSINFO:
			{
				printf("�ͻ��������ȡ������Ϣ\n");
				sendMsgInfo.Msg_id = SYSINFO;
				memcpy(sendMsgInfo.context, &sendSysInfo, sizeof(SYSTEMINFO));

				MySocket.SendCommand(sclient,(char*)&sendMsgInfo, sizeof(MSGINFO));

				printf("������Ϣ�������\n");
				break;
			}
		case RHOSTINFO:
			{
				printf("�ͻ��������ȡ������Ϣ\n");
				MyInfo.GetSysInfo();
				memset(&sendMsgInfo, 0, sizeof(MSGINFO));
				sendMsgInfo.Msg_id = RHOSTINFO;
				memcpy(sendMsgInfo.context, &MyInfo.HostInfo, sizeof(HOSTINFO));
				for(int i = 0; i < 3; i++)
				{
					MySocket.SendCommand(sclient,(char*)&sendMsgInfo, sizeof(MSGINFO));
					Sleep(50);
				}
				printf("������Ϣ�������\n");
				break;
			}
		case TALKMSG:
			{
				printf("����������Ϣ\n");
				char msgdata[1024*5];
				memset(msgdata, 0, sizeof(msgdata));
				memcpy(msgdata, revMsgInfo.context, sizeof(msgdata));
				MessageBoxA(NULL,msgdata, "��Ϣ��ʾ", MB_OK|MB_ICONINFORMATION);
				break;
			}
		case SHUTDOWN:
			{
				printf("������������ػ�!\n");
				MyCmd.MyShutDown();
				break;
			}
		case REBOOT:
			{
				printf("���������������!\n");
				MyCmd.MyReboot();
				break;
			}
		case LOGOFF:
			{
				printf("�����������ע��!\n");
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