// firstDemo.cpp : �������̨Ӧ�ó������ڵ㡣

#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")




int main()
{
	//����ͼ��
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS2;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath1 = "superman.jpg";
	char* srcPath2 = "space.jpg";
	//���ͼ��·��
	char* dstPath = "res.tif";
	//ͼ���ڴ�洢
	GByte* buffTmpR1;
	GByte* buffTmpG1;
	GByte* buffTmpB1;
	GByte* buffTmpR2;
	GByte* buffTmpG2;
	GByte* buffTmpB2;
	GByte* buffTmpR;
	GByte* buffTmpG;
	GByte* buffTmpB;
	//ͼ�񲨶���
	int i,j, bandNum;
	
	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//��ȡͼ��߶ȣ���ȺͲ�������
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	bandNum = poSrcDS1->GetRasterCount();

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);


	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmpR1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpR2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpG1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpG2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte)); 
	buffTmpB1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpB2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpR  = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpG  = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));	
	buffTmpB  = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	//��ȡsurpermanͨ��������buffTmp��
	 poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
	 poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
	 poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

	 //��ȡspaceͨ��������buffTmp��
	 poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR2,imgXlen,imgYlen,GDT_Byte,0,0);
	 poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG2,imgXlen,imgYlen,GDT_Byte,0,0);
	 poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB2,imgXlen,imgYlen,GDT_Byte,0,0);
	
	 for(i=0;i<imgYlen;i++)
	{
		
		for(j=0;j<imgXlen;j++)
		{	
			if(!( buffTmpR1[i*imgXlen + j]<(GByte)160&& buffTmpR1[i*imgXlen + j]>(GByte)10 && buffTmpG1[i*imgXlen + j]<(GByte)220 && buffTmpG1[i*imgXlen + j]>(GByte)100 && buffTmpB1[i*imgXlen + j]<(GByte)110 &&buffTmpB1[i*imgXlen + j]>(GByte)10 ))
			{
				buffTmpR[i*imgXlen + j] = buffTmpR1[i*imgXlen + j];
				buffTmpG[i*imgXlen + j] = buffTmpG1[i*imgXlen + j];
				buffTmpB[i*imgXlen + j] = buffTmpB1[i*imgXlen + j];
			}
			else
			{
				buffTmpR[i*imgXlen + j] = buffTmpR2[i*imgXlen + j];
				buffTmpG[i*imgXlen + j] = buffTmpG2[i*imgXlen + j];
				buffTmpB[i*imgXlen + j] = buffTmpB2[i*imgXlen + j];
			}
		}
		
	}
	
	//д��ͼ��
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpR, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpG, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpB, imgXlen, imgYlen, GDT_Byte, 0, 0);



	
	//����ڴ�
	CPLFree(buffTmpR1);
	CPLFree(buffTmpR2);
	CPLFree(buffTmpG1);
	CPLFree(buffTmpG2);
	CPLFree(buffTmpB1);
	CPLFree(buffTmpB2);
	CPLFree(buffTmpR);
	CPLFree(buffTmpG);
	CPLFree(buffTmpB);

	//�ر�dataset
	GDALClose(poSrcDS1);
	GDALClose(poSrcDS2);
	GDALClose(poDstDS);
	
	
	
	
	system("PAUSE");
	return 0;
}


