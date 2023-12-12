// lx325View.cpp : implementation of the CLx325View class
//

#include "stdafx.h"
#include "lx325.h"

#include "lx325Doc.h"
#include "lx325View.h"
#include "HistogramDlg.h"

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
	ON_COMMAND(ID_HISTOGRAMDLG, OnHistogramdlg)
	ON_UPDATE_COMMAND_UI(ID_HISTOGRAMDLG, OnUpdateHistogramdlg)
	ON_COMMAND(ID_LINETRANS, OnLinetrans)
	ON_UPDATE_COMMAND_UI(ID_LINETRANS, OnUpdateLinetrans)
	ON_COMMAND(ID_EQUALIZE, OnEqualize)
	ON_UPDATE_COMMAND_UI(ID_EQUALIZE, OnUpdateEqualize)
	ON_COMMAND(ID_FT, OnFt)
	ON_UPDATE_COMMAND_UI(ID_FT, OnUpdateFt)
	ON_COMMAND(ID_IFT, OnIft)
	ON_UPDATE_COMMAND_UI(ID_IFT, OnUpdateIft)
	ON_COMMAND(ID_FFT, OnFft)
	ON_UPDATE_COMMAND_UI(ID_FFT, OnUpdateFft)
	ON_COMMAND(ID_IFFT, OnIfft)
	ON_UPDATE_COMMAND_UI(ID_IFFT, OnUpdateIfft)
	ON_COMMAND(ID_MID_SMOOTH, OnMidSmooth)
	ON_UPDATE_COMMAND_UI(ID_MID_SMOOTH, OnUpdateMidSmooth)
	ON_COMMAND(ID_AVG_SMOOTH, OnAvgSmooth)
	ON_UPDATE_COMMAND_UI(ID_AVG_SMOOTH, OnUpdateAvgSmooth)
	ON_COMMAND(ID_GRAD_SHARP, OnGradSharp)
	ON_UPDATE_COMMAND_UI(ID_GRAD_SHARP, OnUpdateGradSharp)
	ON_COMMAND(ID_RAPLAS_SHARP, OnRaplasSharp)
	ON_UPDATE_COMMAND_UI(ID_RAPLAS_SHARP, OnUpdateRaplasSharp)
	ON_COMMAND(ID_ILPF, OnIlpf)
	ON_UPDATE_COMMAND_UI(ID_ILPF, OnUpdateIlpf)
	ON_COMMAND(ID_BLPF, OnBlpf)
	ON_UPDATE_COMMAND_UI(ID_BLPF, OnUpdateBlpf)
	ON_COMMAND(ID_GLPF, OnGlpf)
	ON_UPDATE_COMMAND_UI(ID_GLPF, OnUpdateGlpf)
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
extern BITMAPINFO* lpBitsInfo;//内存的首地址
extern BITMAPINFO* lpDIB_FT;//
extern BITMAPINFO* lpDIB_IFT;//
void CLx325View::OnDraw(CDC* pDC)//管绘图的函数
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
	if(lpDIB_FT)
	{
		lpBits = &lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];
		StretchDIBits(pDC ->GetSafeHdc(),
		600,0,lpDIB_FT ->bmiHeader.biWidth,lpDIB_FT ->bmiHeader.biHeight,
		0,0,lpDIB_FT ->bmiHeader.biWidth,lpDIB_FT ->bmiHeader.biHeight,
		lpBits,lpDIB_FT,
		DIB_RGB_COLORS,
		SRCCOPY);
	}

	if(lpDIB_IFT)
	{
		lpBits = &lpDIB_IFT->bmiColors[lpDIB_IFT->bmiHeader.biClrUsed];
		StretchDIBits(pDC ->GetSafeHdc(),
		0,600,lpDIB_IFT ->bmiHeader.biWidth,lpDIB_IFT ->bmiHeader.biHeight,
		0,0,lpDIB_IFT ->bmiHeader.biWidth,lpDIB_IFT ->bmiHeader.biHeight,
		lpBits,lpDIB_IFT,
		DIB_RGB_COLORS,
		SRCCOPY);
	}
	// TODO: add draw code for native data here
}

void CLx325View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 1200;//当窗口小于1200的时候出现滚动条的意思

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
	Invalidate();//更新屏幕
}

