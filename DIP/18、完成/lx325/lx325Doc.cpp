// lx325Doc.cpp : implementation of the CLx325Doc class
//

#include "stdafx.h"
#include "lx325.h"

#include "lx325Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLx325Doc

IMPLEMENT_DYNCREATE(CLx325Doc, CDocument)

BEGIN_MESSAGE_MAP(CLx325Doc, CDocument)
	//{{AFX_MSG_MAP(CLx325Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLx325Doc construction/destruction

CLx325Doc::CLx325Doc()
{
	// TODO: add one-time construction code here

}

CLx325Doc::~CLx325Doc()
{
}

BOOL CLx325Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLx325Doc serialization

void CLx325Doc::Serialize(CArchive& ar)
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
// CLx325Doc diagnostics

#ifdef _DEBUG
void CLx325Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLx325Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLx325Doc commands

BOOL LoadBmpFile(char* BmpFileName);

BOOL CLx325Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LoadBmpFile((char*)lpszPathName);
	return TRUE;
}
