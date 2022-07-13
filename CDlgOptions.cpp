// COptions.cpp : implementation file
//
// @Exotic wondrous, All Rights Reserved.
// Based on the Visual C++ TestButton component.
//
// ahmdsmhmmd@gmail.com
// Telegram: https://t.me/exoticwondrous
//

#include "pch.h"
#include "TestButton.h"
#include "CDlgOptions.h"
#include "afxdialogex.h"


// COptions dialog

IMPLEMENT_DYNAMIC(CDlgOptions, CDialogEx)

CDlgOptions::CDlgOptions(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPTIONS, pParent)
	, m_edit1Flashout(9)
	, m_edit2Fladeout(1)
{
 }

CDlgOptions::~CDlgOptions()
{
}

void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_1EN, m_ch1En);
	DDX_Control(pDX, IDC_CHECK_1DE, m_ch1De);
	DDX_Control(pDX, IDC_CHECK_1HO, m_ch1Ho);
	DDX_Control(pDX, IDC_CHECK_1CL, m_ch1Cl);
	DDX_Control(pDX, IDC_CHECK_1FL, m_ch1Fl);
	DDX_Control(pDX, IDC_CHECK_1SL, m_ch1Sl);

	DDX_Control(pDX, IDC_CHECK_2EN, m_ch2En);
	DDX_Control(pDX, IDC_CHECK_2DE, m_ch2De);
	DDX_Control(pDX, IDC_CHECK_2HO, m_ch2Ho);
	DDX_Control(pDX, IDC_CHECK_2CL, m_ch2Cl);
	DDX_Control(pDX, IDC_CHECK_2FL, m_ch2Fo);
	DDX_Control(pDX, IDC_CHECK_2SL, m_ch2Sl);


	DDX_Control(pDX, IDC_MFCEDITBROWSE, m_editBrowserImg);

	DDX_Control(pDX, IDC_BUTTON_OFF, m_btnOFFHover);
	DDX_Control(pDX, IDC_BUTTON_ON, m_btnONHover);
	DDX_Text(pDX, IDC_EDIT_ON, m_edit1Flashout);
	DDV_MinMaxInt(pDX, m_edit1Flashout, 1, 9);
	DDX_Text(pDX, IDC_EDIT_OFF, m_edit2Fladeout);
	DDV_MinMaxInt(pDX, m_edit2Fladeout, 1, 9);
	DDX_Control(pDX, IDC_SPIN_OFF, m_SpingOFF);
	DDX_Control(pDX, IDC_SPIN_ON, m_SpingON);
	DDX_Control(pDX, IDC_SLIDER, m_SliderList);
	DDX_Control(pDX, IDC_CHECK_LOCATION, m_checkLocation);
}


BEGIN_MESSAGE_MAP(CDlgOptions, CDialogEx)
	ON_WM_DESTROY()
  ON_BN_CLICKED(IDOK, &CDlgOptions::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_MFCEDITBROWSE, &CDlgOptions::OnEnChangeMfceditbrowse)
	ON_BN_CLICKED(IDAPPLY, &CDlgOptions::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON_ON, &CDlgOptions::OnBnClickedButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CDlgOptions::OnBnClickedButtonOff)
	ON_BN_CLICKED(IDC_CHECK_2FL, &CDlgOptions::OnBnClickedCheck2fl)
	ON_BN_CLICKED(IDC_CHECK_1FL, &CDlgOptions::OnBnClickedCheck1fl)
	ON_BN_CLICKED(IDC_CHECK_2EN, &CDlgOptions::OnBnClickedCheck2en)
	ON_BN_CLICKED(IDC_CHECK_1EN, &CDlgOptions::OnBnClickedCheck1en)
	ON_BN_CLICKED(IDC_CHECK_1DE, &CDlgOptions::OnBnClickedCheck1de)
	ON_BN_CLICKED(IDC_CHECK_2DE, &CDlgOptions::OnBnClickedCheck2de)
	ON_BN_CLICKED(IDC_CHECK_1CL, &CDlgOptions::OnBnClickedCheck1cl)
	ON_BN_CLICKED(IDC_CHECK_1HO, &CDlgOptions::OnBnClickedCheck1ho)
	ON_BN_CLICKED(IDC_CHECK_1SL, &CDlgOptions::OnBnClickedCheck1sl)
	ON_BN_CLICKED(IDC_CHECK_2CL, &CDlgOptions::OnBnClickedCheck2cl)
	ON_BN_CLICKED(IDC_CHECK_2HO, &CDlgOptions::OnBnClickedCheck2ho)
	ON_BN_CLICKED(IDC_CHECK_2SL, &CDlgOptions::OnBnClickedCheck2sl)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER, &CDlgOptions::OnTRBNThumbPosChangingSlider)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_LOCATION, &CDlgOptions::OnBnClickedCheckLocation)
	ON_BN_CLICKED(IDC_SAVEPRES, &CDlgOptions::OnBnClickedSavepres)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFF, &CDlgOptions::OnDeltaposSpinOff)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ON, &CDlgOptions::OnDeltaposSpinOn)
  END_MESSAGE_MAP()


