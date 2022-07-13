// SplashWnd.cpp : implementation file
//
// ©1998-2001 Codejock Software, All Rights Reserved.
// Based on the Visual C++ splash screen component.
//
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "SplashWnd.h"
#include "TestButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class
 
BOOL  CSplashWnd::m_bShowSplashWnd;
CSplashWnd* CSplashWnd::m_pSplashWnd;
BOOL CSplashWnd::m_bFileVersion = TRUE;
BOOL CSplashWnd::m_bLicensedName = TRUE;
 CSplashWnd::CSplashWnd()
{
  	m_bShow = FALSE;
	m_crTextCol = RGB(0, 0, 0);
	 
    nCurrStep = 100;
	
	// initialize the fonts:
	InitFonts();
 	m_sCompaneyName.LoadStringW(IDS_STRINGCOMPANYNAME);
	  
}

CSplashWnd::~CSplashWnd()
{
	// Clear the static window pointer.
	ASSERT(m_pSplashWnd == this);
	m_pSplashWnd = NULL;
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	m_bShowSplashWnd = bEnable;
}

BOOL CSplashWnd::ShowSplashScreen(UINT uTimeOut, UINT uBitmapID, CString strFileVers, CWnd* pParentWnd /*= NULL*/)
{
	ASSERT(uTimeOut && uBitmapID);
	
	if (!m_bShowSplashWnd || m_pSplashWnd != NULL)
	{
		return FALSE;
	}
	
	// Allocate a new splash screen, and create the window.
	m_pSplashWnd = new CSplashWnd;
	
	if (!m_pSplashWnd->m_bitmap.LoadBitmap(uBitmapID))
	{
		return FALSE;
	}
	
	BITMAP bm;
	m_pSplashWnd->m_bitmap.GetBitmap(&bm);
	
	CString strWndClass = AfxRegisterWndClass(0,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	
	if (!m_pSplashWnd->CreateEx(WS_EX_TOPMOST, strWndClass, NULL, WS_POPUP  | WS_VISIBLE,
		0, 0, 10, 10, pParentWnd->GetSafeHwnd(), NULL))
	{
		TRACE0("Failed to create splash screen.\n");
		delete m_pSplashWnd;
		return FALSE;
	}
	
	// Center the window.
	m_pSplashWnd->ShowWindow(SW_HIDE);
	m_pSplashWnd->SetWindowPos(&wndTop, 0 , 0, bm.bmWidth, bm.bmHeight, SWP_NOZORDER);
	m_pSplashWnd->CenterWindow();
	m_pSplashWnd->ShowWindow(SW_SHOW);
	m_pSplashWnd->m_sFileVersion = strFileVers;
	// Set a timer to destroy the splash screen.
	m_pSplashWnd->SetTimer(0, uTimeOut, NULL);
	return TRUE;
}

CSplashWnd * CSplashWnd::GetCurrentWindow()
{
  return (m_pSplashWnd);
}
BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	/*
	if (m_pSplashWnd == NULL)
		return FALSE;
		
		// If we get a keyboard or mouse message, hide the splash screen.
		if (pMsg->message == WM_KEYDOWN ||
		pMsg->message == WM_SYSKEYDOWN ||
		pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_RBUTTONDOWN ||
		pMsg->message == WM_MBUTTONDOWN ||
		pMsg->message == WM_NCLBUTTONDOWN ||
		pMsg->message == WM_NCRBUTTONDOWN ||
		pMsg->message == WM_NCMBUTTONDOWN)
		{
		m_pSplashWnd->HideSplashScreen();
		return TRUE;	// message handled here
		}
	*/
	return FALSE;	// message not handled
}

void CSplashWnd::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
	DestroyWindow();
    AfxGetMainWnd()->UpdateWindow();
}

void CSplashWnd::PostNcDestroy()
{
	delete this;
}

