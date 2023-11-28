#include "stdafx.h"
#include<complex>

using namespace std;
#define PI 3.1415926535

BITMAPINFO* lpBitsInfo = NULL;//
BITMAPINFO* lpDIB_FT = NULL;//
BITMAPINFO* lpDIB_IFT = NULL;//

complex<double>* gFD = NULL; //指向频域数据


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

void gray2()//这个是老师上课时候带领编写的灰度图变换函数
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

void gray()
{

	int w = lpBitsInfo->bmiHeader.biWidth;//图像的宽度
	int h = lpBitsInfo->bmiHeader.biHeight;//图像的高度
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//bmiHeader.biBitCount是每个像素点用到的位数，+31/32是为了四舍五入，*4是为了对齐
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];//指向调色板的末尾，也就是实际图像的起始点。

	int i,j;
	BYTE R , G , B , avg; //定义三个变量用来存储像素点的RGB值。

	//灰度图像的像素
	BYTE* pixel_gray;
	BYTE* lpBitsGray;
	//灰度图像每行字节数，8值得是每个像素点用到的位数
	int lineBytesGray = (w * 8 + 31 ) / 32 *4;

	//(40 + 256*4 + lineBytesGray * h) 是开辟的灰度图像文件的总大小，40是信息头，256*4是调色板的大小
	//lineBytesGray * h 是灰度图像图像数据的大小
	BITMAPINFO* lpBitsInfoGray = (BITMAPINFO*)malloc(40 + 256*4 + lineBytesGray * h);

	//将原本信息头的信息（前40）都赋值给lpBitsInfoGray
	memcpy(lpBitsInfoGray,lpBitsInfo,40);


	lpBitsInfoGray->bmiHeader.biBitCount = 8;
	lpBitsInfoGray->bmiHeader.biClrUsed = 256;
	lpBitsGray = (BYTE*)&lpBitsInfoGray ->bmiColors[lpBitsInfoGray ->bmiHeader.biClrUsed];


	//填写调色板
	for (int n = 0 ;n < 256 ;n++)
	{
		lpBitsInfoGray -> bmiColors[n].rgbBlue = n;
		lpBitsInfoGray -> bmiColors[n].rgbGreen = n;
		lpBitsInfoGray -> bmiColors[n].rgbRed = n;
		lpBitsInfoGray -> bmiColors[n].rgbReserved = 0;
	}

	for(i = 0 ; i < h ; i ++)
	{
		for(j = 0 ; j < w ; j ++)
		{
			switch(lpBitsInfo->bmiHeader.biBitCount)
			{
			case 1:
				break;
			case 4:
				pixel_gray = lpBits + LineBytes * i + j / 2;
				if((j % 2) == 0 )
				{
					B = lpBitsInfo->bmiColors[*pixel_gray / 16].rgbBlue;
					G = lpBitsInfo->bmiColors[*pixel_gray / 16].rgbGreen;
					R = lpBitsInfo->bmiColors[*pixel_gray / 16].rgbRed;

				}
				else if((j % 2) == 1 )
				{
					B = lpBitsInfo->bmiColors[*pixel_gray % 16].rgbBlue;
					G = lpBitsInfo->bmiColors[*pixel_gray % 16].rgbGreen;
					R = lpBitsInfo->bmiColors[*pixel_gray % 16].rgbRed;

				}
				avg = (R + G +B)/3;
				break;


			}



		}



	}





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

//读取像素点的值
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
	for(i=0; i<h ; i++)//遍历整个图像的像素点
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			H[*pixel]++;
		}
	}
}



void LineTrans(float a, float b )//线性点运算
{

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//这里包含了自动对齐原位图的操作
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j,k;
	BYTE* pixel;
	for(i=0; i<h ; i++)
	{
		for(j=0; j<w; j++)
		{
			pixel  = lpBits+LineBytes*(h-1-i)+j;
			//*pixel = (BYTE)((*pixel) * a + b + 0.5);//不增加限幅
			k = (*pixel) * a + b + 0.5;//增加限幅
			if(k > 255)
				*pixel = 255;
			else if(k < 0 )
				*pixel = 0;
			else 
				*pixel = (BYTE)k;

		

		}
	}




}

void Equalize()//均值化
{

	//复制粘贴获得图像数据
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//这里包含了自动对齐原位图的操作
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i , j;
	BYTE* pixel;
	int temp;
	BYTE Map[256];

	Histogram();

	for (i = 0 ; i < 256 ; i ++)
	{
		temp = 0 ;
		for( j = 0; j <= i ; j ++)
		{
			temp += H[j];
		}
		Map[i] = (BYTE)(temp * 255 / (w * h) + 0.5);

	}

	for(i=0; i<h ; i++)
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			*pixel = Map[*pixel];
		
		}
	}

}


