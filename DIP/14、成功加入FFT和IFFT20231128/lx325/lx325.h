// lx325.h : main header file for the LX325 application
//

#if !defined(AFX_LX325_H__3D320D3A_B92A_406B_86DB_47071B18B5B6__INCLUDED_)
#define AFX_LX325_H__3D320D3A_B92A_406B_86DB_47071B18B5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLx325App:
// See lx325.cpp for the implementation of this class
//

class CLx325App : public CWinApp
{
public:
	CLx325App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLx325App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLx325App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LX325_H__3D320D3A_B92A_406B_86DB_47071B18B5B6__INCLUDED_)
