// DlgAddRemark.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "DlgAddRemark.h"


// CDlgAddRemark �Ի���

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


// CDlgAddRemark ��Ϣ�������

void CDlgAddRemark::OnBnClickedAddRemark()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	::SendMessage(m_pParent->m_hWnd, ID_ADDREMARK, NULL, NULL);
	this->DestroyWindow();
}

void CDlgAddRemark::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	m_editremark.SetWindowText(_T(""));
	// TODO: �ڴ˴������Ϣ����������
}
