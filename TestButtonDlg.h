// ButtonExampleDlg.h : header file
//
// @Exotic wondrous, All Rights Reserved.
// Based on the Visual C++ TestButton component.
//
// ahmdsmhmmd@gmail.com
// Telegram: https://t.me/exoticwondrous

#pragma once
#include "HoverButton.h"


// CTestButtonDlg dialog
class CTestButtonDlg : public CDialogEx
{
// Construction
public:
	CTestButtonDlg(CWnd* pParent = nullptr);	// standard constructor
	void MovePosCtrl(CHoverButton* PosDlgMoveCtrl, CWnd* PosDlgToMoveCtrl);
	void RestorePosCtrl(CHoverButton* PosDlgMoveCtrl);
	void UpdateButtonsLocation();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTBUTTON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HBITMAP m_hbkBitmap_close;
	HBITMAP m_hbkBitmap_open;
	BOOL    m_isDoorOpen;
	HBRUSH m_hBkBrush;
	CRect m_rct;
	CHoverButton m_btnON;
	CHoverButton m_btnOff;
	CHoverButton m_btnExit;
	CHoverButton m_btnOptions;
	CString m_strImagePath;
	int m_ButtonsCount;
	CMFCLinkCtrl m_mfclink;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOff();
	afx_msg void OnBnClickedCancel();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedOptions();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};
