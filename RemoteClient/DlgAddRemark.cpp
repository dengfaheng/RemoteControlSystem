// DlgAddRemark.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "DlgAddRemark.h"


// CDlgAddRemark 对话框

IMPLEMENT_DYNAMIC(CDlgAddRemark, CDialog)

CDlgAddRemark::CDlgAddRemark(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddRemark::IDD, pParent)
	, m_remark(_T(""))
{
	m_pParent = pParent;
}

CDlgAddRemark::~CDlgAddRemark()
{
}

void CDlgAddRemark::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_remark);
	DDX_Control(pDX, IDC_EDIT1, m_editremark);
}


BEGIN_MESSAGE_MAP(CDlgAddRemark, CDialog)
	ON_BN_CLICKED(IDADDREMARK, &CDlgAddRemark::OnBnClickedAddRemark)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDlgAddRemark 消息处理程序

void CDlgAddRemark::OnBnClickedAddRemark()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	::SendMessage(m_pParent->m_hWnd, ID_ADDREMARK, NULL, NULL);
	this->DestroyWindow();
}

void CDlgAddRemark::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	m_editremark.SetWindowText(_T(""));
	// TODO: 在此处添加消息处理程序代码
}
