// big_planView.h : interface of the CBig_planView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIG_PLANVIEW_H__07511B51_5B66_47CD_855A_BC60302FA257__INCLUDED_)
#define AFX_BIG_PLANVIEW_H__07511B51_5B66_47CD_855A_BC60302FA257__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBig_planView : public CView
{
protected: // create from serialization only
	CBig_planView();
	DECLARE_DYNCREATE(CBig_planView)

// Attributes
public:
	CBig_planDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBig_planView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBig_planView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBig_planView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in big_planView.cpp
inline CBig_planDoc* CBig_planView::GetDocument()
   { return (CBig_planDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIG_PLANVIEW_H__07511B51_5B66_47CD_855A_BC60302FA257__INCLUDED_)
