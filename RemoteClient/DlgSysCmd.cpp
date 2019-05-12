// DlgSysCmd.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgSysCmd.h"


// CDlgSysCmd 对话框

IMPLEMENT_DYNAMIC(CDlgSysCmd, CDialog)

CDlgSysCmd::CDlgSysCmd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSysCmd::IDD, pParent)
	, m_lsmsg(_T(""))
	, m_record(_T(""))
{
	//pPat = (CRemoteClientDlg*)pParent;
	m_pParent = pParent;
}

CDlgSysCmd::~CDlgSysCmd()
{
}

void CDlgSysCmd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editmsg);
	DDX_Text(pDX, IDC_EDIT1, m_lsmsg);
	DDX_Control(pDX, IDC_EDIT2, m_msgrecord);
	DDX_Text(pDX, IDC_EDIT2, m_record);
}


BEGIN_MESSAGE_MAP(CDlgSysCmd, CDialog)
	ON_BN_CLICKED(IDCLEAR, &CDlgSysCmd::OnBnClickedClear)
	ON_BN_CLICKED(IDSENDSINGLE, &CDlgSysCmd::OnBnClickedSendsingle)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDSENDMSGALL, &CDlgSysCmd::OnBnClickedSendmsgall)
	ON_BN_CLICKED(IDSHUTDOWNSINGLE, &CDlgSysCmd::OnBnClickedShutDownSingle)
	ON_BN_CLICKED(IDREBOOTSINGLE, &CDlgSysCmd::OnBnClickedRebootSingle)
	ON_BN_CLICKED(IDLOGOFFSINGLE, &CDlgSysCmd::OnBnClickedLogOffSingle)
END_MESSAGE_MAP()


// CDlgSysCmd 消息处理程序

void CDlgSysCmd::OnBnClickedClear()
{
	m_editmsg.SetWindowText(_T(""));
	m_msgrecord.SetWindowText(_T(""));
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgSysCmd::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//DestroyWindow();
	m_editmsg.SetWindowText(_T(""));
	CDialog::OnOK();
}

void CDlgSysCmd::OnBnClickedSendsingle()
{
	// TODO: 在此添加控件通知处理程序代码

	CWnd *pMainDlg = m_pParent;
	UpdateData(TRUE);

	CString record(m_record.GetBuffer());
	record += L"\r\n发送消息(单台):\r\n";
	record += m_lsmsg.GetBuffer();
	m_msgrecord.SetWindowText(record.GetBuffer());

	::SendMessage(pMainDlg->m_hWnd, ID_TALKMSG,NULL, NULL);
	
}

INT_PTR CDlgSysCmd::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::DoModal();
}

BOOL CDlgSysCmd::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSysCmd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	m_editmsg.SetWindowText(_T(""));
	m_msgrecord.SetWindowText(_T(""));

	// TODO: 在此处添加消息处理程序代码
}

void CDlgSysCmd::OnBnClickedSendmsgall()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pMainDlg = m_pParent;
	UpdateData(TRUE);
	
	CString record(m_record.GetBuffer());
	record += L"\r\n发送消息(所有):\r\n";
	record += m_lsmsg.GetBuffer();
	m_msgrecord.SetWindowText(record.GetBuffer());

	::SendMessage(pMainDlg->m_hWnd, ID_SENDMSGALL,NULL, NULL);

}

void CDlgSysCmd::OnBnClickedShutDownSingle()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_pParent->m_hWnd, ID_SHUTDOWNSINGLE,NULL, NULL);
}

void CDlgSysCmd::OnBnClickedRebootSingle()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_pParent->m_hWnd, ID_REBOOTSINGLE,NULL, NULL);
}

void CDlgSysCmd::OnBnClickedLogOffSingle()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_pParent->m_hWnd, ID_LOGOFFSINGLE,NULL, NULL);
}
