// DlgAbout.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "DlgAbout.h"


// CDlgAbout 对话框

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


// CDlgAbout 消息处理程序

void CDlgAbout::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//DestroyWindow();
	CDialog::OnOK();
}
