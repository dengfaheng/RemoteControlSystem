// DlgAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "DlgAbout.h"


// CDlgAbout �Ի���

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)

CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAbout::IDD, pParent)
{

}

CDlgAbout::~CDlgAbout()
{
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
END_MESSAGE_MAP()


// CDlgAbout ��Ϣ�������

void CDlgAbout::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	//DestroyWindow();
	CDialog::OnOK();
}
