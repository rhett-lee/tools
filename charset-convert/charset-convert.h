
// charset-convert.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CcharsetconvertApp:
// See charset-convert.cpp for the implementation of this class
//

class CcharsetconvertApp : public CWinApp
{
public:
	CcharsetconvertApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CcharsetconvertApp theApp;
