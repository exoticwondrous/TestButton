// @Exotic wondrous, All Rights Reserved.
// Based on the Visual C++ TestButton component.
//
// ahmdsmhmmd@gmail.com
// Telegram: https://t.me/exoticwondrous
//
#if !defined(AFX_HOVERBUTTON_H__E9C797B5_DB5E_446A_9C65_59DE50A8C46E__INCLUDED_)
#define AFX_HOVERBUTTON_H__E9C797B5_DB5E_446A_9C65_59DE50A8C46E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HoverButton.h : header file
//
// Messages used for communicate (Main windows and Button control).  
#define WM_MSGKILFOCUS (WM_USER + 0x01)
#define WM_MSGSETFOCUS (WM_USER + 0x02)
#define WM_ENDFLASHBTN (WM_USER + 0x03)
#define WM_UPDATEBTONS (WM_USER + 0x04)

/////////////////////////////////////////////////////////////////////////////
// CHoverButton window

class CHoverButton : public CBitmapButton
{
// Construction
public:
	CHoverButton();

// Attributes
public:
   void SetButton2dColor (COLORREF clrNormal = RGB(129,129,129),
	                      COLORREF clrHover  = RGB(11,12,244),
						  COLORREF clrSelect = RGB(244,244,244),
						  COLORREF clrDisable = RGB(129,129,129) );
   void SetButton2dShadow (COLORREF clrNormal = RGB(12,12,12),
	                       COLORREF clrHover = RGB(200,200,200),
						   COLORREF clrSelect = RGB(200,200,200),
						   COLORREF clrDisable = RGB(12,12,12) );
   
// Operations
public:
	BOOL m_bEn;
	BOOL m_bDe;
	BOOL m_bHo;
	BOOL m_bSl;
	BOOL m_bCl;
	BOOL m_bFl;
	BOOL m_bFo;
	int  m_nFlashFadeOut;
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHoverButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
 	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateDataButton();
	void BiltBlitAlpha(CDC* pDC, int w, int h, CDC* pDCMemory, int xSrc, int ySrc);
  	void SetWindowText (LPCTSTR lpString );
	WINDOWPLACEMENT GetWindowPlacementEx();
	void SetFlashButton(int nTimeOut);
	void SetFadeOutButton(int nSecc);
 	void LoadFileBitmap(LPCTSTR szPathFile,int nButtons);
	void SetCustomLoadBitmapMap (int nBitmapMapSet=1,int nDircetMap = 0 );
	
     BOOL InitCustomFont (int nSize=13, LPCTSTR fimalyFont = L"Tahoma",  BOOL bBold=TRUE,
					 BOOL bUnderLine =  FALSE ,
					 BOOL bItalic = FALSE  );
	BOOL IsButtonHighLight ();
	BOOL IsButtonSelected();
	void Show();
	void Hide();
	BOOL IsVisible();
	void SetButtonHighLight ( BOOL bHighLight = TRUE);
	void SetButtonSelected(BOOL bSelected);
	void SetCursor(LPCWSTR szCursor);
	//void SetCursor(UINT nCursor);
	void IniColorShadow ();
	void IniTabColorShadow();
	BOOL LoadBitmap ( UINT bitmapid , int nButton );
	CString GetCurrentImagePath();
	virtual ~CHoverButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHoverButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave (WPARAM wparam, LPARAM lparam);
	
	afx_msg LRESULT  OnMouseHover (WPARAM wparam, LPARAM lparam);
	afx_msg void   OnOK(){};
    afx_msg void   OnCancel(){};
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_nBitmapMapSet;
	int m_nDirectBitmapMap;
	BOOL m_bInitCustomFont;
    //NEW:
	BOOL m_bHighLight;
	// New2021
	BOOL m_bSelectedBtn;
	LPCWSTR m_szCursor;
	CFont m_cFont;
	WINDOWPLACEMENT m_lplacemet;
	BOOL m_bONBtn;
	BITMAP bitmapbits; // create instance object of bitmap info.
	//..........
 	void DrawText3dRct (CDC * pDC, LPRECT lpRect,
		                COLORREF clrText,
						COLORREF clr3dShadow);

	COLORREF m_clrNormal [ 2 ];
	COLORREF m_clrHover [2 ];
	COLORREF m_clrSelected [ 2 ];
	COLORREF m_clrDisabled [2 ];
	CString m_strTextButton;
	BOOL m_bHover;
	CSize m_ButtonSize;
	CBitmap m_Bmpbuttons;
	BOOL m_bTracking;
	int  m_nFlashingIndex;
	int  m_nFadeOutSecc;
	LPCTSTR m_szPathFile;
	CRect m_rctbtn;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnBnClicked();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVERBUTTON_H__E9C797B5_DB5E_446A_9C65_59DE50A8C46E__INCLUDED_)