void CDlgOptions::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
}
// Return the name of section from registry by the image name.
CString CDlgOptions::GetPersSectionName(CString strPathfile)
{
	int nRight = strPathfile.ReverseFind('\\');
	CString strfName = strPathfile.Right(strPathfile.GetLength() - nRight - 1);
	CString strPath = CString(KEYPRES) + L"\\" + strfName;

	return(strPath);
}
// update the images's info by the file name
BOOL CDlgOptions::UpdatePersistence(CString strPathfile)
{
	CString strPath = GetPersSectionName(strPathfile);
	  theApp.GetSectionKey(strPath);
	  if(theApp.GetProfileIntW(strPath, KEY_PRTYP, -1)==-1)// is there any profile stored yet ?
	  {
 		  return FALSE;
	  }
	  
		
		m_SliderPos = theApp.GetProfileIntW(strPath, KEY_BTNCT, 5);

		m_nlocation = theApp.GetProfileIntW(strPath, KEY_LOCAT, 1);

		UpdateLocation(m_nlocation);

		m_SliderList.SetRange(2, 5);
 		m_SliderList.SetPos(m_SliderPos);
		UpdateSliderPos();
		m_checkLocation.SetCheck(m_nlocation);

		m_ch1En.SetCheck(theApp.GetProfileIntW(strPath, KEY_1EN, TRUE));
		m_ch1De.SetCheck(theApp.GetProfileIntW(strPath, KEY_1DS, FALSE));
		m_ch1Ho.SetCheck(theApp.GetProfileIntW(strPath, KEY_1HO, TRUE));
		m_ch1Sl.SetCheck(theApp.GetProfileIntW(strPath, KEY_1SL, TRUE));
		m_ch1Cl.SetCheck(theApp.GetProfileIntW(strPath, KEY_1CL, TRUE));
		m_ch1Fl.SetCheck(theApp.GetProfileIntW(strPath, KEY_1FL, TRUE));

		m_ch2En.SetCheck(theApp.GetProfileIntW(strPath, KEY_2EN, TRUE));
		m_ch2De.SetCheck(theApp.GetProfileIntW(strPath, KEY_2DS, FALSE));
		m_ch2Ho.SetCheck(theApp.GetProfileIntW(strPath, KEY_2HO, TRUE));
		m_ch2Sl.SetCheck(theApp.GetProfileIntW(strPath, KEY_2SL, TRUE));
		m_ch2Cl.SetCheck(theApp.GetProfileIntW(strPath, KEY_2CL, TRUE));
		m_ch2Fo.SetCheck(theApp.GetProfileIntW(strPath, KEY_2FO, TRUE));

		UpdateData(TRUE);
		m_edit1Flashout = theApp.GetProfileIntW(strPath, KEY_1TMFL, 9);
		m_edit2Fladeout = theApp.GetProfileIntW(strPath, KEY_2TMFO, 2);
		UpdateData(FALSE);
 
	 

	return TRUE;
}
 
