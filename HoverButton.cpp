
// HoverButton.cpp : implementation file
//
// @Exotic wondrous, All Rights Reserved.
// Based on the Visual C++ TestButton component.
//
// ahmdsmhmmd@gmail.com
// Telegram: https://t.me/exoticwondrous
//
#include "pch.h"
#include "TestButton.h"
#include "TestButtonDlg.h"
#include "HoverButton.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHoverButton

CHoverButton::CHoverButton()
{
   // hover button 
   m_bHover = FALSE; // will set true if button ready hovering.
   m_bTracking = FALSE; // if mouse move on button.
   //NEW....
   m_bHighLight = FALSE; // will set true if button ready highlight.
   // NEW 2021
   m_bSelectedBtn = FALSE;
   m_cFont.m_hObject = NULL;
   m_bInitCustomFont = FALSE; // flag will be true if InitCustomFont called.
   m_nBitmapMapSet  = 1;      // one side map bitmap load.
   m_nDirectBitmapMap = 0; // default direct on bitmap;    
}

CHoverButton::~CHoverButton()
{
  m_bTracking = FALSE;
  m_bHover = FALSE;
  m_bHighLight = FALSE;
  m_bSelectedBtn = FALSE;
}


BEGIN_MESSAGE_MAP(CHoverButton, CButton)
	//{{AFX_MSG_MAP(CHoverButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE ( WM_MOUSELEAVE , OnMouseLeave)
	ON_MESSAGE ( WM_MOUSEHOVER, OnMouseHover )
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
//	ON_CONTROL_REFLECT(BN_CLICKED, &CHoverButton::OnBnClicked)
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHoverButton message handlers

void CHoverButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
// NEW set this variables to initialize on an attached window 
   // hover button 
   m_bHover = FALSE; // will set true if button ready hovering.
   m_bTracking = FALSE; // if mouse move on button.
   m_szCursor = NULL;
	// get button text 
   // GetWindowText (m_strTextButton );
      
   m_lplacemet = GetWindowPlacementEx();
   
   GetClientRect(m_rctbtn);

   UpdateDataButton();

	CButton::PreSubclassWindow();
}
 

void CHoverButton::UpdateDataButton()
{
	m_bONBtn = GetDlgCtrlID() == IDC_BUTTON_ON ? TRUE : FALSE;

	m_bEn = theApp.GetProfileIntW(KEYMAIN, m_bONBtn ? KEY_1EN : KEY_2EN, TRUE);
	m_bDe = theApp.GetProfileIntW(KEYMAIN, m_bONBtn ? KEY_1DS : KEY_2DS, TRUE);
	m_bHo = theApp.GetProfileIntW(KEYMAIN, m_bONBtn ? KEY_1HO : KEY_2HO, TRUE);
	m_bSl = theApp.GetProfileIntW(KEYMAIN, m_bONBtn ? KEY_1SL : KEY_2SL, TRUE);
	m_bCl = theApp.GetProfileIntW(KEYMAIN, m_bONBtn ? KEY_1CL : KEY_2CL, TRUE);
	m_bFl = theApp.GetProfileIntW(KEYMAIN, KEY_1FL , TRUE);
	m_bFo = theApp.GetProfileIntW(KEYMAIN, KEY_2FO, TRUE);

	m_nFlashFadeOut = theApp.GetProfileIntW(KEYMAIN, m_bONBtn? KEY_1TMFL: KEY_2TMFO,
		                            m_bONBtn?9:2);

	// disabled button when recored is zero En from registry  
	if(GetDlgCtrlID() != IDCANCEL && GetDlgCtrlID() != IDC_OPTIONS)
	EnableWindow(m_bEn);

	SetButtonHighLight(FALSE);
	SetButtonSelected(FALSE);
	m_bHover = FALSE;
	m_bSelectedBtn = FALSE;
	m_bHighLight = FALSE;

	Invalidate();
}
 
void CHoverButton::BiltBlitAlpha(CDC *pDC, int w, int h, CDC* pDCMemory, int xSrc, int ySrc)
{
	
  	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 0xFF, AC_SRC_ALPHA };

	pDC->AlphaBlend(0, 0, w, h, pDCMemory, xSrc, ySrc, w, h, bf);

	
}

void CHoverButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    // get CDC context device of button from it handle
    CDC * MyPDC = CDC::FromHandle (lpDrawItemStruct->hDC);
    
	CDC * pMemDC = new CDC;
    pMemDC->CreateCompatibleDC (MyPDC); // create Dc in memory.
    // NEW m_nDirectBitmapMap by one if it default state.
	int nSpaceToMoveDirect = 0;
	if(m_nBitmapMapSet>1 ) 
		{
          nSpaceToMoveDirect = m_nDirectBitmapMap *m_ButtonSize.cx;
		}
    
	// set background mode : transparent(no color).
 	pMemDC->SetBkMode ( TRANSPARENT);
    CBitmap * pOldBitmap; // create bitmap instance for old bitmap.
	// select new device to draw a bitmap.
    pOldBitmap = pMemDC->SelectObject (&m_Bmpbuttons);
	
	// normal status
	BiltBlitAlpha(MyPDC, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC,
		             nSpaceToMoveDirect,0);

	
	if (m_bHighLight)//when is highlight 
		{

		BiltBlitAlpha(MyPDC, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC,
			nSpaceToMoveDirect, m_ButtonSize.cy);
			  
		}
	
	 
	if (lpDrawItemStruct->itemState & ODS_SELECTED && m_bCl)// when clicked status
	{

		BiltBlitAlpha(MyPDC, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC,
			nSpaceToMoveDirect, m_ButtonSize.cy);
		  
	}
	 
	if (m_bSelectedBtn && m_bSl)// when selected event status 
	{

		BiltBlitAlpha(MyPDC, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC,
			nSpaceToMoveDirect, m_ButtonSize.cy*4);
		  
	}

	if (m_bHover && m_bHo)// when button is hovered by mouse
	{
		BiltBlitAlpha(MyPDC, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC,
			nSpaceToMoveDirect, m_ButtonSize.cy * 3);

	}
	if (!IsWindowEnabled() && m_bDe)// if disabled status 
	{

		BiltBlitAlpha(MyPDC, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC,
			nSpaceToMoveDirect, m_ButtonSize.cy*2);	 
	}


	//[Option and Exit button methods]
	///////////////////////////////////////////////////////////////////////
	if (GetDlgCtrlID() == IDCANCEL || GetDlgCtrlID() == IDC_OPTIONS)
	{
		// when a button is selected or when state of button highlight.
		if (lpDrawItemStruct->itemState & ODS_SELECTED || m_bHighLight)//<-NEW
		{

			// when a button clicked.
			MyPDC->BitBlt(0, 0,  // x,y coordinate
				m_ButtonSize.cx, // size of button width.
				m_ButtonSize.cy,// size of button height
				pMemDC,         // get info from memory  
				nSpaceToMoveDirect, //NEW// same as nSpaceToMoveDirect.  
				m_ButtonSize.cy * 2,// NEW// increase tow button              
				SRCCOPY);       // type of copy bit-bits as origin. 

		}
		// when a button is disabled.
		else if (lpDrawItemStruct->itemState & ODS_DISABLED)
		{
			MyPDC->BitBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, nSpaceToMoveDirect, m_ButtonSize.cy * 3, SRCCOPY);
		}
		else // normal button mode.
		{

			if (m_bHover) // if a button hovered.	 
			{
				MyPDC->BitBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, nSpaceToMoveDirect, m_ButtonSize.cy, SRCCOPY);
			}
			else // A normal mode 
			{
				MyPDC->BitBlt(0, 0, m_ButtonSize.cx, m_ButtonSize.cy, pMemDC, nSpaceToMoveDirect, 0, SRCCOPY);
			}

		}
	}
  // finally clean up 
    pMemDC ->SelectObject (pOldBitmap);
	delete pMemDC;
}

void CHoverButton::PostNcDestroy() 
{
	// Delete bitmap object when window destroy.
	m_Bmpbuttons.DeleteObject ();
	m_cFont.DeleteObject();
	m_bTracking = FALSE;
	CButton::PostNcDestroy();
}

void CHoverButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    
   if (!m_bTracking && !m_bHighLight )
		{
          TRACKMOUSEEVENT  tme; // create instance of struct mouse event
		  tme.cbSize = sizeof(tme); // calculate it size
		  tme.hwndTrack = m_hWnd; // get handle window of this button
		  tme.dwFlags = TME_LEAVE|TME_HOVER; // set tow flags hover and leave action
		  tme.dwHoverTime = 1;// set time hover
          
		  // copy struct to TrackMouseEvent function.
		  // returns true if mouse on button.
		  m_bTracking = _TrackMouseEvent (&tme);
		}
  
   if (m_szCursor != NULL)
   {
	   HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(m_szCursor);
	   ::SetCursor(hCursor);
   }

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CHoverButton::OnMouseHover(WPARAM wparam,LPARAM lparam)
{
	 
		// if button is hover 
		m_bHover = TRUE;
		// redraw window 
		Invalidate();
	 
  AfxGetMainWnd()->PostMessageW(WM_MSGSETFOCUS, GetDlgCtrlID(), 0L);
  return (0);//unused.

}

LRESULT CHoverButton::OnMouseLeave (WPARAM wparam,LPARAM lparam)
{
	 
		// when mouse leave button
		m_bTracking = FALSE;
		m_bHover = FALSE;
		Invalidate();
        AfxGetMainWnd()->PostMessageW(WM_MSGKILFOCUS, GetDlgCtrlID(), 0L);
  return (0);//unused.
}
CString CHoverButton::GetCurrentImagePath()
{
	return (m_szPathFile);
}

void CHoverButton::LoadFileBitmap(LPCTSTR szPathFile, int nButtons)
{
	if (m_Bmpbuttons.GetSafeHandle() != NULL)
		m_Bmpbuttons.Detach();

	if (!theApp.IsFileExist(szPathFile))
	{
 		Invalidate();
		return;
	}
	m_szPathFile = m_szPathFile;
	HBITMAP hBitmap = theApp.LoadPictureFile(szPathFile);

	//hBitmap = CreateBitmapMask(hBitmap, RGB(0, 0, 0));
	BOOL bResult = m_Bmpbuttons.Attach(hBitmap);
	VERIFY(bResult);
	if (!bResult)
		return;
 
   // retrieve bitmap informations
	m_Bmpbuttons.GetBitmap(&bitmapbits);
	// Calculate size of buttons.
	m_ButtonSize.cy = bitmapbits.bmHeight / nButtons; // divide Hight of image on button number used.; 
	m_ButtonSize.cx = bitmapbits.bmWidth / m_nBitmapMapSet; // divide it on Mapdirect mode default =1.

   // set window positions (size, move, etc..)
	SetWindowPos(NULL, 0, 0, m_ButtonSize.cx,
		m_ButtonSize.cy,
		SWP_NOMOVE | SWP_NOOWNERZORDER);

	Invalidate();
	Invalidate();
}

// Load bitmap from resource.
// bitmapid: id bitmap on recourse file.
// nButton: number of button in this bitmap.
// GLOBAL: call this function out-side this class.
BOOL CHoverButton::LoadBitmap(UINT bitmapid, int nButton)
{
	if (m_Bmpbuttons.GetSafeHandle() != NULL)
		m_Bmpbuttons.Detach();
   // load bitmap from resource then attach it.
   BOOL bResult = m_Bmpbuttons.Attach (LoadImage (AfxGetInstanceHandle (),
	   MAKEINTRESOURCE (bitmapid), // name of resource
	   IMAGE_BITMAP,  // type of load image  bitmap
	   0,            // not used for cursor or icon 
	   0,            // not used for cursor or icon
	   LR_DEFAULTCOLOR) );//load with same attributes image color.

   VERIFY(bResult);
   if (!bResult)
	   return FALSE;

   BITMAP bitmapbits; // create instance object of bitmap info.
   // retrieve bitmap informations
   m_Bmpbuttons.GetBitmap (&bitmapbits);
   // Calculate size of buttons.
   m_ButtonSize.cy = bitmapbits.bmHeight / nButton; // divide Hight of image on button number used.; 
   m_ButtonSize.cx = bitmapbits.bmWidth / m_nBitmapMapSet; // divide it on Mapdirect mode default =1.
   
  // set window positions (size, move, etc..)
   SetWindowPos (NULL,0,0, m_ButtonSize.cx,
	                       m_ButtonSize.cy,
						   SWP_NOMOVE|SWP_NOOWNERZORDER );

   Invalidate();
   return (bResult); // returns true if attached succeed.
}