void FT(complex<double>* TD,complex<double>* FD, int m)
{
	int x, u ;
	double angle;
	for( u = 0; u < m ; u++)
	{
		FD[u] = 0;
		//所有的时域的点都要参与一个频域点的计算
		for(x = 0 ; x < m ; x ++)
		{
			angle = -2 * PI * u * x /m;
			FD[u] += TD[x] * complex<double>(cos(angle),sin(angle));//这个是傅里叶正变换的公式，此处的e进行了欧拉公式变成了angle
		}
		FD[u] /= m;

	}

}

void IFT(complex<double>* TD,complex<double>* FD, int m)
{
	int x, u ;
	double angle;
	for( x = 0; x < m ; x++)
	{
		TD[x] = 0;
		//所有的频域的点都要参与一个时域点的计算
		for(u = 0 ; u < m ; u ++)
		{
			angle = 2 * PI * u * x /m;
			TD[x] += FD[u] * complex<double>(cos(angle),sin(angle)); //这个是傅里叶正变换的公式，此处的e进行了欧拉公式变成了angle

		}

	}
}


BOOL FD_Available()
{
	return (gFD != NULL);

}

void Fourier()
{

	//复制粘贴获得图像数据
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//这里包含了自动对齐原位图的操作
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];


	complex<double>* TD= new complex<double>[w * h];
	complex<double>* FD= new complex<double>[w * h];

	int i , j;
	BYTE* pixel;

	for(i=0; i<h ; i++)//遍历整个图像的像素点
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			TD[w * i + j] = complex<double>(*pixel * pow(-1, i + j),0);

		}
	}

	for (i = 0 ; i < h ; i ++)
		FT(&TD[w * i],&FD[w * i],w);


	//转置一下，方便取出列的数据
	for (i = 0 ; i < h ; i ++)
		for (j = 0 ; j < w ; j ++)
			TD[h * j + i] = FD[w * i + j];//让同一个列上的点暂时装入TD


	for (i = 0 ; i < w ; i ++)
		FT(&TD[h * i],&FD[h * i],w);

	LONG size = 40 + 1024 + LineBytes * h;
	
	lpDIB_FT = (BITMAPINFO*)malloc(size);

	if(NULL == lpDIB_FT)
		return;

	memcpy(lpDIB_FT,lpBitsInfo,size);

	lpBits =(BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for(i=0; i<h ; i++)//遍历整个图像的像素点
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			temp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() + 
				        FD[j * h + i].imag() * FD[j * h + i].imag()) * 2000;

			if( temp > 255 )
				temp = 255;
			*pixel = (BYTE)(temp);

		}
	}

	delete TD;
	gFD = FD;





}



void IFourier()
{
	//复制粘贴获得图像数据
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//这里包含了自动对齐原位图的操作
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];


	complex<double>* TD= new complex<double>[w * h];
	complex<double>* FD= new complex<double>[w * h];

	int i , j;
	BYTE* pixel;

	for(i=0; i<h ; i++)//遍历整个图像的像素点
	{
		for(j=0; j<w; j++)
		{
			FD[w * i + j] = gFD[i + h * j];

		}
	}


	for (i = 0 ; i < h ; i ++)
		IFT(&TD[w * i],&FD[w * i],w);


	//转置一下，方便取出列的数据
	for (i = 0 ; i < h ; i ++)
		for (j = 0 ; j < w ; j ++)
			FD[h * j + i] = TD[w * i + j];//让同一个列上的点暂时装入TD


	for (i = 0 ; i < w ; i ++)
		IFT(&TD[h * i],&FD[h * i],h);




	LONG size = 40 + 1024 + LineBytes * h;
	
	lpDIB_IFT = (BITMAPINFO*)malloc(size);

	if(NULL == lpDIB_IFT)
		return;

	memcpy(lpDIB_IFT,lpBitsInfo,size);

	lpBits =(BYTE*)&lpDIB_IFT->bmiColors[lpDIB_IFT->bmiHeader.biClrUsed];

//	double temp;
	for(i=0; i<h ; i++)//遍历整个图像的像素点
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			*pixel = (BYTE)(TD[j * h + i ].real() / pow(-1 , i + j));

		}
	}

	delete TD;
	delete FD;
	delete gFD;
	gFD = NULL;


}


//以下是FFT

BOOL is_gFD_OK()
{
	return (gFD != NULL);
}