void CSplashWnd::OnPaint()
{
	if (!m_bShow)
		ShowWindow(SW_HIDE);
	
	CPaintDC dc(this);
	int nOldBkMode = 0, iX = 0, iY = 0;
	CDC dcImage;
	CRect rectC;
	GetClientRect(&rectC);
	ClientToScreen(rectC);
	int iCX = rectC.Width();
	int iCY = rectC.Height();
	
	if (dcImage.CreateCompatibleDC(&dc))
	{
		BITMAP bm;
		m_bitmap.GetBitmap(&bm);
		
		if (m_iX < bm.bmWidth)	
		{
			m_iX = bm.bmWidth;
			m_iY = bm.bmHeight;
		}
		// select color and mode for the text:
		dc.SetTextColor(m_crTextCol);
		nOldBkMode = dc.SetBkMode(TRANSPARENT);
		
		// select the font and save the default font:
		HFONT def_font;
		def_font = (HFONT) SelectObject(dc.m_hDC, m_Font.m_hObject);
		
		 
		
		if (m_bLicensedName)
		{
			// DrawText over bitmap
			m_csTextExt = dc.GetOutputTextExtent(m_sCompaneyName);
			dc.SetTextColor(RGB(154, 185, 215));
			dc.TextOut(18,
				iCY - 75,
				m_sCompaneyName);


			if (m_csTextExt.cx > iX)
				iX = m_csTextExt.cx;
			if (m_csTextExt.cy > iY)
				iY = m_csTextExt.cy;
		}
		
		if (m_bFileVersion)
		{
			(HFONT) SelectObject(dc.m_hDC, m_Font.m_hObject);
			// DrawText over bitmap
			m_csTextExt = dc.GetOutputTextExtent(m_sFileVersion);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOut(18,	
				iCY - 60,
				m_sFileVersion);
			
			if (m_csTextExt.cx > iX)
				iX = m_csTextExt.cx;
			if (m_csTextExt.cy > iY)
				iY = m_csTextExt.cy;
		}
		
		// re-select the old objects and clean up:
		dc.SetBkMode(nOldBkMode);
		SelectObject(dc.m_hDC , def_font);
		
		if (m_iX<iX || m_iY < iY)
		{
			m_iX = iX + 50;
			m_iY = iY*2;
			SetWindowPos(&wndTop, 0, 0, m_iX, m_iY, SWP_NOZORDER);
			CenterWindow();
			RedrawWindow();
		}
		
		if (!m_bShow) 
		{
			ShowWindow(SW_SHOW);
			m_bShow = TRUE;
		}
	}
}



void CSplashWnd::InitFonts()
{
    VERIFY(m_Font.CreateFont
		(13,
		0,
		0,
		0,
		FW_MEDIUM,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		_T("Tahoma")));
}


BOOL CSplashWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO:
	
	CRect rect, rect2;    // We use rect to get the client area size
	GetClientRect(rect);
	
	CBitmap* pbmpOldBitmap1;
	CBitmap bmpMainBitmap2;
	CBitmap* pbmpOldBitmap2;
	CDC dcMem1;
	CDC dcMem2;
	
	dcMem1.CreateCompatibleDC(NULL); // Create double CDCs
	dcMem2.CreateCompatibleDC(NULL);
	
	// We create an empty bitmap of the client rect size
	bmpMainBitmap2.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	
	// Select the bitmaps
	pbmpOldBitmap1 = dcMem1.SelectObject(&m_bitmap);
	pbmpOldBitmap2 = dcMem2.SelectObject(&bmpMainBitmap2);
	
	dcMem1.GetClipBox(rect2);
	// We stretch the small bitmap to the background
	dcMem2.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem1, 0, 0, rect2.Width(), rect2.Height(), SRCCOPY);
	
	// We blit the big one to the screen
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem2, 0, 0, SRCCOPY);
	
	// Cleaning up
	dcMem1.SelectObject(pbmpOldBitmap1);
	dcMem1.DeleteDC();
	dcMem2.SelectObject(pbmpOldBitmap2);
	dcMem2.DeleteDC();	
	
	return TRUE;
	// return CWnd::OnEraseBkgnd(pDC);
}


LRESULT CSplashWnd::SplashWinProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_pSplashWnd->WindowProc(message, wParam, lParam);
}

void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{

	nCurrStep--;
	if (nCurrStep <= 0)
	{
		KillTimer(nIDEvent);
		// Destroy the splash screen window.
		HideSplashScreen();
	}
	else {
		theApp.DlgTransparent(m_hWnd, nCurrStep);
	}
}

 


