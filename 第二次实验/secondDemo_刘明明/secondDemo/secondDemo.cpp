// secondDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ�����ʼλ�����꣬�����Ⱥ͸߶�
	int StartX1, StartY1, tmpXlen1, tmpYlen1, StartX2, StartY2, tmpXlen2, tmpYlen2, imgXlen, imgYlen, bandNum;
	char* srcPath = "mm.jpg";
	//���ͼ��·��
	char* dstPath = "res.tif";
	//ע������
	GDALAllRegister();
	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	StartX1 = 300;
	StartY1 = 300;
	tmpXlen1 = 100;
	tmpYlen1 = 50;
	StartX2 = 500;
	StartY2 = 500;
	tmpXlen2 = 50;
	tmpYlen2 = 100;
	//�����ڴ�
	GByte* buffTmp;
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	//�����ȡ���
	cout << "Image X Length: " << imgXlen << endl;
	cout << "Image Y Length: " << imgYlen << endl;
	cout << "Band number: " << bandNum << endl;
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//��ȡ��ɫͨ�����浽buffTmp��
	for (int i = 0; i <bandNum; i++)
	{
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, 500, buffTmp, imgXlen, 500, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0, 0, imgXlen, StartY2, buffTmp, imgXlen, StartY2, GDT_Byte, 0, 0);
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 500, 500, 100, buffTmp, 500, 100, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0, 500, 500, 100, buffTmp, 500, 100, GDT_Byte, 0, 0);
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			550, 500, imgXlen - 550, 100, buffTmp, imgXlen - 550, 100, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			550, 500, imgXlen - 550, 100, buffTmp, imgXlen - 550, 100, GDT_Byte, 0, 0);
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 600, imgXlen, imgYlen - 600, buffTmp, imgXlen, imgYlen - 600, GDT_Byte, 0, 600);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0, 600, imgXlen, imgYlen - 600, buffTmp, imgXlen, imgYlen - 600, GDT_Byte, 0, 600);
		printf(" ... ... band %d processing ... ...\n", i);
	}
	/*poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,
	StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);*/
	//����������������Ϊ255
	for (int j = 0; j < tmpYlen1; j++)
	{
		for (int i = 0; i < tmpXlen1; i++)
		{
			buffTmp[j*tmpXlen1 + i] = (GByte)255;
		}
	}
	for (int j = 0; j < tmpYlen2; j++)
	{
		for (int i = 0; i < tmpXlen2; i++)
		{
			buffTmp[j*tmpXlen2 + i] = (GByte)255;
		}
	}
	//����д��poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write,
		StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write,
		StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write,
		StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
	//����ڴ�
	CPLFree(buffTmp);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}
