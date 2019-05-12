#pragma once
#include "afxcmn.h"
#include "Common.h"

#define ID_UPDATA WM_USER+11


// CDlgHostInfo �Ի���
typedef struct MyHostInfo
{
	CString CpuFreq;
	CString CpuMaker;
	CString CpuType;
	CString TotalPhyMem;
	CString AvailPhyMem;
	CString TotalVirMem;
	CString AvailVirMem;
	CString SystemPath;
	CString UserName;
	CString HostName;
	CString SysVersion;
}LsCtrInfo;



class CDlgHostInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgHostInfo)

public:
	CDlgHostInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHostInfo();

// �Ի�������
	enum { IDD = IDD_DLGHOSTINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listHsInfo;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
public:
	LRESULT OnUpdata(WPARAM wparam,LPARAM lparam);

public:
	LsCtrInfo lsctrinfo;

protected:
	virtual void OnOK();
};
