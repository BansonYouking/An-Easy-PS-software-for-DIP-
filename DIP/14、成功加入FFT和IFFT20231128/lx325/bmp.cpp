#include "stdafx.h"
#include<complex>

using namespace std;
#define PI 3.1415926535

BITMAPINFO* lpBitsInfo = NULL;//
BITMAPINFO* lpDIB_FT = NULL;//
BITMAPINFO* lpDIB_IFT = NULL;//

complex<double>* gFD = NULL; //ָ��Ƶ������


BOOL LoadBmpFile(char* BmpFileName) //��ȡ�ļ����ļ�ͷ����Ϣͷ
{

	FILE* fp;
	if(NULL == (fp = fopen(BmpFileName , "rb")))
		return FALSE;



	BITMAPFILEHEADER bf;//�ļ�ͷ����Ҫ��Ϣ����
	BITMAPINFOHEADER bi;//������ͼ���ȵ���Ҫ��Ϣ�ĵ�ַ
	
	fread(&bf,14,1,fp);//�ļ�ͷ
	fread(&bi,40,1,fp);//��Ϣͷ
	
	int LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;//ÿ�еı��أ�ռ�ÿռ䣩
	int ImgSize = LineBytes * bi.biHeight;//�����������õ�ͼƬ���ܱ���

//	DWOED NumColors;   // �����д��

	int NumColors;//������ɫ�������ɫ����
	if(bi.biClrUsed != 0)
		NumColors = bi.biClrUsed;
	else{
		switch(bi.biBitCount)
		{
		case 1://ʹ��һ��BIT
			NumColors = 2;//������ɫ
			break;
		case 4:
			NumColors = 16;
			break;

		case 8:
			NumColors = 256;
			break;


		case 24:
			NumColors = 0;//���ͼ��û�е�ɫ��
			break;
		}
	}
	int size = 40 + NumColors * 4 + ImgSize;

	if(NULL == (lpBitsInfo = (BITMAPINFO*)malloc(size)))
		return FALSE;

	fseek(fp,14,SEEK_SET);//���¶����ļ�ͷָ��

	fread(lpBitsInfo,size,1,fp);

	lpBitsInfo->bmiHeader.biClrUsed = NumColors;

	return TRUE;

}

void gray2()//�������ʦ�Ͽ�ʱ������д�ĻҶ�ͼ�任����
{
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE *R , *G , *B , avg; //��������ָ��ָ������ͨ��

	//Ϊ�Ҷ�ͼ������ڴ�
	int lineBytesGray = (w * 8 +31)/32 * 4;
    BITMAPINFO* lpBitsInfoGray = (BITMAPINFO* ) malloc(40 + 1024 + lineBytesGray * h);
	//��д��Ϣͷ
	memcpy(lpBitsInfoGray , lpBitsInfo , 40 );
	lpBitsInfoGray -> bmiHeader.biBitCount = 8;
	lpBitsInfoGray -> bmiHeader.biClrUsed = 256;

	//��д��ɫ��
	for (int n = 0 ;n < 256 ;n++)
	{
		lpBitsInfoGray -> bmiColors[n].rgbBlue = n;
		lpBitsInfoGray -> bmiColors[n].rgbGreen = n;
		lpBitsInfoGray -> bmiColors[n].rgbRed = n;
		lpBitsInfoGray -> bmiColors[n].rgbReserved = 0;
	}

BYTE* pixel_gray;
BYTE* lpBitsGray = (BYTE*)&lpBitsInfoGray -> bmiColors[256];

	//��дʵ��λͼ����
	for(i = 0;i < h; i ++)
	{
		for(j = 0; j < w; j ++)
		{
		
			//24bis���ͼ������
			B = lpBits + LineBytes * i+ j*3;
			//����˴���ʾ��LineBytes*(h - 1 - i)��ô��ʾ�����ľ��Ƿ�ת�ģ�
			//��Ҫ���ֲ���ת������Ҫ�����
			//pixel_gray = lpBitsGray + lineBytesGray *(h - 1 -i)+ j;
			G = B + 1;
			R = G + 1;
			avg = (*R + *G + *B)/3;
			*R = *G = *B = avg;
			//�Ҷ�ͼ������
			pixel_gray = lpBitsGray + lineBytesGray *i+ j;
			*pixel_gray = avg;

		}

	}
	//����ͼ��
	free(lpBitsInfo);
	lpBitsInfo = lpBitsInfoGray;
}

