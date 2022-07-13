
// TestButtonDlg.cpp : implementation file
//
// @Exotic wondrous, All Rights Reserved.
// Based on the Visual C++ TestButton component.
//
// ahmdsmhmmd@gmail.com
// Telegram: https://t.me/exoticwondrous

#include "pch.h"
#include "framework.h"
#include "TestButton.h"
#include "TestButtonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "SplashWnd.h"
#include "CDlgOptions.h"


// CTestButtonDlg dialog



CTestButtonDlg::CTestButtonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTBUTTON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 	m_hbkBitmap_close = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCEW(IDB_BITMAP_BKGROUNDCLOSE));
	m_hbkBitmap_open = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCEW(IDB_BITMAP_BKGROUNDOPEN));
	m_hBkBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_isDoorOpen = FALSE;
}

void CTestButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_BUTTON_ON, m_btnON);
	DDX_Control(pDX, IDC_BUTTON_OFF, m_btnOff);
	DDX_Control(pDX, IDCANCEL, m_btnExit);
	DDX_Control(pDX, IDC_OPTIONS, m_btnOptions);
	DDX_Control(pDX, IDC_MFCLINK1, m_mfclink);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestButtonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_ON, &CTestButtonDlg::OnBnClickedButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CTestButtonDlg::OnBnClickedButtonOff)
	ON_BN_CLICKED(IDCANCEL, &CTestButtonDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPTIONS, &CTestButtonDlg::OnBnClickedOptions)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTestButtonDlg message handlers
