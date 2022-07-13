// @Exotic wondrous, All Rights Reserved.
// Based on the Visual C++ TestButton component.
//
// ahmdsmhmmd@gmail.com
// Telegram: https://t.me/exoticwondrous
//
#pragma once
 #include "HoverButton.h"


// COptions dialog

class CDlgOptions : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOptions)

public:
	CDlgOptions(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgOptions();
	CString m_strImagePath;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	
	CButton m_ch1En;
	CButton m_ch1De;
	CButton m_ch1Ho;
	CButton m_ch1Cl;
	CButton m_ch1Fl;
	CButton m_ch1Sl;

	CButton m_ch2En;
	CButton m_ch2De;
	CButton m_ch2Ho;
	CButton m_ch2Cl;
	CButton m_ch2Fo;
	CButton m_ch2Sl;

	HBITMAP m_hSelectedBitmap;
	CMFCEditBrowseCtrl m_editBrowserImg;
 	void UpdateSliderPos();
	void MovePosCtrl(CHoverButton* PosDlgMoveCtrl, CWnd* PosDlgToMoveCtrl);
	void RestorePosCtrl(CHoverButton* PosDlgMoveCtrl);
	void UpdateLocation(int nLocation);
	CString GetPersSectionName(CString strPathfile);
	BOOL UpdatePersistence(CString strPath);

protected:
	CButton m_chSl;
	CHoverButton m_btnOFFHover;
	CHoverButton m_btnONHover;
	int m_edit1Flashout;
	int m_edit2Fladeout;
	CSliderCtrl m_SliderList;
	int         m_SliderPos;
	int         m_nlocation;
	CRect       m_rctbkgnd;
	CSpinButtonCtrl m_SpingOFF;
	CSpinButtonCtrl m_SpingON;
	CButton m_checkLocation;


	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnEnChangeMfceditbrowse();
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOff();
	afx_msg void OnBnClickedCheck2fl();
	afx_msg void OnBnClickedCheck1fl();
	afx_msg void OnBnClickedCheck2en();
	afx_msg void OnBnClickedCheck1en();
	afx_msg void OnBnClickedCheck1de();
	afx_msg void OnBnClickedCheck2de();
	afx_msg void OnBnClickedCheck1cl();
	afx_msg void OnBnClickedCheck1ho();
	afx_msg void OnBnClickedCheck1sl();
	afx_msg void OnBnClickedCheck2cl();
	afx_msg void OnBnClickedCheck2ho();
	afx_msg void OnBnClickedCheck2sl();
	
	afx_msg void OnTRBNThumbPosChangingSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCheckLocation();
	afx_msg void OnBnClickedSavepres();
	afx_msg void OnDeltaposSpinOff(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinOn(NMHDR* pNMHDR, LRESULT* pResult);
};
