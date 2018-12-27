// SixDemo2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	
	//输入图像
	GDALDataset *poSrcDS1,*poSrcDS2;
	//输出图像
    GDALDataset* poDstDS;
	//输入图像路径
	char* srcPath1 = "Mul_large.tif";
	char* srcPath2 = "Pan_large.tif";
	//输出图像路径
	char* dstPath = "2.tif";
	
	//图像的宽度和高度
    int imgXlen, imgYlen;
    int i;
	//图像内存
	float *bandR, *bandG, *bandB;
    float *bandI, *bandH, *bandS;
    float *bandP;
	
	//注册驱动
	GDALAllRegister();
	//打开图像
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);
	//获取图像的宽度和高度
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	//内存分配
	bandR = (float*)CPLMalloc(imgXlen*256*sizeof(float));
    bandG = (float*)CPLMalloc(imgXlen*256*sizeof(float));
    bandB = (float*)CPLMalloc(imgXlen*256*sizeof(float));
    bandP = (float*)CPLMalloc(imgXlen*256*sizeof(float));
    bandI = (float*)CPLMalloc(imgXlen*256*sizeof(float));
    bandH = (float*)CPLMalloc(imgXlen*256*sizeof(float));
    bandS = (float*)CPLMalloc(imgXlen*256*sizeof(float));
	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,imgXlen,imgYlen,3,GDT_Byte,NULL);

	int m=imgYlen/256+1;
	int n=1;
	while(n<m)
	{
			//读取图像缓存
			poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,   0, 256*(n-1), imgXlen, 256,
				bandR,  imgXlen, 256, GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,   0, 256*(n-1), imgXlen, 256,
				bandG,  imgXlen, 256, GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,  0, 256*(n-1), imgXlen, 256,
				bandB,  imgXlen, 256, GDT_Float32, 0, 0);
			poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,   0, 256*(n-1), imgXlen, 256, 
				bandP,  imgXlen, 256, GDT_Float32, 0, 0);
			//RGB与IHS间的变换
			for (i = 0; i < imgXlen * 256; i++)
			{
				bandH[i] = -sqrt(2.0f)/6.0f*bandR[i]-sqrt(2.0f)/6.0f*bandG[i]+sqrt(2.0f)/3.0f*bandB[i];
				bandS[i] = 1.0f/sqrt(2.0f)*bandR[i]-1/sqrt(2.0f)*bandG[i];

				bandR[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]+1.0f/sqrt(2.0f)*bandS[i];
				bandG[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]-1.0f/sqrt(2.0f)*bandS[i];
				bandB[i] = bandP[i]+sqrt(2.0f)*bandH[i];
			}

			poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 256*(n-1), imgXlen, 256,
				bandR, imgXlen, 256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 256*(n-1), imgXlen, 256, 
				bandG, imgXlen, 256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 256*(n-1), imgXlen, 256,
				bandB, imgXlen, 256, GDT_Float32, 0, 0);
			n++;
	}
	//读取图像缓存
			poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,   0, 256*(m-1), imgXlen, imgYlen-(m-1)*256,
				bandR,  imgXlen, imgYlen-(m-1)*256,GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,   0, 256*(m-1), imgXlen, imgYlen-(m-1)*256,
				bandG,  imgXlen, 256, GDT_Float32, 0, 0);
			poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,   0, 256*(m-1), imgXlen, imgYlen-(m-1)*256,
				bandB,  imgXlen, imgYlen-(m-1)*256, GDT_Float32, 0, 0);
			poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,   0, 256*(m-1), imgXlen, imgYlen-(m-1)*256,
				bandP,  imgXlen, imgYlen-(m-1)*256, GDT_Float32, 0, 0);
			//RGB与IHS间的变换
			for (i = 0; i < imgXlen * (imgYlen-(m-1)*256); i++)
			{
				bandH[i] = -sqrt(2.0f)/6.0f*bandR[i]-sqrt(2.0f)/6.0f*bandG[i]+sqrt(2.0f)/3.0f*bandB[i];
				bandS[i] = 1.0f/sqrt(2.0f)*bandR[i]-1/sqrt(2.0f)*bandG[i];

				bandR[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]+1.0f/sqrt(2.0f)*bandS[i];
				bandG[i] = bandP[i]-1.0f/sqrt(2.0f)*bandH[i]-1.0f/sqrt(2.0f)*bandS[i];
				bandB[i] = bandP[i]+sqrt(2.0f)*bandH[i];
			}

			poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 256*(m-1), imgXlen, imgYlen-(m-1)*256,
				bandR, imgXlen, imgYlen-(m-1)*256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 256*(m-1), imgXlen, imgYlen-(m-1)*256,
				bandG, imgXlen, imgYlen-(m-1)*256, GDT_Float32, 0, 0);
			poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 256*(m-1), imgXlen, imgYlen-(m-1)*256,
				bandB, imgXlen, imgYlen-(m-1)*256, GDT_Float32, 0, 0);
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


