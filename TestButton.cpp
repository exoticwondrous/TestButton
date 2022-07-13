
// TestButton.cpp : Defines the class behaviors for the application.
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestButtonApp

BEGIN_MESSAGE_MAP(CTestButtonApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestButtonApp construction
using namespace Gdiplus;

CTestButtonApp::CTestButtonApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTestButtonApp object

CTestButtonApp theApp;


// CTestButtonApp initialization

BOOL CTestButtonApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Exoticwondrous"));

	CTestButtonDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
BOOL CTestButtonApp::IsFileExist(CString strFullFileName)
{
	HANDLE hFile = NULL; BOOL bResult = FALSE;
	WIN32_FIND_DATAW dw;

	hFile = ::FindFirstFile(strFullFileName, &dw);

	if (hFile != INVALID_HANDLE_VALUE) {
		//CloseHandle(hFile);
		bResult = TRUE;
	}
	return (bResult);
}
CString CTestButtonApp::GetFileVersion(LPCWSTR szlpFileName)
{
	DWORD  verHandle = 0;
	UINT   size = 0;
	LPBYTE lpBuffer = NULL;
	CString strRet(L"");
	DWORD  verSize = GetFileVersionInfoSize(szlpFileName, &verHandle);

	if (verSize != NULL)
	{
		LPSTR verData = new char[verSize];

		if (GetFileVersionInfo(szlpFileName, verHandle, verSize, verData))
		{
			if (VerQueryValue(verData, L"\\", (VOID FAR * FAR*) & lpBuffer, &size))
			{
				if (size)
				{
					VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{

						// Doesn't matter if you are on 32 bit or 64 bit,
						// DWORD is always 32 bits, so first two revision numbers
						// come from dwFileVersionMS, last two come from dwFileVersionLS
						strRet.Format(L"(Build Ver: %d.%d.%d.%d)",
							(verInfo->dwFileVersionMS >> 16) & 0xffff,
							(verInfo->dwFileVersionMS >> 0) & 0xffff,
							(verInfo->dwFileVersionLS >> 16) & 0xffff,
							(verInfo->dwFileVersionLS >> 0) & 0xffff
						);
					}
				}
			}
		}
		delete[] verData;
	}
	return strRet;
}

CString CTestButtonApp::GetProgramDir()
{
	CString RtnVal;
	TCHAR    FileName[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), FileName, MAX_PATH);
	RtnVal = FileName;
	RtnVal = RtnVal.Left(RtnVal.ReverseFind('\\'));
	return RtnVal;
}

void CTestButtonApp::DlgTransparent(HWND hWnd, DWORD nTransparent)
{
	if (nTransparent == 0) // not transparent
	{
		LONG lExStyle;
		lExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		lExStyle &= ~0x80000;
		::SetWindowLong(hWnd, GWL_EXSTYLE, lExStyle);
	}
	else
	{
		LONG lExStyle;
		lExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		::SetWindowLong(hWnd, GWL_EXSTYLE, lExStyle | 0x80000);
	}

	SetLayeredWindowAttributes(hWnd, 0, (BYTE)nTransparent, 2);
}

// using GDI+
HBITMAP CTestButtonApp::LoadPictureFile(LPCTSTR szFile)
{



	InitGdiPlus();

	HBITMAP hbitmap = NULL;
	// If it is suspected that the file type isn't supported, try to use GdiPlus if available.
	// If it's not available, fall back to the old method in case the filename doesn't properly
	// reflect its true contents (i.e. in case it really is a JPG/GIF/BMP internally).
	// If the below LoadLibrary() succeeds, either the OS is XP+ or the GdiPlus extensions have been
	// installed on an older OS.
	if (m_hinstGDI)
	{
		TRACE(L"\nGdiplusStartupInput::FilePath[%s]\n", szFile);

		// LPVOID and "int" are used to avoid compiler errors caused by... namespace issues?
		GdipCreateBitmapFromFileType DynGdipCreateBitmapFromFile = (GdipCreateBitmapFromFileType)GetProcAddress(m_hinstGDI, "GdipCreateBitmapFromFile");
		GdipCreateHBITMAPFromBitmapType DynGdipCreateHBITMAPFromBitmap = (GdipCreateHBITMAPFromBitmapType)GetProcAddress(m_hinstGDI, "GdipCreateHBITMAPFromBitmap");
		GdipDisposeImageType DynGdipDisposeImage = (GdipDisposeImageType)GetProcAddress(m_hinstGDI, "GdipDisposeImage");

		ULONG_PTR token;
		GdiplusStartupInput gdi_input;
		GpBitmap* pgdi_bitmap;


		if (DynGdipCreateBitmapFromFile((LPVOID)szFile, &pgdi_bitmap) == Gdiplus::Ok)
		{
			if (DynGdipCreateHBITMAPFromBitmap(pgdi_bitmap, &hbitmap, 0) != Gdiplus::Ok)
				hbitmap = NULL; // Set to NULL to be sure.
			DynGdipDisposeImage(pgdi_bitmap); // This was tested once to make sure it really returns Gdiplus::Ok.

		}
	}

	if (hbitmap == NULL) //if GDI+ failed, try to load bitmap:24 bit if is possible 
		hbitmap = (HBITMAP)LoadImage(NULL, szFile, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_LOADMAP3DCOLORS | LR_DEFAULTCOLOR);

	UnInitGdiPlus();

	return(hbitmap);
}

void CTestButtonApp::InitGdiPlus()
{


	m_hinstGDI = LoadLibrary(L"gdiplus");


	if (m_hinstGDI)
	{
		// LPVOID and "int" are used to avoid compiler errors caused by... namespace issues?
		GdiplusStartupType DynGdiplusStartup = (GdiplusStartupType)GetProcAddress(m_hinstGDI, "GdiplusStartup");

		Gdiplus::GdiplusStartupInput gdi_input;

		if (DynGdiplusStartup && DynGdiplusStartup(&token, &gdi_input, NULL) == Gdiplus::Ok)
		{
			TRACE(L"\nGdiplusStartupInput::START\n");
		}
	}

}
void CTestButtonApp::UnInitGdiPlus()
{

	// The current thought is that shutting it down every time conserves resources.  If so, it
	// seems justified since it is probably called infrequently by most scripts:
	if (m_hinstGDI)
	{
		GdiplusShutdownType DynGdiplusShutdown = (GdiplusShutdownType)GetProcAddress(m_hinstGDI, "GdiplusShutdown");
		DynGdiplusShutdown(token);
		TRACE(L"\nGdiplusStartupInput::FREELIB\n");
	}
}
