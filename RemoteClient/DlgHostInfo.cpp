// DlgHostInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "DlgHostInfo.h"


// CDlgHostInfo 对话框

IMPLEMENT_DYNAMIC(CDlgHostInfo, CDialog)

CDlgHostInfo::CDlgHostInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHostInfo::IDD, pParent)
{

}

CDlgHostInfo::~CDlgHostInfo()
{
}

void CDlgHostInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_listHsInfo);
}


BEGIN_MESSAGE_MAP(CDlgHostInfo, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CDlgHostInfo::OnBnClickedOk)
	ON_MESSAGE(ID_UPDATA, OnUpdata)
END_MESSAGE_MAP()


// CDlgHostInfo 消息处理程序

int CDlgHostInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

BOOL CDlgHostInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listHsInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listHsInfo.InsertColumn(0,_T("NAME"),LVCFMT_CENTER,120);
	m_listHsInfo.InsertColumn(1,_T("VALUE"),LVCFMT_CENTER,240);

	m_listHsInfo.InsertItem(0,_T("CPU主频"),0);
	m_listHsInfo.InsertItem(1,_T("CPU生产商"),0);
	m_listHsInfo.InsertItem(2,_T("CPU型号"),0);
	m_listHsInfo.InsertItem(3,_T("物理内存总大小"),0);
	m_listHsInfo.InsertItem(4,_T("可用物理内存"),0);
	m_listHsInfo.InsertItem(5,_T("虚拟内存总大小"),0);
	m_listHsInfo.InsertItem(6,_T("可用虚拟内存"),0);
	m_listHsInfo.InsertItem(7,_T("系统路径"),0);
	m_listHsInfo.InsertItem(8,_T("用户名"),0);
	m_listHsInfo.InsertItem(9,_T("主机名"),0);
	m_listHsInfo.InsertItem(10,_T("系统版本"),0);
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgHostInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//(CRemoteClientDlg*)GetParent()->
	OnOK();
}

void CDlgHostInfo::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//DestroyWindow();

	CDialog::OnOK();
}

LRESULT CDlgHostInfo::OnUpdata(WPARAM wparam,LPARAM lparam)
{
	m_listHsInfo.SetItemText(0,1,lsctrinfo.CpuFreq.GetBuffer());
	m_listHsInfo.SetItemText(1,1,lsctrinfo.CpuMaker.GetBuffer());
	m_listHsInfo.SetItemText(2,1,lsctrinfo.CpuType.GetBuffer());
	m_listHsInfo.SetItemText(3,1,lsctrinfo.TotalPhyMem.GetBuffer());
	m_listHsInfo.SetItemText(4,1,lsctrinfo.AvailPhyMem.GetBuffer());
	m_listHsInfo.SetItemText(5,1,lsctrinfo.TotalVirMem.GetBuffer());
	m_listHsInfo.SetItemText(6,1,lsctrinfo.AvailVirMem.GetBuffer());
	m_listHsInfo.SetItemText(7,1,lsctrinfo.SystemPath.GetBuffer());
	m_listHsInfo.SetItemText(8,1,lsctrinfo.UserName.GetBuffer());
	m_listHsInfo.SetItemText(9,1,lsctrinfo.HostName.GetBuffer());
	m_listHsInfo.SetItemText(10,1,lsctrinfo.SysVersion.GetBuffer());

	return 0;
}

