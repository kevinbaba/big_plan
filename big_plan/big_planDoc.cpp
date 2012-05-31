// big_planDoc.cpp : implementation of the CBig_planDoc class
//

#include "stdafx.h"
#include "big_plan.h"

#include "big_planDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBig_planDoc

IMPLEMENT_DYNCREATE(CBig_planDoc, CDocument)

BEGIN_MESSAGE_MAP(CBig_planDoc, CDocument)
	//{{AFX_MSG_MAP(CBig_planDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBig_planDoc construction/destruction

CBig_planDoc::CBig_planDoc()
{
	// TODO: add one-time construction code here

}

CBig_planDoc::~CBig_planDoc()
{
}

BOOL CBig_planDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBig_planDoc serialization

void CBig_planDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBig_planDoc diagnostics

#ifdef _DEBUG
void CBig_planDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBig_planDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBig_planDoc commands
