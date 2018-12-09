// third.cpp : 定义控制台应用程序的入口点。
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
	GDALDataset* poSrc2;
	GDALDataset* podes;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输入图像路径
	char* srcPath1 = "superman.jpg";
	char* srcPath2 = "space.jpg";
	//输出图像路径
	char* dstPath = "output.tif";
	//图像内存存储
	GByte *bufftmpR,*bufftmpG,*bufftmpB;
	GByte *bufftmpR1, *bufftmpG1, *bufftmpB1;
	GByte *bufftmpR2, *bufftmpG2, *bufftmpB2;
	//图像波段数
	int i,j, bandNum;
	//起始位置坐标
	

	int tmpXlen,tmpYlen;
	//注册驱动
	GDALAllRegister();
	//打开图像
	poSrc1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrc2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//获取图像高度，宽度和波段数量
	imgXlen = poSrc1->GetRasterXSize();
	imgYlen = poSrc1->GetRasterYSize();
	bandNum = poSrc1->GetRasterCount();
	//创建输出图像
	podes = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//根据图像的大小分配内存
	bufftmpR1= (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpR2 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpG1 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpG2 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpB1 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpB2 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpR = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	bufftmpG = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));	
	bufftmpB = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	//superman图像RGB通道像素读入
	poSrc1->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpR1, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrc1->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpG1, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrc1->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, bufftmpB1, imgXlen, imgYlen, GDT_Byte, 0, 0);
	//space图像RGB通道像素读入
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
	
	
	
	//数据写入podes
	podes->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmpR, imgXlen, imgYlen, GDT_Byte, 0, 0);
	podes->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmpG, imgXlen, imgYlen, GDT_Byte, 0, 0);
	podes->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, bufftmpB, imgXlen, imgYlen, GDT_Byte, 0, 0);


	
	//清除内存
	CPLFree(bufftmpR);
	CPLFree(bufftmpG);
	CPLFree(bufftmpB);
	CPLFree(bufftmpG1);
	CPLFree(bufftmpR1);
	CPLFree(bufftmpB1);
	CPLFree(bufftmpR2);
	CPLFree(bufftmpG2);	
	CPLFree(bufftmpB2);
	//关闭dataset
	GDALClose(podes);
	GDALClose(poSrc1);
	GDALClose(poSrc2);
	system("PAUSE");
	return 0;
}
