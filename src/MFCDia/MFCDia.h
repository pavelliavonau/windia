
// MFCDia.h : main header file for the MFCDia application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCDiaApp:
// See MFCDia.cpp for the implementation of this class
//
class CMFCDiaDoc;

class CMFCDiaApp : public CWinApp
{
public:
	CMFCDiaApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();	
	DECLARE_MESSAGE_MAP()
};

extern CMFCDiaApp theApp;
