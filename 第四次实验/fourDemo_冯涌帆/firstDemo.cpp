// FirstDemo.cpp: 定义控制台应用程序的入口点。
//

#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")



int main()
{
	//输入图像
	GDALDataset* poSrc1;
	//GDALDataset* poSrc2;
	GDALDataset* podes1,*podes2,*podes3,*podes4,*podes5,*podes6;
	double matirx(double a[3][3], double b[3][3]);
	double matirx(double a[5][5], double b[5][5]);
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输入图像路径
	//char* srcPath1 = "superman.jpg";
	//char* srcPath2 = "space.jpg";
	//输出图像路径
	char* dstPath1 = "output1.tif";
	char* dstPath2 = "output2.tif";
	char* dstPath3 = "output3.tif";
	char* dstPath4 = "output4.tif";
	char* dstPath5 = "output5.tif";
	char* dstPath6 = "output6.tif";
	//图像内存存储
	GByte *bufftmp[3], *bufftmp1[6][3];
	//图像波段数
	int i,j, bandNum,m=0,n=0,result[6];
	//起始位置坐标
	//int tmpXlen,tmpYlen;
	//注册驱动

	GDALAllRegister();
	//打开图像
	char *srcPath1 = "lina.jpg";
	poSrc1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	//获取图像高度，宽度和波段数量
	imgXlen = poSrc1->GetRasterXSize();
	imgYlen = poSrc1->GetRasterYSize();
	bandNum = poSrc1->GetRasterCount();
	//创建输出图像
	podes1 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath1, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	podes2 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath2, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	podes3 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath3, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	podes4 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath4, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	podes5 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath5, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	podes6 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath6, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//matrix
	double  matrix1[3][3] = { { 0,1,0 },{ 1,1,1 },{ 0,1,0 } };
	double  matrix2[5][5] = { { 1,0,0,0,0 },{ 0,1,0,0,0 },{ 0,0,1,0,0 },{ 0,0,0,1,0 },{ 0,0,0,0,1 } };
	double  matrix3[3][3] = { { -1,-1,-1 },{ -1,8,-1 },{ -1,-1,-1 } };
	double  matrix4[3][3] = { { -1,-1,-1 },{ -1,9,-1 },{ -1,-1,-1 } };
	double  matrix5[3][3] = { { -1,-1,0 },{ -1,0,1 },{ 0,1,1 } };
	double  matrix6[5][5] = { { 0.0120,0.1253,0.2736,0.1253,0.0120 },{ 0.1253,1.3054,2.8514,1.3054,0.1253 },
	{ 0.2736,2.8514,6.2279,2.8514,0.2736 },{ 0.1253,1.3054,2.8514,1.3054,0.1253 },{ 0.0120,0.1253,0.2736,0.1253,0.0120 } };
	// 根据图像的宽度和高度分配内存
	for (i = 0; i <bandNum; i++)
	{
		bufftmp[i] = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
		for(int j=0;j<6;j++)
		bufftmp1[j][i] = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	}
	double example1[3][3];
	double example2[5][5];

	for (i = 0; i < bandNum; i++)
	{
		poSrc1->GetRasterBand(i + 1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmp[i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		for (m = 0; m < imgYlen; m++)
		{

			for (n = 0; n < imgXlen; n++)
			{
				if (m >= 1 && m <= imgYlen - 2 && n >= 1 && n <= imgXlen - 2)
				{
					for (int l1 = 0; l1 < 3; l1++)
					{
						for (int l2 = 0; l2<3; l2++)
							example1[l1][l2] = bufftmp[i][(m + (l1 - 1))*imgXlen + n + (l2 - 1)];
					}
					result[0] = (int)(0.2*matirx(example1, matrix1));
					result[2] = (int)(matirx(example1, matrix3));
					result[3] = (int)(matirx(example1, matrix4));
					result[4] = (int)(matirx(example1, matrix5));
				}
				else
				{
					result[0] = 0;
					result[2] = 0;
					result[3] = 0;
					result[4] = 0;
				}
				if ( m>=2 && m<=imgYlen-3 && n>=2 && n <= imgXlen - 3)
				{
					for (int l1 = 0; l1 < 5; l1++)
					{
						for(int l2=0;l2<5;l2++)
						example2[l1][l2]=bufftmp[i][(m +(l1-2))*imgXlen + n +(l2-2)];
					}
					result[1] = (int)(0.2*matirx(example2, matrix2));
					result[5] = (int)(matirx(example2, matrix6)/25);
				}
				else
				{
					result[1] = 0;
					result[5] = 0;
				}
				for (int l3 = 0; l3 < 6; l3++)
				{
					if (result[l3] < 0)    result[l3] = 0;
					else if (result[l3] > 255) result[l3] = 255;
					bufftmp1[l3][i][m*imgXlen + n] = (GByte)result[l3];
				}
			}
		}
		podes1->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmp1[0][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		podes2->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmp1[1][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		podes3->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmp1[2][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		podes4->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmp1[3][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		podes5->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmp1[4][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		podes6->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmp1[5][i], imgXlen, imgYlen, GDT_Byte, 0, 0);

	}

	//清理内存

	CPLFree(bufftmp[0]);
	CPLFree(bufftmp[1]);
	CPLFree(bufftmp[2]);
	for ( i = 0; i < 6; i++)
	{
		CPLFree(bufftmp1[i][0]);
		CPLFree(bufftmp1[i][1]);
		CPLFree(bufftmp1[i][2]);
	}

	//关闭dataset
	GDALClose(poSrc1);
	GDALClose(podes1);
	GDALClose(podes2);
	GDALClose(podes3);
	GDALClose(podes4);
	GDALClose(podes5);
	GDALClose(podes6);
	system("PAUSE");
	return 0;
}
double matirx(double a[5][5], double b[5][5])
{
	double result = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
				result += a[i][j] * b[i][j];
		}
	}
	return result;
}
double matirx(double a[3][3], double b[3][3])
{
	double result = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
				result += a[i][j] * b[i][j];
		}
	}
	return result;
}