void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// 计算付立叶变换点数
	LONG count = 1 << r;
	// 计算加权系数
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	// 将时域点写入X1
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// 采用蝶形算法进行快速付立叶变换，输出为频域值X2
	complex<double>* X2 = new complex<double>[count]; 

	int k,j,p,size;
	complex<double>* temp;
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1 << k; j++)
		{
			size = 1 << (r-k);
			for (i = 0; i < size/2; i++)
			{
				p = j * size;
				X2[i + p] = X1[i + p] + X1[i + p + size/2];
				X2[i + p + size/2] = (X1[i + p] - X1[i + p + size/2]) * W[i * (1<<k)];
			}
		}
		temp  = X1;
		X1 = X2;
		X2 = temp;
	}
	
	// 重新排序（码位倒序排列）
	for (j = 0; j < count; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
		FD[j] /= count;
	}
	
	// 释放内存
	delete W;
	delete X1;
	delete X2;
}

void FFourier()
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	//指向图像数据指针
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// FFT宽度（必须为2的整数次方）
	int FFT_w = 1;
	// FFT宽度的幂数，即迭代次数
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT高度（必须为2的整数次方）
	int FFT_h = 1;
	// FFT高度的幂数，即迭代次数
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	
	for(i = 0; i < FFT_h; i++)  // 行
	{
		for(j = 0; j < FFT_w; j++)  // 列
		{
			// 指向DIB第i行，第j个象素的指针
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 给时域赋值
			TD[j + FFT_w * i] = complex<double>(*pixel* pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// 对y方向进行快速付立叶变换
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// 保存中间变换结果
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// 对x方向进行快速付立叶变换
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}

	//生成频谱图像
	//为频域图像分配内存
	LONG size = 40 + 1024 + LineBytes * height;
	lpDIB_FT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FT)
		return;
	memcpy(lpDIB_FT, lpBitsInfo, size);

	//指向频域图像数据指针
	lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for(i = 0; i < FFT_h; i++) // 行
	{
		for(j = 0; j < FFT_w; j++) // 列
		{
			// 计算频谱幅度
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) *2000;
			
			// 判断是否超过255
			if (temp > 255)
			{
				// 对于超过的，直接设置为255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 更新源图像
			*pixel = (BYTE)(temp);
		}
	}

	delete TD;
	gFD = FD;
}


void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// 付立叶变换点数
	LONG	count;
	// 计算付立叶变换点数
	count = 1 << r;

	// 分配运算所需存储器
	complex<double> * X = new complex<double>[count];
	// 将频域点写入X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// 求共轭
	for(int i = 0; i < count; i++)
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	
	// 调用快速付立叶变换
	FFT(X, TD, r);
	
	// 求时域点的共轭
	for(i = 0; i < count; i++)
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	
	// 释放内存
	delete X;
}


void IFFourier()
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// FFT宽度（必须为2的整数次方）
	int FFT_w = 1;
	// FFT宽度的幂数，即迭代次数
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT高度（必须为2的整数次方）
	int FFT_h = 1;
	// FFT高度的幂数，即迭代次数
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	for(i = 0; i < FFT_h; i++)  // 行
		for(j = 0; j < FFT_w; j++)  // 列
			FD[j + FFT_w * i] = gFD[i + FFT_h*j];
	
	// 沿水平方向进行快速付立叶变换
	for(i = 0; i < FFT_h; i++)
		IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
	
	// 保存中间变换结果
	for(i = 0; i < FFT_h; i++)
		for(j = 0; j < FFT_w; j++)
			FD[i + FFT_h * j] = TD[j + FFT_w * i];
	
	// 沿垂直方向进行快速付立叶变换
	for(i = 0; i < FFT_w; i++)
		IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);

	//为反变换图像分配内存
	LONG size = 40 + 1024 + LineBytes * height;

	lpDIB_IFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_IFT)
		return;
	memcpy(lpDIB_IFT, lpBitsInfo, size);

	//指向反变换图像数据指针
	BYTE* lpBits = (BYTE*)&lpDIB_IFT->bmiColors[256];
	BYTE* pixel;
	double temp;
	for(i = 0; i < FFT_h; i++) // 行
	{
		for(j = 0; j < FFT_w; j++) // 列
		{
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			temp= (TD[j*FFT_h + i].real() / pow(-1, i+j));
			if (temp < 0)
				temp = 0;
			else if (temp >255)
				temp = 255;
			*pixel = (BYTE)temp;
		}
	}

	// 删除临时变量
	delete FD;
	delete TD;
	delete gFD;
	gFD = NULL;
}





