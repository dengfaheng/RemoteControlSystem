#pragma once

#include "Common.h"
#include "afxwin.h"
// CDlgAddRemark 对话框

class CDlgAddRemark : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddRemark)

public:
	CDlgAddRemark(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddRemark();

// 对话框数据
	enum { IDD = IDD_DLGADDREMARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_remark;
	CWnd *m_pParent;
	afx_msg void OnBnClickedAddRemark();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CEdit m_editremark;
};