BOOL CDlgOptions::OnInitDialog()
{
	CDialogEx::OnInitDialog();
 
	// get default path file location.
	m_strImagePath = theApp.GetProgramDir() + L"\\samples\\Normal.bmp";
	m_strImagePath = theApp.GetProfileStringW(KEYMAIN, KEY_FPTHM, m_strImagePath);

	UpdatePersistence(m_strImagePath);

   // update the slider control
	m_SliderPos = theApp.GetProfileIntW(KEYMAIN, KEY_BTNCT, 5);
	
	m_nlocation = theApp.GetProfileIntW(KEYMAIN, KEY_LOCAT, 1);
	UpdateLocation(m_nlocation);


	m_SpingON.SetRange(1, 9);// flash 
	m_SpingOFF.SetRange(1, 9);// fadeout delay 

	m_SliderList.SetRange(2, 5);// from (2 - 5) status
	m_SliderList.SetPos(m_SliderPos);

	m_checkLocation.SetCheck(m_nlocation);
	UpdateSliderPos();

	m_ch1En.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_1EN, TRUE));
	m_ch1De.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_1DS, FALSE));
	m_ch1Ho.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_1HO, TRUE));
	m_ch1Sl.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_1SL, TRUE));
	m_ch1Cl.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_1CL, TRUE));
	m_ch1Fl.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_1FL, TRUE));

	m_ch2En.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_2EN, TRUE));
	m_ch2De.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_2DS, FALSE));
	m_ch2Ho.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_2HO, TRUE));
	m_ch2Sl.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_2SL, TRUE));
	m_ch2Cl.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_2CL, TRUE));
	m_ch2Fo.SetCheck(theApp.GetProfileIntW(KEYMAIN, KEY_2FO, TRUE));

 
 	m_edit1Flashout = theApp.GetProfileIntW(KEYMAIN, KEY_1TMFL, 7);
	m_edit2Fladeout = theApp.GetProfileIntW(KEYMAIN, KEY_2TMFO, 2);
	UpdateData(FALSE);


	m_btnONHover.EnableWindow(m_ch1En.GetCheck());
	m_btnOFFHover.EnableWindow(m_ch2En.GetCheck());

	m_btnONHover.SetCustomLoadBitmapMap(2, 0);
	m_btnONHover.LoadFileBitmap(m_strImagePath, m_SliderPos);
	m_btnONHover.SetCursor(IDC_HAND);

	
	m_btnOFFHover.SetCustomLoadBitmapMap(2, 1);
	m_btnOFFHover.LoadFileBitmap(m_strImagePath, m_SliderPos);
	m_btnOFFHover.SetCursor(IDC_HAND);

	// make filter of image extension(type/png,bmp,tiff) 
 	CString strExt;
	strExt.LoadStringW(IDS_STRING_IMAGEFILEEXE);
	m_editBrowserImg.EnableFileBrowseButton(strExt, strExt);
	m_editBrowserImg.SetWindowTextW(m_strImagePath);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOptions::OnDestroy()
{
	CDialogEx::OnDestroy();

 }
 
void CDlgOptions::OnBnClickedOk()
{
 	CDialogEx::OnOK();
}
 
void CDlgOptions::OnEnChangeMfceditbrowse()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	if (!IsWindowVisible())// only if showed window  
		return;

	// TODO:  Add your control notification handler code here
 	m_editBrowserImg.GetWindowTextW(m_strImagePath);

	HBITMAP hBitmap = theApp.LoadPictureFile(m_strImagePath);


	if (hBitmap==NULL)
	{
		AfxMessageBox(L"This image file cant be supported\nPlease select another");
		return;
	}
	BITMAP hBitmapDim = { 0 };
	VERIFY(GetObject(hBitmap, sizeof(hBitmapDim), &hBitmapDim) != NULL);

	if (hBitmapDim.bmWidth > 220 || hBitmapDim.bmHeight > 200)
	{
		AfxMessageBox(L"This image file size is large than what is supported\nPlease use image around 200X200 pixels or less");
		return;
	}

  // only if image name has changed 
	if(m_btnONHover.GetCurrentImagePath().Find(m_strImagePath)==-1)
	{
		 
		UpdatePersistence(GetPersSectionName(m_strImagePath));

		m_btnONHover.SetCustomLoadBitmapMap(2, 0);
		m_btnONHover.LoadFileBitmap(m_strImagePath, m_SliderPos);
		m_btnONHover.SetCursor(IDC_HAND);

		m_btnOFFHover.SetCustomLoadBitmapMap(2, 1);
		m_btnOFFHover.LoadFileBitmap(m_strImagePath, m_SliderPos);
		m_btnOFFHover.SetCursor(IDC_HAND);

		m_btnONHover.UpdateDataButton();
		m_btnOFFHover.UpdateDataButton();
		Invalidate();
	}

}

