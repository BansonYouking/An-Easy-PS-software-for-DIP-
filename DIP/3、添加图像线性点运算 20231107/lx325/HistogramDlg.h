#if !defined(AFX_HISTOGRAMDLG_H__002D3D0A_EDE6_400E_BF10_DC922E836952__INCLUDED_)
#define AFX_HISTOGRAMDLG_H__002D3D0A_EDE6_400E_BF10_DC922E836952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistogramDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistogramDlg dialog

class CHistogramDlg : public CDialog
{
// Construction
public:
	CHistogramDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHistogramDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHistogramDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMDLG_H__002D3D0A_EDE6_400E_BF10_DC922E836952__INCLUDED_)