// CTestButtonDlg message handlers
LRESULT CTestButtonDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, lParam);
		break;

	case WM_ENDFLASHBTN:// Received from button handle if flashed done occur.
	{
		m_isDoorOpen = TRUE;
		Invalidate();
	}
	break;

	default:
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
BOOL CTestButtonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Show splash screen
	CSplashWnd::EnableSplashScreen();
	CSplashWnd::ShowSplashScreen(30, IDB_BITMAP_SPLASH, theApp.GetFileVersion(theApp.GetProgramDir() + L"\\" + MODULE_MAINAPP), this);

	// TODO: Add extra initialization 
	SetWindowText(L"TestButton 1.0.0.5");

	// make window layered
	ModifyStyleEx(NULL, WS_EX_LAYERED);
	SetLayeredWindowAttributes(RGB(255, 0, 255), 1, 1);
	GetClientRect(m_rct);// get client width and height in pixels


	// load option and Exit button image from resource.
	m_btnExit.SetCustomLoadBitmapMap(2, 1);
	m_btnExit.LoadBitmapW(IDB_BITMAP_BTNORG, 4);
	m_btnOptions.SetCustomLoadBitmapMap(2, 0);
	m_btnOptions.LoadBitmapW(IDB_BITMAP_BTNORG, 4);

	// get default path file location.
	m_strImagePath = theApp.GetProgramDir() + L"\\samples\\Normal.bmp";

	// get if exist from registry entry.
	m_strImagePath = theApp.GetProfileStringW(KEYMAIN, KEY_FPTHM, m_strImagePath);
	m_ButtonsCount = theApp.GetProfileIntW(KEYMAIN, KEY_BTNCT, 5);


	//load ON button image from file.
	m_btnON.SetCustomLoadBitmapMap(2, 0);
	m_btnON.LoadFileBitmap(m_strImagePath, m_ButtonsCount);
	m_btnON.SetCursor(IDC_HAND);

	//load OFF button image from file.
	m_btnOff.SetCustomLoadBitmapMap(2, 1);
	m_btnOff.LoadFileBitmap(m_strImagePath, m_ButtonsCount);
	m_btnOff.SetCursor(IDC_HAND);

	// is enabled in the registry ?
	m_btnON.EnableWindow(theApp.GetProfileIntW(KEYMAIN, KEY_1EN, TRUE));
	m_btnOff.EnableWindow(theApp.GetProfileIntW(KEYMAIN, KEY_2EN, TRUE));


	// make them in top z order as always.
	m_btnOff.SetWindowPos(&m_btnOptions, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
	m_btnON.SetWindowPos(&m_btnExit, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);

	// call function coordinate button location 
	UpdateButtonsLocation();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestButtonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestButtonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL CTestButtonDlg::OnEraseBkgnd(CDC* pDC)
{
	HDC hDC;
	hDC = CreateCompatibleDC(pDC->m_hDC);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(hDC, m_isDoorOpen ? m_hbkBitmap_open : m_hbkBitmap_close);
	BitBlt(pDC->m_hDC, 0, 0, m_rct.Width(), m_rct.Height(), hDC, 0, 0, SRCCOPY);
	SelectObject(hDC, OldBitmap);
	DeleteDC(hDC);
	return TRUE;// CDialog::OnEraseBkgnd(pDC);
}

// when click on ON button
void CTestButtonDlg::OnBnClickedButtonOn()
{

	m_btnOff.SetButtonHighLight(FALSE);
	m_btnOff.SetButtonSelected(FALSE);

	if (m_btnON.m_bFl)
		m_btnON.SetFlashButton(m_btnON.m_nFlashFadeOut);

}

// when click on OFF button
void CTestButtonDlg::OnBnClickedButtonOff()
{
	m_isDoorOpen = FALSE;
	m_btnON.SetButtonHighLight(FALSE);
	m_btnON.SetButtonSelected(FALSE);

	if (m_btnOff.m_bSl)
		m_btnOff.SetButtonHighLight();

	if (m_btnOff.m_bFo)
		m_btnOff.SetFadeOutButton(m_btnOff.m_nFlashFadeOut);


	Invalidate();
}


void CTestButtonDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


// MovePosCtrl: helps for move the control from location to same other control's location
void CTestButtonDlg::MovePosCtrl(CHoverButton* PosDlgMoveCtrl, CWnd* PosDlgToMoveCtrl)
{
	WINDOWPLACEMENT wp = {};
	WINDOWPLACEMENT wporg = {};

	wp.length = sizeof(WINDOWPLACEMENT);
	wporg.length = sizeof(WINDOWPLACEMENT);

	PosDlgToMoveCtrl->GetWindowPlacement(&wp);
	PosDlgMoveCtrl->GetWindowPlacement(&wporg);
	PosDlgMoveCtrl->SetWindowPos(NULL, wp.rcNormalPosition.left, wporg.rcNormalPosition.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
// RestorePosCtrl:Return the origin location. 
void CTestButtonDlg::RestorePosCtrl(CHoverButton* PosDlgMoveCtrl)
{
	WINDOWPLACEMENT m_lplacemet;
	m_lplacemet = PosDlgMoveCtrl->GetWindowPlacementEx();
	PosDlgMoveCtrl->SetWindowPos(NULL, m_lplacemet.rcNormalPosition.left, m_lplacemet.rcNormalPosition.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// when click on Option button
void CTestButtonDlg::OnBnClickedOptions()
{
	CDlgOptions optiondlg;

	if (optiondlg.DoModal() == IDOK)
	{
		m_strImagePath = optiondlg.m_strImagePath;
		m_ButtonsCount = theApp.GetProfileIntW(KEYMAIN, KEY_BTNCT, 5);

		m_btnON.SetCustomLoadBitmapMap(2, 0);
		m_btnON.LoadFileBitmap(m_strImagePath, m_ButtonsCount);
		m_btnON.SetCursor(IDC_HAND);

		m_btnOff.SetCustomLoadBitmapMap(2, 1);
		m_btnOff.LoadFileBitmap(m_strImagePath, m_ButtonsCount);
		m_btnOff.SetCursor(IDC_HAND);

		m_btnON.UpdateDataButton();
		m_btnOff.UpdateDataButton();


		UpdateButtonsLocation();

		m_isDoorOpen = false; //Used as flag for load another image background.

		Invalidate();
	}


}

void CTestButtonDlg::UpdateButtonsLocation()
{
	int nBtnslocation = theApp.GetProfileIntW(KEYMAIN, KEY_LOCAT, 1);

	if (nBtnslocation == 0) {
		MovePosCtrl(&m_btnON, GetDlgItem(IDC_BUTTON_TEMPON));
		MovePosCtrl(&m_btnOff, GetDlgItem(IDC_BUTTON_TEMPOFF));

	}
	else
	{
		RestorePosCtrl(&m_btnON);
		RestorePosCtrl(&m_btnOff);
	}
}

void CTestButtonDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// clean up  
	DeleteObject(m_hbkBitmap_close);
	DeleteObject(m_hbkBitmap_open);
	DeleteObject(m_hBkgrBitmap);
	DeleteObject(m_hBkBrush);
}