// when clicked apply button
void CDlgOptions::OnBnClickedApply()
{
	//TRACE("\nCheckEn%d\n",m_ch1En.GetCheck());
	//update as recorded required to...
	theApp.WriteProfileInt(KEYMAIN, KEY_1EN, m_ch1En.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_1DS, m_ch1De.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_1FL, m_ch1Fl.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_1SL, m_ch1Sl.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_1HO, m_ch1Ho.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_1CL, m_ch1Cl.GetCheck());

	theApp.WriteProfileInt(KEYMAIN, KEY_2EN, m_ch2En.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_2DS, m_ch2De.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_2FO, m_ch2Fo.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_2SL, m_ch2Sl.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_2HO, m_ch2Ho.GetCheck());
	theApp.WriteProfileInt(KEYMAIN, KEY_2CL, m_ch2Cl.GetCheck());
	theApp.WriteProfileStringW(KEYMAIN, KEY_FPTHM, m_strImagePath);
	theApp.WriteProfileInt(KEYMAIN, KEY_BTNCT, m_SliderPos);
	theApp.WriteProfileInt(KEYMAIN, KEY_LOCAT, m_checkLocation.GetCheck());
	
	//update as recorded required to...
	m_btnONHover.SetCustomLoadBitmapMap(2, 0);
	m_btnONHover.LoadFileBitmap(m_strImagePath, m_SliderPos);
	m_btnONHover.SetCursor(IDC_HAND);

	m_btnOFFHover.SetCustomLoadBitmapMap(2, 1);
	m_btnOFFHover.LoadFileBitmap(m_strImagePath, m_SliderPos);
	m_btnOFFHover.SetCursor(IDC_HAND);

	UpdateData(TRUE);
	theApp.WriteProfileInt(KEYMAIN, KEY_1TMFL, m_edit1Flashout);
	theApp.WriteProfileInt(KEYMAIN, KEY_2TMFO, m_edit2Fladeout);
	UpdateData(FALSE);

	m_btnONHover.UpdateDataButton();// update button as well
	m_btnOFFHover.UpdateDataButton();
	UpdateSliderPos();

	GetDlgItem(IDAPPLY)->EnableWindow(FALSE);

	// only enable Persistence button if user's file used not program sample image 
	GetDlgItem(IDC_SAVEPRES)->EnableWindow(
		theApp.GetProfileIntW(GetPersSectionName(m_strImagePath), KEY_PRTYP, -1) != 0);


}

void CDlgOptions::OnBnClickedButtonOn()
{

	m_btnOFFHover.SetButtonHighLight(FALSE);
	m_btnOFFHover.SetButtonSelected(FALSE);

	if (m_ch1Fl.GetCheck()) {
		UpdateData(TRUE);
		m_btnONHover.SetFlashButton(m_edit1Flashout);
		UpdateData(FALSE);
	}

  }


void CDlgOptions::OnBnClickedButtonOff()
{

	m_btnONHover.SetButtonHighLight(FALSE);
	m_btnONHover.SetButtonSelected(FALSE);

	m_btnOFFHover.SetButtonSelected(m_ch2Sl.GetCheck());

 	m_btnOFFHover.SetButtonHighLight(m_ch2Ho.GetCheck());

	if (m_ch2Fo.GetCheck()) {
		UpdateData();
		m_btnOFFHover.SetFadeOutButton(m_edit2Fladeout);
		UpdateData(FALSE);
	}
   

}


void CDlgOptions::OnBnClickedCheck2fl()
{
	BOOL bEnable = m_ch2Fo.GetCheck();
	GetDlgItem(IDC_SPIN_OFF)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_OFF)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_OFF)->EnableWindow(bEnable);
	GetDlgItem(IDAPPLY)->EnableWindow();

}


void CDlgOptions::OnBnClickedCheck1fl()
{
	BOOL bEnable = m_ch1Fl.GetCheck();
	GetDlgItem(IDC_SPIN_ON)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ON)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ON)->EnableWindow(bEnable);
	GetDlgItem(IDAPPLY)->EnableWindow();

}


void CDlgOptions::OnBnClickedCheck2en()
{
 	m_ch2De.SetCheck(!m_ch2En.GetCheck());
	GetDlgItem(IDAPPLY)->EnableWindow();

}


void CDlgOptions::OnBnClickedCheck1en()
{
 	m_ch1De.SetCheck(!m_ch1En.GetCheck());
	GetDlgItem(IDAPPLY)->EnableWindow();

}

