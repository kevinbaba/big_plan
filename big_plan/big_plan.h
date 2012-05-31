// big_plan.h : main header file for the BIG_PLAN application
//

#if !defined(AFX_BIG_PLAN_H__71FB5BC3_3198_4EE3_83B5_7211854C3D56__INCLUDED_)
#define AFX_BIG_PLAN_H__71FB5BC3_3198_4EE3_83B5_7211854C3D56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBig_planApp:
// See big_plan.cpp for the implementation of this class
//

class CBig_planApp : public CWinApp
{
public:
	CBig_planApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBig_planApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBig_planApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIG_PLAN_H__71FB5BC3_3198_4EE3_83B5_7211854C3D56__INCLUDED_)
