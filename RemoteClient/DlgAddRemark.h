#pragma once

#include "Common.h"
#include "afxwin.h"
// CDlgAddRemark �Ի���

class CDlgAddRemark : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddRemark)

public:
	CDlgAddRemark(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddRemark();

// �Ի�������
	enum { IDD = IDD_DLGADDREMARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_remark;
	CWnd *m_pParent;
	afx_msg void OnBnClickedAddRemark();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CEdit m_editremark;
};
