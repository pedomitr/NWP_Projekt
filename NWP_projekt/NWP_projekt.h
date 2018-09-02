
// NWP_projekt.h : main header file for the NWP_projekt application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CNWPprojektApp:
// See NWP_projekt.cpp for the implementation of this class
//

class CNWPprojektApp : public CWinApp
{
public:
	CNWPprojektApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNWPprojektApp theApp;