void gray()
{

	int w = lpBitsInfo->bmiHeader.biWidth;//ͼ��Ŀ��
	int h = lpBitsInfo->bmiHeader.biHeight;//ͼ��ĸ߶�
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//bmiHeader.biBitCount��ÿ�����ص��õ���λ����+31/32��Ϊ���������룬*4��Ϊ�˶���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];//ָ���ɫ���ĩβ��Ҳ����ʵ��ͼ�����ʼ�㡣

	int i,j;
	BYTE R , G , B , avg; //�����������������洢���ص��RGBֵ��

	//�Ҷ�ͼ�������
	BYTE* pixel_gray;
	BYTE* lpBitsGray;
	//�Ҷ�ͼ��ÿ���ֽ�����8ֵ����ÿ�����ص��õ���λ��
	int lineBytesGray = (w * 8 + 31 ) / 32 *4;

	//(40 + 256*4 + lineBytesGray * h) �ǿ��ٵĻҶ�ͼ���ļ����ܴ�С��40����Ϣͷ��256*4�ǵ�ɫ��Ĵ�С
	//lineBytesGray * h �ǻҶ�ͼ��ͼ�����ݵĴ�С
	BITMAPINFO* lpBitsInfoGray = (BITMAPINFO*)malloc(40 + 256*4 + lineBytesGray * h);

	//��ԭ����Ϣͷ����Ϣ��ǰ40������ֵ��lpBitsInfoGray
	memcpy(lpBitsInfoGray,lpBitsInfo,40);


	lpBitsInfoGray->bmiHeader.biBitCount = 8;
	lpBitsInfoGray->bmiHeader.biClrUsed = 256;
	lpBitsGray = (BYTE*)&lpBitsInfoGray ->bmiColors[lpBitsInfoGray ->bmiHeader.biClrUsed];


	//��д��ɫ��
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
	if(8 == lpBitsInfo -> bmiHeader.biBitCount )//ֻ���ж����һ����ɫ�ǲ��Ǻ�ɫ
	{
		r = lpBitsInfo -> bmiColors[128].rgbRed;
		g = lpBitsInfo -> bmiColors[128].rgbGreen;
		b = lpBitsInfo -> bmiColors[128].rgbBlue;

		if(r == b && r == g)
			return TRUE;


	}
	return FALSE;



}

//��ȡ���ص��ֵ
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
			strcpy(str,"������");
		else
			strcpy(str,"ǰ����");
			
		break;
	case 4 :

		bv = *(lpBits + LineBytes *( h - 1 - i) + j/2) ;
		if(j%2 == 0)
		{
		
		bv /= 16;
		//����ǳ���0����Ϊ0��˵����ż���ģ���ʱ���ص�ָ��������λ��ָ���ֽڵ�ǰ����ֽڣ�������Ҫ��ǰ����ֽڸ�ȡ����
		//���������������bv��ָ�룩����16��Ҳ�����������ֽ������ƶ�4λ��
		//bv = bv >> 4;
		
		}
		else
		{
			
		bv = bv & 15;
		//���������Ϊ0����ô˵�������������ʱ���Ҫȡ��ָ���ֽڵĺ����ֽڣ���Ҫ��ǰ����ֽ�ȫ������
		//���Ծ�����bv(ָ��)��λ����15��0000 1111��������������
		//bv %= 16��
	
		}
		r = lpBitsInfo -> bmiColors[bv].rgbRed;
		g = lpBitsInfo -> bmiColors[bv].rgbGreen;
		b = lpBitsInfo -> bmiColors[bv].rgbBlue;
		sprintf(str,"RGB(%d,%d,%d)",r,g,b);

		break;
	case 8 ://��������п�����256�Ҷ�ͼ��Ҳ�п�����256��ɫͼ��ȡ���ڵ�ɫ��Ĵ�С
		pixel = lpBits + LineBytes *( h - 1 - i) + j;
		if(IsGray())
			sprintf(str,"����ֵ��%d",*pixel);
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

