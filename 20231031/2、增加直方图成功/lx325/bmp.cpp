#include "stdafx.h"

BITMAPINFO* lpBitsInfo = NULL;//

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

void gray()
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
	for(i=0; i<h ; i++)
	{
		for(j=0; j<w; j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			H[*pixel]++;
		}
	}
}