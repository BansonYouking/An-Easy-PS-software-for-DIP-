// lx325Doc.h : interface of the CLx325Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LX325DOC_H__F0A7B295_EBFF_41E2_9808_04CA929025EC__INCLUDED_)
#define AFX_LX325DOC_H__F0A7B295_EBFF_41E2_9808_04CA929025EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLx325Doc : public CDocument
{
protected: // create from serialization only
	CLx325Doc();
	DECLARE_DYNCREATE(CLx325Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLx325Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLx325Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLx325Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LX325DOC_H__F0A7B295_EBFF_41E2_9808_04CA929025EC__INCLUDED_)
