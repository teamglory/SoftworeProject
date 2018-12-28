// firstDemo.cpp : �������̨Ӧ�ó������ڵ㡣

#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


double Con(double a[3][3], double b[3][3])
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
double Con(double a[5][5], double b[5][5])
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
int main()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS1;
	GDALDataset* poDstDS2;
	GDALDataset* poDstDS3;
	GDALDataset* poDstDS4;
	GDALDataset* poDstDS5;
	GDALDataset* poDstDS6;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath1 = "girl.jpg";
	//���ͼ��·��
	char* dstPath1 = "res1.tif";
	char* dstPath2 = "res2.tif";
	char* dstPath3 = "res3.tif";
	char* dstPath4 = "res4.tif";
	char* dstPath5 = "res5.tif";
	char* dstPath6 = "res6.tif";
	//ͼ���ڴ�洢
	GByte* buffTmp[3];
	GByte* buffTmp1[6][3];
	
	//ͼ�񲨶���
	int i,j, bandNum, m = 0, n = 0, result[6];
	double middle1[3][3],middle2[5][5];
	//����˳�ʼ��
	double Con1[3][3]={0,1,0,1,1,1,0,1,0},Con2[5][5]={1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0 ,0,0,0,0,1};
	double Con3[3][3]={-1,-1,-1,-1,8,-1,-1,-1,-1 },Con4[3][3]={-1,-1,-1,-1,9,-1,-1,-1,-1 };
	double Con5[3][3]={-1,-1,0,-1,0,1,0,1,1};
	double Con6[5][5]={0.0120,0.1253,0.2736,0.1253,0.0120,0.1253,1.3054,2.8514,1.3054,0.1253,0.2736,2.8514,6.2279,2.8514,0.2736,0.1253,1.3054,2.8514,1.3054,0.1253,0.0120,0.1253,0.2736,0.1253,0.0120 };
	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	//��ȡͼ��߶ȣ���ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//�������ͼ��
	poDstDS1 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath1, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	poDstDS2 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath2, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	poDstDS3 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath3, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	poDstDS4 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath4, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	poDstDS5 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath5, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	poDstDS6 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath6, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	for (i = 0; i <bandNum; i++)
	{
		buffTmp[i]= (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
		for(int j=0;j<6;j++)
		buffTmp1[j][i] = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	}
	//��ȡgirlͨ��������buffTmp��
	for (i = 0; i <bandNum; i++)
	{
		poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmp[i],imgXlen,imgYlen,GDT_Byte,0,0);
		for(m=0;m<imgYlen;m++)
		{
			for(n=0;n<imgXlen;n++)
			{	
				if(m>=1 && m<=imgYlen-2 && n>=1 && n<=imgXlen-2)//3*3�Ǳ�Ե���ص�
				{
					for(int a=0; a<3 ;a++)
					{
						for(int b=0; b<3 ;b++)
							middle1[a][b]= buffTmp[i][(m+(a-1))*imgXlen + n + (b - 1)];
					}
					result[0] = (int)(0.2 * Con(middle1, Con1));
					result[2] = (int)(Con(middle1, Con3));
					result[3] = (int)(Con(middle1, Con4));
					result[4] = (int)(Con(middle1, Con5));
				}
				else//3*3��Ե���ص���0
				{
					result[0] = 0;
					result[2] = 0;
					result[3] = 0;
					result[4] = 0;
				}
				if(m>=2 && m<=imgYlen-3 && n>=2 && n<=imgXlen-3)//5*5�Ǳ�Ե���ص�
				{
					for(int a=0; a<5 ;a++)
					{
						for(int b=0; b<5 ;b++)
							middle2[a][b]= buffTmp[i][(m+(a-2))*imgXlen + n + (b - 2)];
					}
					result[1] = (int)(0.2*Con(middle2, Con2));
					result[5] = (int)(Con(middle2, Con6)/25);
				}
				else//5*5��Ե���ص���0
				{
					result[1] = 0;
					result[5] = 0;
				}
				for (int c = 0; c < 6; c++)
				{
					if (result[c] < 0)    
						result[c] = 0;
					else if (result[c] > 255) 
						result[c] = 255;
					buffTmp1[c][i][m*imgXlen + n] = (GByte)result[c];
				}
			}
		}
	
	//д��ͼ��
	poDstDS1->GetRasterBand(i+1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1[0][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS2->GetRasterBand(i+1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1[1][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS3->GetRasterBand(i+1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1[2][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS4->GetRasterBand(i+1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1[3][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS5->GetRasterBand(i+1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1[4][i], imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS6->GetRasterBand(i+1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1[5][i], imgXlen, imgYlen, GDT_Byte, 0, 0);

	}

	//����ڴ�
	for ( i = 0; i < 3; i++)
		CPLFree(buffTmp[i]);
	for ( i = 0; i < 6; i++)
	{
			CPLFree(buffTmp1[i][0]);
			CPLFree(buffTmp1[i][1]);
			CPLFree(buffTmp1[i][2]);
	}
	//�ر�dataset
	GDALClose(poSrcDS);

	GDALClose(poDstDS1);
	GDALClose(poDstDS2);
	GDALClose(poDstDS3);
	GDALClose(poDstDS4);
	GDALClose(poDstDS5);
	GDALClose(poDstDS6);
	system("PAUSE");
	return 0;
}





