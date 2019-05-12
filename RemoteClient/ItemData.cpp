#include "StdAfx.h"
#include "ItemData.h"

CItemData::CItemData(UINT id,SOCKET sock,SOCKADDR_IN *addr,HWND m_hWnd)
{
	this->m_id = id;
    this->m_sock = sock;
    this->m_hWnd = m_hWnd;
    char *csIP = inet_ntoa(addr->sin_addr);
    m_IP.Format(_T("%s"),CA2T(csIP));
    //m_Address = QQ.IP2Add(m_IP);
	m_Address.Format(_T("未知"));
    if(m_Address.IsEmpty())
    {
        m_Address.Format(_T("未知"));
    }
    //初始化对话框指针
    /*
    m_cmd = NULL;
    m_screen = NULL;
    m_task = NULL;
    m_filedlg = NULL;
    */
}


DWORD WINAPI CItemData::OnListen(LPVOID lp)
{
	CItemData* t = (CItemData*)lp;
	t->OnBeginListen();
	return 0;
}

void CItemData::Run()
{
	::CloseHandle(CreateThread(0,0,OnListen,(LPVOID)this,0,0));
}

SOCKET CItemData::GetSocket()
{
	return this->m_sock;
}

void CItemData::OnBeginListen() //等待完善
{
	int nRet;
	MSGINFO msg;
	memset(&msg,0,sizeof(MSGINFO));
	msg.Msg_id = SYSINFO;
	nRet = m_Mysocket.SendCommand(m_sock,(char*)&msg,sizeof(MSGINFO));
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("获取系统信息消息发送失败"),_T("警告"),MB_OK|MB_ICONWARNING);
	}
	memset(&msg,0,sizeof(MSGINFO));
	while(true)
	{
		nRet = m_Mysocket.RecvCommand(m_sock,(char*)&msg,sizeof(MSGINFO));
		if(nRet == 0)
		{
			if(WSAGetLastError()==WSAEWOULDBLOCK)  //WSAEWOULDBLOCK的错误,则表示要发生阻塞了
			{
				Sleep(200);
				continue;   //进行下次循环
			}
			else
			{
				//接收消息失败，发送下线通知
				::closesocket(m_sock);
				::SendMessage(this->m_hWnd,ID_OFFLINE,this->m_id,0);
				return;
			}
		}
		else
		{
			switch(msg.Msg_id)
			{
			case SYSINFO:
				{
					SYSTEMINFO systeminfo;
					memset(&systeminfo,0,sizeof(SYSTEMINFO));
					memcpy(&systeminfo,msg.context,sizeof(SYSTEMINFO));
					GetSysVer(systeminfo);
					::SendMessage(m_hWnd,ID_ONLINE,(WPARAM)this,0);
				}
				break;
			}
		}
	}
}

void CItemData::GetSysVer(SYSTEMINFO sys)
{
	this->Cam = sys.Cam;
	this->m_Ver.Format(_T("%0.2lf 测试版"),sys.ver);
	this->m_OS.Format(_T("%s"), CA2T(sys.os));
}




CItemData::~CItemData(void)
{
}
