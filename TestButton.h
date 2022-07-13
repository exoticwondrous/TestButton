
// TestButton.h : main header file for the PROJECT_NAME application
//
// @Exotic wondrous, All Rights Reserved.
// Based on the Visual C++ TestButton component.
//
// ahmdsmhmmd@gmail.com
// Telegram: https://t.me/exoticwondrous

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTestButtonApp:
// See TestButton.cpp for the implementation of this class
//
typedef int (WINAPI* GdiplusStartupType)(ULONG_PTR*, LPVOID, LPVOID);
typedef VOID(WINAPI* GdiplusShutdownType)(ULONG_PTR);
typedef int (WINGDIPAPI* GdipCreateBitmapFromFileType)(LPVOID, LPVOID);
typedef int (WINGDIPAPI* GdipCreateHBITMAPFromBitmapType)(LPVOID, LPVOID, DWORD);
typedef int (WINGDIPAPI* GdipDisposeImageType)(LPVOID);


// key registry data exchange
#define KEYPRES  L"Persistence"
#define KEYMAIN  L"Options"
#define KEY_1EN   L"Button Enabled[ON]"
#define KEY_1DS   L"Button Disabled[ON]"
#define KEY_1HO   L"Button Hovered[ON]"
#define KEY_1CL   L"Button Clicked[ON]"
#define KEY_1FL   L"Button Flashed[ON]"
#define KEY_1SL   L"Button Selected[ON]"

#define KEY_2EN   L"Button Enabled[OFF]"
#define KEY_2DS   L"Button Disabled[OFF]"
#define KEY_2HO   L"Button Hovered[OFF]"
#define KEY_2CL   L"Button Clicked[OFF]"
#define KEY_2FO   L"Button Fadeout[OFF]"
#define KEY_2SL   L"Button Selected[OFF]"

#define KEY_1TMFL  L"FlashTimeout-ON"
#define KEY_2TMFO  L"FadeTimeout-OFF"
#define KEY_FPTHM  L"ButtonName"
#define KEY_BTNCT  L"ButtonsCount"
#define KEY_LOCAT  L"ButtonLocation" 
#define KEY_PRTYP  L"KeyPresType"

#pragma comment(lib,"Version.lib")
#define MODULE_MAINAPP L"TestButton.exe"

class CTestButtonApp : public CWinApp
{
public:
	CTestButtonApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL IsFileExist(CString strFullFileName);
	CString GetFileVersion(LPCWSTR szlpFileName);
	CString GetProgramDir();
	void DlgTransparent(HWND hWnd, DWORD nTransparent);
	HBITMAP LoadPictureFile(LPCTSTR szFile);
	void InitGdiPlus();
	void UnInitGdiPlus();

	DECLARE_MESSAGE_MAP()

protected:
	HMODULE m_hinstGDI;
	ULONG_PTR token;
};

extern CTestButtonApp theApp;
