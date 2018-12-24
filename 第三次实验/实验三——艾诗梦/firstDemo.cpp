// firstDemo.cpp : 定义控制台应用程序的入口点。

#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")




int main()
{
	//输入图像
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS2;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输入图像路径
	char* srcPath1 = "superman.jpg";
	char* srcPath2 = "space.jpg";
	//输出图像路径
	char* dstPath = "res.tif";
	//图像内存存储
	GByte* buffTmpR1;
	GByte* buffTmpG1;
	GByte* buffTmpB1;
	GByte* buffTmpR2;
	GByte* buffTmpG2;
	GByte* buffTmpB2;
	GByte* buffTmpR;
	GByte* buffTmpG;
	GByte* buffTmpB;
	//图像波段数
	int i,j, bandNum;
	
	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//获取图像高度，宽度和波段数量
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	bandNum = poSrcDS1->GetRasterCount();

	//创建输出图像；
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);


	//根据图像的宽度和高度分配内存
	buffTmpR1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpR2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpG1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpG2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte)); 
	buffTmpB1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpB2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpR  = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpG  = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));	
	buffTmpB  = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	//读取surperman通道缓存在buffTmp中
	 poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
	 poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
	 poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

	 //读取space通道缓存在buffTmp中
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
	
	//写入图像
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpR, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpG, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpB, imgXlen, imgYlen, GDT_Byte, 0, 0);



	
	//清除内存
	CPLFree(buffTmpR1);
	CPLFree(buffTmpR2);
	CPLFree(buffTmpG1);
	CPLFree(buffTmpG2);
	CPLFree(buffTmpB1);
	CPLFree(buffTmpB2);
	CPLFree(buffTmpR);
	CPLFree(buffTmpG);
	CPLFree(buffTmpB);

	//关闭dataset
	GDALClose(poSrcDS1);
	GDALClose(poSrcDS2);
	GDALClose(poDstDS);
	
	
	
	
	system("PAUSE");
	return 0;
}