// Colorized even normal and shadow set.
// GLOBAL: Calls outside this class
void CHoverButton::IniColorShadow()
{
     // normal colors set.
        m_clrNormal [0] = RGB(250,250,250);
		m_clrHover [0]  = RGB(255,244,10);
		m_clrSelected [0] = RGB(244,244,244);
		m_clrDisabled [0] = RGB(189,189,189);
 
    // shadow colors set
		m_clrNormal [1] = RGB(250,250,126);
		m_clrHover [1]  = RGB(240,240,240);
		m_clrSelected [1] = RGB(200,200,200);
		m_clrDisabled [1] = RGB(244,244,244);
		
		// Ini Custom fonts
		InitCustomFont(16,L"Tahoma",TRUE);
}

// Colorized even normal and shadow set.
// GLOBAL: Calls outside this class
void CHoverButton::IniTabColorShadow()
{
     // normal colors set.
        m_clrNormal [0] = RGB(250/2,250/2,250/2);
		m_clrHover [0]  = RGB(255,10,10);
		m_clrSelected [0] = RGB(244,244,244);
		m_clrDisabled [0] = RGB(129,129,129);
 
    // shadow colors set
		m_clrNormal [1] = RGB(250,250,250);
		m_clrHover [1]  = RGB(240,240,240);
		m_clrSelected [1] = RGB(200,200,200);
		m_clrDisabled [1] = RGB(12,12,12);

   	// Ini Custom fonts
	   InitCustomFont(13);

}

// Draw text string over button.
void CHoverButton::DrawText3dRct (CDC * pDC, LPRECT lpRect,
		                COLORREF clrText,
						COLORREF clr3dShadow)
{
   // check if error occurred while debug configured.
   // if and if any not valid Debug mode will break here.
   ASSERT ( pDC !=NULL); //check pDC pointer is Valid
   ASSERT (!IsRectEmpty (lpRect)); // Is rect not Empty 
   
   // create tow instances of rect client window
   CRect rctStatic = *lpRect;
   CRect shadowRctDraw = *lpRect;
   
   const int nLeft = 1;// NEW// set button same as Top.
   const int nTop = 1;
   // Intend increase and decrease of shadow color text.
   // to make shadow 3D.
   shadowRctDraw.left -= nLeft;//decrease 2 pixel of let window
   shadowRctDraw.top += nTop; // increase 1 pixel of top window
   
   // make text background transparent (no color)
    pDC ->SetBkMode ( TRANSPARENT );
   // set color of text as requested.
   pDC->SetTextColor (clr3dShadow);
   
   // NEW .....
   // add new code to init font on current object
   CFont * pOldFont = NULL;
   if( m_bInitCustomFont)
          pOldFont = pDC->SelectObject (&m_cFont);

   // draw text string with shadow color
   pDC->DrawText ((LPCTSTR)m_strTextButton, -1,shadowRctDraw,
	            DT_INTERNAL|DT_VCENTER|DT_CENTER|DT_SINGLELINE);

   
   // set color of text as requested.
   pDC->SetTextColor (clrText);

   // draw text string with normal color
   pDC->DrawText ((LPCTSTR)m_strTextButton, -1,rctStatic,
	            DT_INTERNAL|DT_VCENTER|DT_CENTER|DT_SINGLELINE);

   
   if( m_bInitCustomFont) // removed old font object.
	   pDC->SelectObject (pOldFont ); 

}

// Set 2D Color over button. 
// GLOBAL: Calls outside this class
void CHoverButton::SetButton2dColor (COLORREF clrNormal,
	                      COLORREF clrHover  ,
						  COLORREF clrSelect ,
						  COLORREF clrDisable  )
{
     m_clrNormal [0] = clrNormal;
	 m_clrHover [0] = clrHover;
	 m_clrSelected [0] = clrSelect;
	 m_clrDisabled [0] = clrDisable;

}
// Set 2D Color shadow over button.
// GLOBAL: Calls outside this class
void CHoverButton::SetButton2dShadow (COLORREF clrNormal ,
	                       COLORREF clrHover ,
						   COLORREF clrSelect ,
						   COLORREF clrDisable )

{
     m_clrNormal [1] = clrNormal;
	 m_clrHover [1] = clrHover;
	 m_clrSelected [1] = clrSelect;
	 m_clrDisabled [1] = clrDisable;
   
}



// NEW.......
//------------------------------------------------------

// GLOBAL: call this function out-side this class.
void CHoverButton::SetButtonHighLight(BOOL bHighLight)
{
   m_bHighLight = bHighLight;  
   Invalidate();
}

void CHoverButton::SetButtonSelected(BOOL bSelected)
{
	m_bSelectedBtn = bSelected;
	Invalidate();
}

