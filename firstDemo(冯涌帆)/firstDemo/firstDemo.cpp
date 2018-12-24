// FirstDemo.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
	/// ����ͼ��
	GDALDataset *poSrcDs;
	// ���ͼ��
	GDALDataset *poDstDs;
	// ͼ��ĸ߶ȺͿ��
	double imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "trees.jpg";
	// ����ͼ��·��
	char* dstPath = "res.tif";
	// ͼ���ڴ�洢
	GByte* buffTmp;
	// ͼ�񲨶���
	int i, bandNum;

	//ע������
	GDALAllRegister();

	// ��ͼ��
	poSrcDs = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȡ��߶ȺͲ�������
	imgXlen = poSrcDs->GetRasterXSize();
	imgYlen = poSrcDs->GetRasterYSize();
	bandNum = poSrcDs->GetRasterCount();
	// �����ȡ�Ľ��
	cout << "Image X Length = " << imgXlen << endl;
	cout << "Image Y Length = " << imgYlen << endl;
	cout << "Band Number    = " << bandNum << endl;
	// ����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmp = (GByte*)CPLMalloc(imgXlen * imgYlen * sizeof(GByte));
	// �������ͼ��
	poDstDs = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	// һ�������ε����룬Ȼ��һ�������ε����
	for (int i = 0; i < bandNum; i++) {
		poSrcDs->GetRasterBand(i + 1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDs->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		cout << "... ... Band " << i << " Processing ... ..." << endl;
	}
	// ����ڴ�
	CPLFree(buffTmp);
	// �ر�dataset
	GDALClose(poSrcDs);
	GDALClose(poDstDs);
	
	system("pause");
    return 0;
}

