// big_planDoc.h : interface of the CBig_planDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIG_PLANDOC_H__7F13B7F3_93A6_4E4F_A736_F6DB1C6A25B3__INCLUDED_)
#define AFX_BIG_PLANDOC_H__7F13B7F3_93A6_4E4F_A736_F6DB1C6A25B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBig_planDoc : public CDocument
{
protected: // create from serialization only
	CBig_planDoc();
	DECLARE_DYNCREATE(CBig_planDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBig_planDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBig_planDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBig_planDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIG_PLANDOC_H__7F13B7F3_93A6_4E4F_A736_F6DB1C6A25B3__INCLUDED_)
