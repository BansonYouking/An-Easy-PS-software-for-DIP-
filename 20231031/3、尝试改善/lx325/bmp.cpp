#include "stdafx.h"

BITMAPINFO* lpBitsInfo = NULL;//

BOOL LoadBmpFile(char* BmpFileName) //读取文件的文件头和信息头
{

	FILE* fp;
	if(NULL == (fp = fopen(BmpFileName , "rb")))
		return FALSE;



	BITMAPFILEHEADER bf;//文件头，重要信息不多
	BITMAPINFOHEADER bi;//包含了图像宽度等重要信息的地址
	
	fread(&bf,14,1,fp);//文件头
	fread(&bi,40,1,fp);//信息头
	
	int LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;//每行的比特（占用空间）
	int ImgSize = LineBytes * bi.biHeight;//乘于行数，得到图片的总比特

//	DWOED NumColors;   // 奇瑞的写法

	int NumColors;//表明调色板的总颜色数量
	if(bi.biClrUsed != 0)
		NumColors = bi.biClrUsed;
	else{
		switch(bi.biBitCount)
		{
		case 1://使用一个BIT
			NumColors = 2;//两种颜色
			break;
		case 4:
			NumColors = 16;
			break;

		case 8:
			NumColors = 256;
			break;


		case 24:
			NumColors = 0;//真彩图像没有调色板
			break;
		}
	}
	int size = 40 + NumColors * 4 + ImgSize;

	if(NULL == (lpBitsInfo = (BITMAPINFO*)malloc(size)))
		return FALSE;

	fseek(fp,14,SEEK_SET);//重新定义文件头指针

	fread(lpBitsInfo,size,1,fp);

	lpBitsInfo->bmiHeader.biClrUsed = NumColors;

	return TRUE;

}

void gray()
{
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE *R , *G , *B , avg; //定义三个指针指向三个通道

	//为灰度图像分配内存
	int lineBytesGray = (w * 8 +31)/32 * 4;
    BITMAPINFO* lpBitsInfoGray = (BITMAPINFO* ) malloc(40 + 1024 + lineBytesGray * h);
	//填写信息头
	memcpy(lpBitsInfoGray , lpBitsInfo , 40 );
	lpBitsInfoGray -> bmiHeader.biBitCount = 8;
	lpBitsInfoGray -> bmiHeader.biClrUsed = 256;

	//填写调色板
	for (int n = 0 ;n < 256 ;n++)
	{
		lpBitsInfoGray -> bmiColors[n].rgbBlue = n;
		lpBitsInfoGray -> bmiColors[n].rgbGreen = n;
		lpBitsInfoGray -> bmiColors[n].rgbRed = n;
		lpBitsInfoGray -> bmiColors[n].rgbReserved = 0;


	}

BYTE* pixel_gray;
BYTE* lpBitsGray = (BYTE*)&lpBitsInfoGray -> bmiColors[256];

	//填写实际位图数据
	for(i = 0;i < h; i ++)
	{
		for(j = 0; j < w; j ++)
		{
		
			//24bis真彩图像数据
			B = lpBits + LineBytes * i+ j*3;
			//如果此处显示的LineBytes*(h - 1 - i)那么显示出来的就是翻转的，
			//想要保持不翻转，就需要下面的
			//pixel_gray = lpBitsGray + lineBytesGray *(h - 1 -i)+ j;
			G = B + 1;
			R = G + 1;
			avg = (*R + *G + *B)/3;
			*R = *G = *B = avg;
			//灰度图像数据
			pixel_gray = lpBitsGray + lineBytesGray *i+ j;
			*pixel_gray = avg;


		}

	}
	//更新图像
	free(lpBitsInfo);
	lpBitsInfo = lpBitsInfoGray;


}

BOOL IsGray()
{
	int r,g,b;
	if(8 == lpBitsInfo -> bmiHeader.biBitCount )//只是判断最后一个颜色是不是黑色
	{
		r = lpBitsInfo -> bmiColors[128].rgbRed;
		g = lpBitsInfo -> bmiColors[128].rgbGreen;
		b = lpBitsInfo -> bmiColors[128].rgbBlue;

		if(r == b && r == g)
			return TRUE;


	}
	return FALSE;



}

void pixel(int i , int j , char* str)
{
	if(NULL == lpBitsInfo)
		return;

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	if (i >= h || j >= w)
		return;

	BYTE *pixel, bv , r, g , b;

	switch (lpBitsInfo -> bmiHeader.biBitCount)
	{
	case 1 :
		bv = *(lpBits + LineBytes *( h - 1 - i) + j/8) & (1 << (7 - j % 8));
		if( 0 == bv )
			strcpy(str,"背景点");
		else
			strcpy(str,"前景点");
			
		break;
	case 4 :

		bv = *(lpBits + LineBytes *( h - 1 - i) + j/2) ;
		if(j%2 == 0)
		{
		
		bv /= 16;
		//如果是除以0余数为0，说明是偶数的，此时像素点指定的数据位于指定字节的前半个字节，所以需要把前半个字节给取出来
		//这里的做法就是让bv（指针）除以16，也就是让整个字节向右移动4位，
		//bv = bv >> 4;
		
		}
		else
		{
			
		bv = bv & 15;
		//如果余数不为0，那么说明是奇数，这个时候就要取出指定字节的后半个字节，需要把前半个字节全部归零
		//所以就是让bv(指针)按位与上15（0000 1111），这样就行了
		//bv %= 16；
	
		}
		r = lpBitsInfo -> bmiColors[bv].rgbRed;
		g = lpBitsInfo -> bmiColors[bv].rgbGreen;
		b = lpBitsInfo -> bmiColors[bv].rgbBlue;
		sprintf(str,"RGB(%d,%d,%d)",r,g,b);

		break;
	case 8 ://两种情况有可能是256灰度图像，也有可能是256彩色图，取决于调色板的大小
		pixel = lpBits + LineBytes *( h - 1 - i) + j;
		if(IsGray())
			sprintf(str,"亮度值：%d",*pixel);
		else {
		r = lpBitsInfo -> bmiColors[*pixel].rgbRed;
		g = lpBitsInfo -> bmiColors[*pixel].rgbGreen;
		b = lpBitsInfo -> bmiColors[*pixel].rgbBlue;
		sprintf(str,"RGB(%d,%d,%d)",r,g,b);
		}

		break;
	case 24 :
		pixel = lpBits + LineBytes *( h - 1 - i) + j*3;
		b = *pixel;
		g = *(pixel + 1);
		r = *(pixel + 2);
		sprintf(str,"RGB(%d,%d,%d)",r,g,b);
		break;



	}


}

//统计直方图
//作业：将彩色图的多通道直方图显示出来
DWORD H[256];//多通道时可以定义为多维数组
void Histogram()
{
	//复制粘贴得到图像数据
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//这里包含了自动对齐原位图的操作
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE* pixel;

	for(i=0; i<256 ; i++)
	{
		H[i]=0;
	}
	for(i=0; i<h ; i++)
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			H[*pixel]++;
		}
	}
}