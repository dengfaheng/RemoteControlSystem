// RemoteClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ItemData.h"
#include "MySocket.h"
#include "Common.h"
#include <MMSystem.h>
#include "afxwin.h"
#include "DlgAbout.h"
#include "DlgHostInfo.h"
#include "DlgSysCmd.h"
#include "DlgAddRemark.h"


// CRemoteClientDlg �Ի���
class CRemoteClientDlg : public CDialog
{
// ����
public:
	CRemoteClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REMOTECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileMgr();
	afx_msg void OnAbout();
	afx_msg void OnHostInfo();
	afx_msg void OnSysCmd();
	afx_msg void OnAddRemark();

	DECLARE_MESSAGE_MAP()


private:
	CToolBar m_toolbar;
	CImageList m_imagelist;
	CStatusBar m_statusbar;
	CBitmap m_subbmp[6];
	CImageList m_mainicon;
	void UpdateMain(int port);

	UINT m_port;
	UINT m_max;
	UINT m_Sound;
	SOCKET s;

public:
	CListCtrl m_list;
	CRect m_rect;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	static DWORD WINAPI OninitSocket(LPVOID self);
	void AddHost(SOCKET sock,SOCKADDR_IN addr);

	void GetNewItemData(SOCKET sock,SOCKADDR_IN addr);
	bool InitSocket();
//������
public:
	void  ShowOnLine();
	 LRESULT OnOffLine(WPARAM wparam,LPARAM lparam);
	 LRESULT OnAddHost(WPARAM wparam,LPARAM lparam);
	 afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
//ϵͳ����
public:
	LRESULT OnTalkMsg(WPARAM wparam,LPARAM lparam);
	LRESULT OnSendMsgAll(WPARAM wparam,LPARAM lparam);
	LRESULT OnShutDownSingle(WPARAM wparam,LPARAM lparam);
	LRESULT OnRebootSingle(WPARAM wparam,LPARAM lparam);
	LRESULT OnLogOffSingle(WPARAM wparam,LPARAM lparam);

	LRESULT OnShutDownAll(WPARAM wparam,LPARAM lparam);
	LRESULT OnRebootAll(WPARAM wparam,LPARAM lparam);
	LRESULT OnLogOffAll(WPARAM wparam,LPARAM lparam);
	//��ӱ�ע
public:
	LRESULT OnAddServerRemark(WPARAM wparam,LPARAM lparam);

public:
	CDlgAbout *pDlgAbout;
	CDlgHostInfo *pDlgHostInfo;
	CDlgSysCmd *pDlgSysCmd;
	CDlgAddRemark *pDlgAddRemark;
};
