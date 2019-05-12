#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "resource.h"
#include "Common.h"
#include "ItemData.h"
#include "MySocket.h"
#include "afxwin.h"
// CDlgSysCmd 对话框

class CDlgSysCmd : public CDialog
{
	DECLARE_DYNAMIC(CDlgSysCmd)

public:
	CDlgSysCmd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysCmd();

// 对话框数据
	enum { IDD = IDD_DLGSYSCMD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editmsg;
	afx_msg void OnBnClickedClear();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedSendsingle();
	CString m_lsmsg;
	CString m_GetMsg;

	//CRemoteClientDlg * pPat;
	CWnd *m_pParent;

	virtual INT_PTR DoModal();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedSendmsgall();
	CEdit m_msgrecord;
	CString m_record;
	afx_msg void OnBnClickedShutDownSingle();
	afx_msg void OnBnClickedRebootSingle();
	afx_msg void OnBnClickedLogOffSingle();
};