void CDlgOptions::OnBnClickedCheck1de()
{
	m_ch1En.SetCheck(!m_ch1De.GetCheck());
	GetDlgItem(IDAPPLY)->EnableWindow();

}


void CDlgOptions::OnBnClickedCheck2de()
{
 	m_ch2En.SetCheck(!m_ch2De.GetCheck());
	GetDlgItem(IDAPPLY)->EnableWindow();
}


void CDlgOptions::OnBnClickedCheck1cl()
{
	GetDlgItem(IDAPPLY)->EnableWindow();
}


void CDlgOptions::OnBnClickedCheck1ho()
{
	GetDlgItem(IDAPPLY)->EnableWindow();
}


void CDlgOptions::OnBnClickedCheck1sl()
{
	GetDlgItem(IDAPPLY)->EnableWindow();
}


void CDlgOptions::OnBnClickedCheck2cl()
{
	GetDlgItem(IDAPPLY)->EnableWindow();
}


void CDlgOptions::OnBnClickedCheck2ho()
{
	GetDlgItem(IDAPPLY)->EnableWindow();
}


void CDlgOptions::OnBnClickedCheck2sl()
{
	GetDlgItem(IDAPPLY)->EnableWindow();
}


void CDlgOptions::OnDeltaposSpinOff(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	GetDlgItem(IDAPPLY)->EnableWindow();
}

void CDlgOptions::OnDeltaposSpinOn(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	GetDlgItem(IDAPPLY)->EnableWindow();

}
void CDlgOptions::OnTRBNThumbPosChangingSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_SliderPos = pNMTPC->dwPos;
	UpdateSliderPos();
}

// update the checkBox as the slider values set.
void CDlgOptions::UpdateSliderPos()
{

	CString strFormat;
	strFormat.Format(L"[%d] Buttons", m_SliderPos);
	SetDlgItemText(IDC_STATIC_BTNCOUNT, strFormat);

	GetDlgItem(IDAPPLY)->EnableWindow(TRUE);

	switch (m_SliderPos)
	{
	case 2:
	{
		m_ch1De.EnableWindow(FALSE);
		m_ch2De.EnableWindow(FALSE);
		
		m_ch1Ho.EnableWindow(FALSE);
		m_ch2Ho.EnableWindow(FALSE);
		
		m_ch1Sl.EnableWindow(FALSE);
		m_ch2Sl.EnableWindow(FALSE);

		m_ch1Fl.EnableWindow(FALSE);
		m_ch2Fo.EnableWindow(FALSE);

		m_SpingOFF.EnableWindow(FALSE);
		m_SpingON.EnableWindow(FALSE);
		
		GetDlgItem(IDC_EDIT_ON)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OFF)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_ON)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_OFF)->EnableWindow(FALSE);
		
	 }
	break;
	case 3:
	{
		m_ch1De.EnableWindow(TRUE);
		m_ch2De.EnableWindow(TRUE);
		
		m_ch1Ho.EnableWindow(FALSE);
		m_ch2Ho.EnableWindow(FALSE);

		m_ch1Sl.EnableWindow(FALSE);
		m_ch2Sl.EnableWindow(FALSE);

		m_ch1Fl.EnableWindow(FALSE);
		m_ch2Fo.EnableWindow(FALSE);

		m_SpingOFF.EnableWindow(FALSE);
		m_SpingON.EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_ON)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OFF)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_ON)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_OFF)->EnableWindow(FALSE);

	}
	break;
	case 4:
	{
		m_ch1Ho.EnableWindow(TRUE);
		m_ch2Ho.EnableWindow(TRUE);

		m_ch1Fl.EnableWindow(TRUE);
		m_ch2Fo.EnableWindow(TRUE);
		
		m_ch1De.EnableWindow();
		m_ch2De.EnableWindow();

		m_ch1Ho.EnableWindow();
		m_ch2Ho.EnableWindow();

		m_ch1Fl.EnableWindow();
		m_ch2Fo.EnableWindow();

		m_ch1Sl.EnableWindow(FALSE);
		m_ch2Sl.EnableWindow(FALSE);

		m_SpingOFF.EnableWindow();
		m_SpingON.EnableWindow();

		GetDlgItem(IDC_EDIT_ON)->EnableWindow();
		GetDlgItem(IDC_EDIT_OFF)->EnableWindow();
		GetDlgItem(IDC_STATIC_ON)->EnableWindow();
		GetDlgItem(IDC_STATIC_OFF)->EnableWindow();

 	}
	break;
	case 5:
	{

		m_ch1Ho.EnableWindow();
		m_ch2Ho.EnableWindow();

		m_ch1Fl.EnableWindow();
		m_ch2Fo.EnableWindow();

		m_ch1De.EnableWindow();
		m_ch2De.EnableWindow();

		m_ch1Ho.EnableWindow();
		m_ch2Ho.EnableWindow();

		m_ch1Fl.EnableWindow();
		m_ch2Fo.EnableWindow();

		m_ch1Sl.EnableWindow();
		m_ch2Sl.EnableWindow();

		m_SpingOFF.EnableWindow();
		m_SpingON.EnableWindow();

		GetDlgItem(IDC_EDIT_ON)->EnableWindow();
		GetDlgItem(IDC_EDIT_OFF)->EnableWindow();
		GetDlgItem(IDC_STATIC_ON)->EnableWindow();
		GetDlgItem(IDC_STATIC_OFF)->EnableWindow();

	}
	break;
	default:
		break;

	}

}