//ͳ��ֱ��ͼ
//��ҵ������ɫͼ�Ķ�ͨ��ֱ��ͼ��ʾ����
DWORD H[256];//��ͨ��ʱ���Զ���Ϊ��ά����
void Histogram()
{
	//����ճ���õ�ͼ������
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//����������Զ�����ԭλͼ�Ĳ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE* pixel;

	for(i=0; i<256 ; i++)
	{
		H[i]=0;
	}
	for(i=0; i<h ; i++)//��������ͼ������ص�
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			H[*pixel]++;
		}
	}
}



void LineTrans(float a, float b )//���Ե�����
{

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//����������Զ�����ԭλͼ�Ĳ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j,k;
	BYTE* pixel;
	for(i=0; i<h ; i++)
	{
		for(j=0; j<w; j++)
		{
			pixel  = lpBits+LineBytes*(h-1-i)+j;
			//*pixel = (BYTE)((*pixel) * a + b + 0.5);//�������޷�
			k = (*pixel) * a + b + 0.5;//�����޷�
			if(k > 255)
				*pixel = 255;
			else if(k < 0 )
				*pixel = 0;
			else 
				*pixel = (BYTE)k;

		

		}
	}




}

void Equalize()//��ֵ��
{

	//����ճ�����ͼ������
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//����������Զ�����ԭλͼ�Ĳ���
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
		//���е�ʱ��ĵ㶼Ҫ����һ��Ƶ���ļ���
		for(x = 0 ; x < m ; x ++)
		{
			angle = -2 * PI * u * x /m;
			FD[u] += TD[x] * complex<double>(cos(angle),sin(angle));//����Ǹ���Ҷ���任�Ĺ�ʽ���˴���e������ŷ����ʽ�����angle
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
		//���е�Ƶ��ĵ㶼Ҫ����һ��ʱ���ļ���
		for(u = 0 ; u < m ; u ++)
		{
			angle = 2 * PI * u * x /m;
			TD[x] += FD[u] * complex<double>(cos(angle),sin(angle)); //����Ǹ���Ҷ���任�Ĺ�ʽ���˴���e������ŷ����ʽ�����angle

		}

	}
}


BOOL FD_Available()
{
	return (gFD != NULL);

}

void Fourier()
{

	//����ճ�����ͼ������
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//����������Զ�����ԭλͼ�Ĳ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];


	complex<double>* TD= new complex<double>[w * h];
	complex<double>* FD= new complex<double>[w * h];

	int i , j;
	BYTE* pixel;

	for(i=0; i<h ; i++)//��������ͼ������ص�
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			TD[w * i + j] = complex<double>(*pixel * pow(-1, i + j),0);

		}
	}

	for (i = 0 ; i < h ; i ++)
		FT(&TD[w * i],&FD[w * i],w);


	//ת��һ�£�����ȡ���е�����
	for (i = 0 ; i < h ; i ++)
		for (j = 0 ; j < w ; j ++)
			TD[h * j + i] = FD[w * i + j];//��ͬһ�����ϵĵ���ʱװ��TD


	for (i = 0 ; i < w ; i ++)
		FT(&TD[h * i],&FD[h * i],w);

	LONG size = 40 + 1024 + LineBytes * h;
	
	lpDIB_FT = (BITMAPINFO*)malloc(size);

	if(NULL == lpDIB_FT)
		return;

	memcpy(lpDIB_FT,lpBitsInfo,size);

	lpBits =(BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for(i=0; i<h ; i++)//��������ͼ������ص�
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
	//����ճ�����ͼ������
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//����������Զ�����ԭλͼ�Ĳ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];


	complex<double>* TD= new complex<double>[w * h];
	complex<double>* FD= new complex<double>[w * h];

	int i , j;
	BYTE* pixel;

	for(i=0; i<h ; i++)//��������ͼ������ص�
	{
		for(j=0; j<w; j++)
		{
			FD[w * i + j] = gFD[i + h * j];

		}
	}


	for (i = 0 ; i < h ; i ++)
		IFT(&TD[w * i],&FD[w * i],w);


	//ת��һ�£�����ȡ���е�����
	for (i = 0 ; i < h ; i ++)
		for (j = 0 ; j < w ; j ++)
			FD[h * j + i] = TD[w * i + j];//��ͬһ�����ϵĵ���ʱװ��TD


	for (i = 0 ; i < w ; i ++)
		IFT(&TD[h * i],&FD[h * i],h);




	LONG size = 40 + 1024 + LineBytes * h;
	
	lpDIB_IFT = (BITMAPINFO*)malloc(size);

	if(NULL == lpDIB_IFT)
		return;

	memcpy(lpDIB_IFT,lpBitsInfo,size);

	lpBits =(BYTE*)&lpDIB_IFT->bmiColors[lpDIB_IFT->bmiHeader.biClrUsed];

//	double temp;
	for(i=0; i<h ; i++)//��������ͼ������ص�
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


//������FFT

BOOL is_gFD_OK()
{
	return (gFD != NULL);
}

void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// ���㸶��Ҷ�任����
	LONG count = 1 << r;
	// �����Ȩϵ��
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	// ��ʱ���д��X1
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// ���õ����㷨���п��ٸ���Ҷ�任�����ΪƵ��ֵX2
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
	
	// ����������λ�������У�
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
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}

void FFourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	//ָ��ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// FFT��ȣ�����Ϊ2�������η���
	int FFT_w = 1;
	// FFT��ȵ�����������������
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT�߶ȣ�����Ϊ2�������η���
	int FFT_h = 1;
	// FFT�߶ȵ�����������������
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	
	for(i = 0; i < FFT_h; i++)  // ��
	{
		for(j = 0; j < FFT_w; j++)  // ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// ��ʱ��ֵ
			TD[j + FFT_w * i] = complex<double>(*pixel* pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// ��y������п��ٸ���Ҷ�任
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// �����м�任���
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// ��x������п��ٸ���Ҷ�任
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}

	//����Ƶ��ͼ��
	//ΪƵ��ͼ������ڴ�
	LONG size = 40 + 1024 + LineBytes * height;
	lpDIB_FT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FT)
		return;
	memcpy(lpDIB_FT, lpBitsInfo, size);

	//ָ��Ƶ��ͼ������ָ��
	lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for(i = 0; i < FFT_h; i++) // ��
	{
		for(j = 0; j < FFT_w; j++) // ��
		{
			// ����Ƶ�׷���
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) *2000;
			
			// �ж��Ƿ񳬹�255
			if (temp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// ����Դͼ��
			*pixel = (BYTE)(temp);
		}
	}

	delete TD;
	gFD = FD;
}


void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// ����Ҷ�任����
	LONG	count;
	// ���㸶��Ҷ�任����
	count = 1 << r;

	// ������������洢��
	complex<double> * X = new complex<double>[count];
	// ��Ƶ���д��X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// ����
	for(int i = 0; i < count; i++)
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X, TD, r);
	
	// ��ʱ���Ĺ���
	for(i = 0; i < count; i++)
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	
	// �ͷ��ڴ�
	delete X;
}


void IFFourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// FFT��ȣ�����Ϊ2�������η���
	int FFT_w = 1;
	// FFT��ȵ�����������������
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT�߶ȣ�����Ϊ2�������η���
	int FFT_h = 1;
	// FFT�߶ȵ�����������������
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	for(i = 0; i < FFT_h; i++)  // ��
		for(j = 0; j < FFT_w; j++)  // ��
			FD[j + FFT_w * i] = gFD[i + FFT_h*j];
	
	// ��ˮƽ������п��ٸ���Ҷ�任
	for(i = 0; i < FFT_h; i++)
		IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
	
	// �����м�任���
	for(i = 0; i < FFT_h; i++)
		for(j = 0; j < FFT_w; j++)
			FD[i + FFT_h * j] = TD[j + FFT_w * i];
	
	// �ش�ֱ������п��ٸ���Ҷ�任
	for(i = 0; i < FFT_w; i++)
		IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);

	//Ϊ���任ͼ������ڴ�
	LONG size = 40 + 1024 + LineBytes * height;

	lpDIB_IFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_IFT)
		return;
	memcpy(lpDIB_IFT, lpBitsInfo, size);

	//ָ�򷴱任ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpDIB_IFT->bmiColors[256];
	BYTE* pixel;
	double temp;
	for(i = 0; i < FFT_h; i++) // ��
	{
		for(j = 0; j < FFT_w; j++) // ��
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

	// ɾ����ʱ����
	delete FD;
	delete TD;
	delete gFD;
	gFD = NULL;
}





