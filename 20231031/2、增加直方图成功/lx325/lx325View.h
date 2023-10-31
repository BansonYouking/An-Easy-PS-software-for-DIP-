// lx325View.h : interface of the CLx325View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LX325VIEW_H__556036EA_54E4_4F1C_85D2_82A9A8E1410B__INCLUDED_)
#define AFX_LX325VIEW_H__556036EA_54E4_4F1C_85D2_82A9A8E1410B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLx325View : public CScrollView
{
protected: // create from serialization only
	CLx325View();
	DECLARE_DYNCREATE(CLx325View)

// Attributes
public:
	CLx325Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLx325View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLx325View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLx325View)
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHistogramdlg();
	afx_msg void OnUpdateHistogramdlg(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in lx325View.cpp
inline CLx325Doc* CLx325View::GetDocument()
   { return (CLx325Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LX325VIEW_H__556036EA_54E4_4F1C_85D2_82A9A8E1410B__INCLUDED_)