void CHoverButton::SetCursor(LPCWSTR szCursor)
{
	m_szCursor = szCursor;
}

// GLOBAL: call this function out-side this class.
BOOL CHoverButton::IsButtonHighLight()
{
  return (m_bHighLight);
}

BOOL CHoverButton::IsButtonSelected()
{
	return (m_bSelectedBtn);
}

void CHoverButton::Show()
{
	if (IsWindow(this->m_hWnd))ShowWindow(SW_SHOW);
}

void CHoverButton::Hide()
{
	if (IsWindow(this->m_hWnd))ShowWindow(SW_HIDE);
}

BOOL CHoverButton::IsVisible()
{
	if (IsWindow(this->m_hWnd))
		return (IsWindowVisible());
	return FALSE;
}



BOOL CHoverButton::InitCustomFont (int nSize, LPCTSTR szfimalyFont,  BOOL bBold ,   
					 BOOL bUnderLine ,
					 BOOL bItalic )
{
 if(szfimalyFont==NULL)
     return FALSE;

 BOOL bResult =  m_cFont.CreateFont (nSize,
	                  0,
					  0,
					  0,
					  bBold?FW_BOLD:FW_NORMAL,
                      bItalic,
					  bUnderLine,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  szfimalyFont);
  m_bInitCustomFont = bResult;
 return (bResult);
}

// load bitmap as action set.
void CHoverButton::SetCustomLoadBitmapMap(int nMapBitmapSet, int nDircetMap)
{
     m_nBitmapMapSet = nMapBitmapSet;
     m_nDirectBitmapMap =   nDircetMap;
} 

// [Not used]set window text over button
void CHoverButton::SetWindowText(LPCTSTR lpString)
{ 
  m_strTextButton =  lpString ;
  Invalidate(); 
}

WINDOWPLACEMENT CHoverButton::GetWindowPlacementEx()
{
	if (m_lplacemet.length == 0)
	{
		m_lplacemet = {};
		m_lplacemet.length = sizeof(WINDOWPLACEMENT);
		::GetWindowPlacement(m_hWnd, &m_lplacemet);
		return m_lplacemet;
	}
	else
		return m_lplacemet;
}
 // Timeout from 1 to 10 each half secs
void CHoverButton::SetFlashButton(int nTimeOut)
{
	if (m_bFl)
	{
		KillTimer(100);
		m_nFlashingIndex = nTimeOut;
		SetTimer(100, 100, NULL);
	}
}
void CHoverButton::SetFadeOutButton(int nSecc)
{
	if (m_bFo)
	{
		KillTimer(200);
		m_nFadeOutSecc = nSecc;
		SetTimer(200, 1000, NULL);
	}
}


BOOL CHoverButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CHoverButton::OnTimer(UINT_PTR nIDEvent)
{

	if (nIDEvent == 100)
	{
		if (m_nFlashingIndex > 0 && m_nFlashingIndex < 10)
		{
			m_bHover = !m_bHover;
			m_nFlashingIndex--;
 			Invalidate();
		}
		else {
			KillTimer(nIDEvent);
			m_bHover = FALSE;
			Invalidate();
			if (m_bSl)SetButtonSelected(TRUE);
			else if (m_bHo || m_bFl)SetButtonHighLight();
			 AfxGetMainWnd()->PostMessageW(WM_ENDFLASHBTN, 0L, 0L);
 		}
	}
	else if (nIDEvent == 200)
	{
		if (m_nFadeOutSecc > 0 && m_nFadeOutSecc < 10)
		{
 			m_nFadeOutSecc--;
 		}
		else {
			KillTimer(nIDEvent);
 			SetButtonHighLight(FALSE);
			SetButtonSelected(FALSE);
		}
	}
	CBitmapButton::OnTimer(nIDEvent);
}



void CHoverButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (GetDlgCtrlID() != IDC_OPTIONS && GetDlgCtrlID() != IDCANCEL &&
		GetDlgCtrlID()!=IDC_BUTTON_OFF)
	{
		if (!m_bFl)
			AfxGetMainWnd()->PostMessageW(WM_ENDFLASHBTN, 0L, 0L);

		if (m_bSl)
		{
			m_bSelectedBtn = !m_bSelectedBtn;
		}
	}
	CBitmapButton::OnLButtonDown(nFlags, point);
}
