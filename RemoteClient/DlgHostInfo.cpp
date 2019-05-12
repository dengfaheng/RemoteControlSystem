// DlgHostInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "DlgHostInfo.h"


// CDlgHostInfo �Ի���

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


// CDlgHostInfo ��Ϣ�������

int CDlgHostInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}

BOOL CDlgHostInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listHsInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listHsInfo.InsertColumn(0,_T("NAME"),LVCFMT_CENTER,120);
	m_listHsInfo.InsertColumn(1,_T("VALUE"),LVCFMT_CENTER,240);

	m_listHsInfo.InsertItem(0,_T("CPU��Ƶ"),0);
	m_listHsInfo.InsertItem(1,_T("CPU������"),0);
	m_listHsInfo.InsertItem(2,_T("CPU�ͺ�"),0);
	m_listHsInfo.InsertItem(3,_T("�����ڴ��ܴ�С"),0);
	m_listHsInfo.InsertItem(4,_T("���������ڴ�"),0);
	m_listHsInfo.InsertItem(5,_T("�����ڴ��ܴ�С"),0);
	m_listHsInfo.InsertItem(6,_T("���������ڴ�"),0);
	m_listHsInfo.InsertItem(7,_T("ϵͳ·��"),0);
	m_listHsInfo.InsertItem(8,_T("�û���"),0);
	m_listHsInfo.InsertItem(9,_T("������"),0);
	m_listHsInfo.InsertItem(10,_T("ϵͳ�汾"),0);
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgHostInfo::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//(CRemoteClientDlg*)GetParent()->
	OnOK();
}

void CDlgHostInfo::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
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

