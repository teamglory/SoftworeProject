//fiveDemo.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	//����ͼ��
	GDALDataset* poSrc1,*poSrc2;
	//���ͼ��
	GDALDataset* poDst1,*poDst2;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//���ͼ��·��
	char* dstPath = "out.tif";
	//ͼ���ڴ�洢
	float *buffTmp[3],*buffTmp2,*buffTmpH,*buffTmpI,*buffTmpS;
	//ͼ�񲨶���
	int i,j, bandNum;
	//��ʼλ������
	//int StartX,StartY;
	//�����Ⱥ͸߶�
	//int tmpXlen,tmpYlen;

	//ע������
	GDALAllRegister();

	char *srcPath1 = "American_MUL.bmp";
	char *srcPath2 = "American_PAN.bmp";
	//��ͼ��
	poSrc1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrc2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//��ȡͼ��߶ȣ���ȺͲ�������
	imgXlen = poSrc1->GetRasterXSize();
	imgYlen = poSrc1->GetRasterYSize();
	bandNum = poSrc1->GetRasterCount();
	
	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	//buffTmp[3] = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));

	//�������ͼ��
	poDst1 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	
	//һ�������ε����룬Ȼ��һ�������ε����
	for(i=0; i<bandNum; i++)
	{
		buffTmp[i] = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	}


	//�����ڴ�
	buffTmpH = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	buffTmpI = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	buffTmpS = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	buffTmp2 = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));

	for(i=0;i<bandNum;i++)
	{
		poDst1->GetRasterBand(i+1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen, buffTmp[i],imgXlen,imgYlen,GDT_Float32,0,0);
	}

	//����д��
	poSrc2->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmp2, imgXlen, imgYlen, GDT_Float32, 0, 0);

	for (i = 0;i<imgXlen*imgYlen;i++)
	{
		buffTmpH[i] = -sqrt(2.0f) / 6.0f* buffTmp[0][i] - sqrt(2.0f) / 6.0f*buffTmp[1][i] + sqrt(2.0f) / 3.0f*buffTmp[2][i];
		buffTmpS[i] = 1.0f/sqrt(2.0f)* buffTmp[0][i] - 1/sqrt(2.0f)*buffTmp[1][i];

		buffTmp[0][i] = buffTmp2[i] - 1.0f / sqrt(2.0f)*buffTmpH[i] + 1.0f / sqrt(2.0f)*buffTmpS[i];
		buffTmp[1][i] = buffTmp2[i] - 1.0f / sqrt(2.0f)*buffTmpH[i] - 1.0f / sqrt(2.0f)*buffTmpS[i];
		buffTmp[2][i] = buffTmp2[i] + sqrt(2.0f)*buffTmpH[i];

	}

	for (i = 0; i<3;i++)
	{
		poDst1->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp[i], imgXlen, imgYlen, GDT_Float32, 0, 0);
	}


	//�����ڴ�

	for(j=0;j<3;j++)
		CPLFree(buffTmp[j]);
	CPLFree(buffTmp2);
	CPLFree(buffTmpH);
	CPLFree(buffTmpI);
	CPLFree(buffTmpS);

	//�ر�dataset
	GDALClose(poSrc1);
	GDALClose(poDst1);
	GDALClose(poSrc2);
	system("PAUSE");
	return 0;
}