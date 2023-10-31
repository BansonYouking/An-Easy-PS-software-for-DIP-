// lx325View.cpp : implementation of the CLx325View class
//

#include "stdafx.h"
#include "lx325.h"

#include "lx325Doc.h"
#include "lx325View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLx325View

IMPLEMENT_DYNCREATE(CLx325View, CScrollView)

BEGIN_MESSAGE_MAP(CLx325View, CScrollView)
	//{{AFX_MSG_MAP(CLx325View)
	ON_COMMAND(ID_GRAY, OnGray)
	ON_UPDATE_COMMAND_UI(ID_GRAY, OnUpdateGray)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLx325View construction/destruction

CLx325View::CLx325View()
{
	// TODO: add construction code here

}

CLx325View::~CLx325View()
{
}

BOOL CLx325View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLx325View drawing
extern BITMAPINFO* lpBitsInfo;//
void CLx325View::OnDraw(CDC* pDC)
{
	CLx325Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(NULL == lpBitsInfo)
		return;

	void* lpBits = &lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	StretchDIBits(pDC ->GetSafeHdc(),
			0,0,lpBitsInfo ->bmiHeader.biWidth,lpBitsInfo ->bmiHeader.biHeight,
			0,0,lpBitsInfo ->bmiHeader.biWidth,lpBitsInfo ->bmiHeader.biHeight,
			lpBits,lpBitsInfo,
			DIB_RGB_COLORS,
			SRCCOPY);
	// TODO: add draw code for native data here
}

void CLx325View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CLx325View printing

BOOL CLx325View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLx325View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLx325View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLx325View diagnostics

#ifdef _DEBUG
void CLx325View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLx325View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CLx325Doc* CLx325View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLx325Doc)));
	return (CLx325Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLx325View message handlers
void gray();
void CLx325View::OnGray() 
{
	// TODO: Add your command handler code here
	gray();
	Invalidate();//������Ļ
}

void CLx325View::OnUpdateGray(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void pixel(int i , int j , char* str);
void CLx325View::OnMouseMove(UINT nFlags, CPoint point) //��һ���������ùܣ��ڶ���������һ���ָ࣬������������
{
	// TODO: Add your message handler code here and/or call default
	//���������
	//����pixel����
	//״̬������ʾ

	char xy[100];
	memset(xy,0,100);
	sprintf(xy,"x:%d y:%d ", point.x, point.y);

	char rgb[100];
	memset(rgb,0,100);
	pixel(point.y,point.x,rgb);

	strcat(xy,rgb);

	((CFrameWnd*)GetParent())->SetMessageText(xy);
	CScrollView::OnMouseMove(nFlags, point);
}