HBRUSH CDlgOptions::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_BTNCOUNT)
	{
		pDC->SetTextColor(RGB(20, 20, 244));
	}
	
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
// MovePosCtrl: helps for move the control from location to same other control's location
void CDlgOptions::MovePosCtrl(CHoverButton* PosDlgMoveCtrl, CWnd* PosDlgToMoveCtrl)
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
void CDlgOptions::RestorePosCtrl(CHoverButton* PosDlgMoveCtrl)
{
	WINDOWPLACEMENT m_lplacemet;
	m_lplacemet = PosDlgMoveCtrl->GetWindowPlacementEx();
	PosDlgMoveCtrl->SetWindowPos(NULL, m_lplacemet.rcNormalPosition.left, m_lplacemet.rcNormalPosition.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CDlgOptions::UpdateLocation(int nLocation)
{
	m_checkLocation.SetWindowTextW(nLocation ? L"Default" : L"Center");

 
	if (nLocation == 0) {
		MovePosCtrl(&m_btnONHover, GetDlgItem(IDC_BUTTON_CTEMPON));
		MovePosCtrl(&m_btnOFFHover, GetDlgItem(IDC_BUTTON_CTEMPOFF));
	}
	else {
		RestorePosCtrl(&m_btnONHover);
		RestorePosCtrl(&m_btnOFFHover);
	}
}
void CDlgOptions::OnBnClickedCheckLocation()
{
	GetDlgItem(IDAPPLY)->EnableWindow(TRUE);
	m_nlocation = m_checkLocation.GetCheck();

	UpdateLocation(m_nlocation);
}


void CDlgOptions::OnBnClickedSavepres()
{

     CString strPath = GetPersSectionName(m_strImagePath);
   
	 // update registry values.
	theApp.WriteProfileInt(strPath, KEY_1EN, m_ch1En.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_1DS, m_ch1De.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_1FL, m_ch1Fl.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_1SL, m_ch1Sl.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_1HO, m_ch1Ho.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_1CL, m_ch1Cl.GetCheck());

	theApp.WriteProfileInt(strPath, KEY_2EN, m_ch2En.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_2DS, m_ch2De.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_2FO, m_ch2Fo.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_2SL, m_ch2Sl.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_2HO, m_ch2Ho.GetCheck());
	theApp.WriteProfileInt(strPath, KEY_2CL, m_ch2Cl.GetCheck());
 	theApp.WriteProfileInt(strPath, KEY_BTNCT, m_SliderPos);
	theApp.WriteProfileInt(strPath, KEY_LOCAT, m_checkLocation.GetCheck());
 

	UpdateData(TRUE);
	theApp.WriteProfileInt(strPath, KEY_1TMFL, m_edit1Flashout);
	theApp.WriteProfileInt(strPath, KEY_2TMFO, m_edit2Fladeout);
	UpdateData(FALSE);

	theApp.WriteProfileInt(strPath, KEY_PRTYP, 1);// User is 1 value used.

	GetDlgItem(IDC_SAVEPRES)->EnableWindow(FALSE);
}


 