// third.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")



int main()
{
	//����ͼ��
	GDALDataset* poSrc1;
	GDALDataset* poSrc2;
	GDALDataset* podes;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath1 = "superman.jpg";
	char* srcPath2 = "space.jpg";
	//���ͼ��·��
	char* dstPath = "output.tif";
	//ͼ���ڴ�洢
	GByte *bufftmpR,*bufftmpG,*bufftmpB;
	GByte *bufftmpR1, *bufftmpG1, *bufftmpB1;
	GByte *bufftmpR2, *bufftmpG2, *bufftmpB2;
	//ͼ�񲨶���
	int i,j, bandNum;
	//��ʼλ������
	

	int tmpXlen,tmpYlen;
	//ע������
	GDALAllRegister();
	//��ͼ��
	poSrc1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrc2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//��ȡͼ��߶ȣ���ȺͲ�������
	imgXlen = poSrc1->GetRasterXSize();
	imgYlen = poSrc1->GetRasterYSize();
	bandNum = poSrc1->GetRasterCount();
	//�������ͼ��
	podes = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//����ͼ��Ĵ�С�����ڴ�
	bufftmpR1= (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpR2 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpG1 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpG2 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpB1 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpB2 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpR = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpG = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));	
	bufftmpB = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	//supermanͼ��RGBͨ�����ض���
	poSrc1->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpR1, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrc1->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpG1, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrc1->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpB1, imgXlen, imgYlen, GDT_Byte, 0, 0);
	//spaceͼ��RGBͨ�����ض���
	poSrc2->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpR2, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrc2->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpG2, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrc2->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpB2, imgXlen, imgYlen, GDT_Byte, 0, 0);
	


	for(i=0; i<imgYlen; i++)
		for (j = 0; j < imgXlen; j++)
		{
			if (!(bufftmpR1[i*imgXlen + j] <(GByte)160 && bufftmpR1[i*imgXlen + j] > (GByte)10 && bufftmpG1[i*imgXlen + j] < (GByte)220 && bufftmpG1[i*imgXlen + j] > (GByte)100  && bufftmpB1[i*imgXlen + j] <(GByte)110 && bufftmpB1[i*imgXlen + j] > (GByte)10))
			{
				bufftmpR[i*imgXlen + j] = bufftmpR1[i*imgXlen + j];
				bufftmpG[i*imgXlen + j] = bufftmpG1[i*imgXlen + j];
				bufftmpB[i*imgXlen + j] = bufftmpB1[i*imgXlen + j];
			}
			else
			{

				bufftmpR[i*imgXlen + j] = bufftmpR2[i*imgXlen + j];
				bufftmpG[i*imgXlen + j] = bufftmpG2[i*imgXlen + j];
				bufftmpB[i*imgXlen + j] = bufftmpB2[i*imgXlen + j];
			}
		}
	
	
	
	//����д��podes
	podes->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmpR, imgXlen, imgYlen, GDT_Byte, 0, 0);
	podes->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmpG, imgXlen, imgYlen, GDT_Byte, 0, 0);
	podes->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmpB, imgXlen, imgYlen, GDT_Byte, 0, 0);


	
	//����ڴ�
	CPLFree(bufftmpR);
	CPLFree(bufftmpG);
	CPLFree(bufftmpB);
	CPLFree(bufftmpG1);
	CPLFree(bufftmpR1);
	CPLFree(bufftmpB1);
	CPLFree(bufftmpR2);
	CPLFree(bufftmpG2);	
	CPLFree(bufftmpB2);
	//�ر�dataset
	GDALClose(podes);
	GDALClose(poSrc1);
	GDALClose(poSrc2);
	system("PAUSE");
	return 0;
}