void CLx325View::OnUpdateGray(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void pixel(int i , int j , char* str);
void CLx325View::OnMouseMove(UINT nFlags, CPoint point) //第一个参数不用管，第二个参数是一个类，指的是鼠标的坐标
{
	// TODO: Add your message handler code here and/or call default
	//鼠标的坐标点
	//调用pixel函数
	//状态栏中显示

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

void CLx325View::OnHistogramdlg() 
{
	// TODO: Add your command handler code here
	CHistogramDlg dlg;
	dlg.DoModal();
}

void CLx325View::OnUpdateHistogramdlg(CCmdUI* pCmdUI) //菜单命令更新函数，实时更新菜单命令状态
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo!=NULL);
}

void LineTrans(float , float);
void CLx325View::OnLinetrans() 
{
	// TODO: Add your command handler code here
	LineTrans(1, 50 );
	Invalidate();//更新屏幕

}


BOOL IsGray();
void CLx325View::OnUpdateLinetrans(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(lpBitsInfo!=NULL && IsGray());
	
}

void Equalize();
void CLx325View::OnEqualize() 
{
	// TODO: Add your command handler code here
	Equalize();
    Invalidate();//更新屏幕
}

void CLx325View::OnUpdateEqualize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo!=NULL && IsGray());
}



//以下是标准傅里叶变换的


void Fourier();

void CLx325View::OnFt() 
{
	// TODO: Add your command handler code here
	Fourier();
	Invalidate();
}

void CLx325View::OnUpdateFt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo!=NULL && IsGray());
	
}



//以下是标准傅里叶反变换的
void IFourier();
void CLx325View::OnIft() 
{
	// TODO: Add your command handler code here
	IFourier();
	Invalidate();
}

BOOL FD_Available();

void CLx325View::OnUpdateIft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FD_Available() && NULL ==  lpDIB_IFT);
	
}



//以下是快速傅里叶变换的


void FFourier();


void CLx325View::OnFft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_FT)
	{
		free(lpDIB_FT);
		lpDIB_FT = NULL;
	}

	if (lpDIB_IFT)
	{
		free(lpDIB_IFT);
		lpDIB_IFT = NULL;
	} 

	FFourier();
	Invalidate();

	
}

void CLx325View::OnUpdateFft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && IsGray()); 
	
}



//以下是快速傅里叶反变换的



void IFFourier();
void CLx325View::OnIfft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_IFT)
	{
		free(lpDIB_IFT);
		lpDIB_IFT = NULL;
	}

	IFFourier();
	Invalidate();

}
BOOL is_gFD_OK();
void CLx325View::OnUpdateIfft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(is_gFD_OK());
}


//均值滤波
void AvgSmooth();
void CLx325View::OnAvgSmooth() 
{
	// TODO: Add your command handler code here
	AvgSmooth();
	Invalidate();
}

void CLx325View::OnUpdateAvgSmooth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && IsGray());
}


//中值滤波
void MidSmooth();
void CLx325View::OnMidSmooth() 
{
	// TODO: Add your command handler code here
	MidSmooth();
	Invalidate();
}

void CLx325View::OnUpdateMidSmooth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && IsGray());
}


//梯度锐化
void GradSharp();
void CLx325View::OnGradSharp() 
{
	// TODO: Add your command handler code here
	GradSharp();
	Invalidate();
}

void CLx325View::OnUpdateGradSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && IsGray());
}

//拉普拉斯锐化
void RaplasSharp();
void CLx325View::OnRaplasSharp() 
{
	// TODO: Add your command handler code here
	RaplasSharp();
	Invalidate();
}

void CLx325View::OnUpdateRaplasSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && IsGray());
}

void FFT_Ideal_Filter(int);
//理想低通滤波器
void CLx325View::OnIlpf() 
{
	// TODO: Add your command handler code here
	FFT_Ideal_Filter(25);
	Invalidate();
}

void CLx325View::OnUpdateIlpf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(is_gFD_OK());
}


void FFT_Butterworth_Filter(int,int);
//巴特沃斯低通滤波器
void CLx325View::OnBlpf() 
{
	// TODO: Add your command handler code here
	FFT_Butterworth_Filter(25,20);//当使用的阶数是2的时候效果最好，阶数越大，越接近于理想滤波器
	Invalidate();
}

void CLx325View::OnUpdateBlpf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(is_gFD_OK());
}
//高斯低通滤波器
void FFT_Gauss_Filter(int D);
void CLx325View::OnGlpf() 
{
	// TODO: Add your command handler code here
	FFT_Gauss_Filter(25);
	Invalidate();
}

void CLx325View::OnUpdateGlpf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(is_gFD_OK());
}
