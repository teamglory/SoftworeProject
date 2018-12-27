// SixDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	
	//����ͼ��
	GDALDataset *poSrcDS1,*poSrcDS2;
	//���ͼ��
    GDALDataset* poDstDS;
	//����ͼ��·��
	char* srcPath1 = "Mul_large.tif";
	char* srcPath2 = "Pan_large.tif";
	//���ͼ��·��
	char* dstPath = "1.tif";
	
	//ͼ��Ŀ�Ⱥ͸߶�
    int imgXlen, imgYlen;
    int i;
	//ͼ���ڴ�
	float *bandR, *bandG, *bandB;
    float *bandI, *bandH, *bandS;
    float *bandP;
	
	//ע������
	GDALAllRegister();
	//��ͼ��
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);
	//��ȡͼ��Ŀ�Ⱥ͸߶�
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	//�ڴ����
	bandR = (float*)CPLMalloc(256*256*sizeof(float));
    bandG = (float*)CPLMalloc(256*256*sizeof(float));
    bandB = (float*)CPLMalloc(256*256*sizeof(float));
    bandP = (float*)CPLMalloc(256*256*sizeof(float));
    bandI = (float*)CPLMalloc(256*256*sizeof(float));
    bandH = (float*)CPLMalloc(256*256*sizeof(float));
    bandS = (float*)CPLMalloc(256*256*sizeof(float));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,imgXlen,imgYlen,3,GDT_Byte,NULL);

	int m=imgYlen/256+1;
	int n=imgXlen/256+1;
	int n1=1,m1=1;
	while(m1<m)
	{
		n1=1;
		while(n1<n)
		{
			//��ȡͼ�񻺴�
			poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read, 256*(n1-1), 256*(m1-1), 256, 256,
				bandR, 256, 256, GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read, 256*(n1-1), 256*(m1-1), 256, 256,
				bandG, 256, 256, GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read, 256*(n1-1), 256*(m1-1), 256, 256,
				bandB, 256, 256, GDT_Float32, 0, 0);
			poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read, 256*(n1-1), 256*(m1-1), 256, 256,
				bandP, 256, 256, GDT_Float32, 0, 0);
			//RGB��IHS��ı任
			for (i = 0; i < 256*256; i++)
			{
				bandH[i] = -sqrt(2.0f)/6.0f*bandR[i]-sqrt(2.0f)/6.0f*bandG[i]+sqrt(2.0f)/3.0f*bandB[i];
				bandS[i] = 1.0f/sqrt(2.0f)*bandR[i]-1/sqrt(2.0f)*bandG[i];

				bandR[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]+1.0f/sqrt(2.0f)*bandS[i];
				bandG[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]-1.0f/sqrt(2.0f)*bandS[i];
				bandB[i] = bandP[i]+sqrt(2.0f)*bandH[i];
			}

			poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 256*(n1-1), 256*(m1-1), 256, 256,
				bandR, 256, 256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 256*(n1-1), 256*(m1-1), 256, 256,
				bandG, 256, 256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 256*(n1-1), 256*(m1-1), 256, 256,
				bandB, 256, 256, GDT_Float32, 0, 0);
			n1++;
		}
		m1++;
	}
	n1=1;
	while(n1<n)
	{
	        //��ȡͼ�񻺴�
			poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,  256*(n1-1),  256*(m-1), 256, imgYlen%256,
				bandR,  256, imgYlen%256,GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,   256*(n1-1), 256*(m-1), 256, imgYlen%256,
				bandG, 256, imgYlen%256,GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,   256*(n1-1), 256*(m-1), 256, imgYlen%256,
				bandB, 256, imgYlen%256, GDT_Float32, 0, 0);
			poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,   256*(n1-1), 256*(m-1), 256, imgYlen%256,
				bandP,  256, imgYlen%256,GDT_Float32, 0, 0);
			//RGB��IHS��ı任
			for (i = 0; i < 256* (imgYlen%256); i++)
			{
				bandH[i] = -sqrt(2.0f)/6.0f*bandR[i]-sqrt(2.0f)/6.0f*bandG[i]+sqrt(2.0f)/3.0f*bandB[i];
				bandS[i] = 1.0f/sqrt(2.0f)*bandR[i]-1/sqrt(2.0f)*bandG[i];

				bandR[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]+1.0f/sqrt(2.0f)*bandS[i];
				bandG[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]-1.0f/sqrt(2.0f)*bandS[i];
				bandB[i] = bandP[i]+sqrt(2.0f)*bandH[i];
			}

			poDstDS->GetRasterBand(1)->RasterIO(GF_Write,256*(n1-1),  256*(m-1), 256, imgYlen%256,
				bandR, 256, imgYlen%256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 256*(n1-1), 256*(m-1), 256, imgYlen%256,
				bandG, 256, imgYlen%256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 256*(n1-1), 256*(m-1), 256, imgYlen%256,
				bandB, 256, imgYlen%256, GDT_Float32, 0, 0);
			n1++;
	}

	cout<<"123"<<endl;

	
	

    CPLFree(bandR);
    CPLFree(bandG);
    CPLFree(bandB);
    CPLFree(bandI);
    CPLFree(bandH);
    CPLFree(bandS);
    CPLFree(bandP);

    GDALClose(poSrcDS1);
    GDALClose(poSrcDS2);
    GDALClose(poDstDS);

	return 0;
}
