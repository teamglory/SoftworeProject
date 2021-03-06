// FirstDemo.cpp: 定义控制台应用程序的入口点。
//

#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")




int main()
{
	//输入图像
	GDALDataset* poSrcDS;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输入图像路径
	char* srcPath = "qingdao.jpg";
	//输出图像路径
	char* dstPath = "qing.tif";
	//图像内存存储
	GByte* buffTmp;
	//图像波段数
	int i,j, bandNum;
	//起始位置坐标
	int StartX,StartY;
	//区域宽度和高度
	int tmpXlen,tmpYlen;

	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//获取图像高度，宽度和波段数量
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	
	//根据图像的宽度和高度分配内存
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));

	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	
	//一个个波段的输入，然后一个个波段的输出
	for(i=0; i<bandNum; i++)
	{
		poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i+1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		printf("... ... band %d processing ... ...\n",i);
	}

	//起始位置坐标1
	StartX = 100;
	StartY = 100;

	//区域宽度和高度
	tmpXlen = 200;
	tmpYlen = 150;

	//分配内存
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
	
	//读取红色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	
	//遍历区域，逐像素置为255
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i] = (GByte)255;
		}
	}

	//数据写入poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);

	//起始位置坐标2
	StartX = 300;
	StartY = 300;

	//区域宽度和高度
	tmpXlen = 100;
	tmpYlen = 50;

	//分配内存
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
	
	//读取红色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	
	//遍历区域，逐像素置为255
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i] = (GByte)255;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//读取绿色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	
	//遍历区域，逐像素置为255
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i] = (GByte)255;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	
	//读取蓝色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	
	//遍历区域，逐像素置为255
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i] = (GByte)255;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);


	//起始位置坐标3
	StartX = 500;
	StartY = 500;

	//区域宽度和高度
	tmpXlen = 50;
	tmpYlen = 100;

	//分配内存
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
	
	//读取红色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//遍历区域，逐像素置为0
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i] = (GByte)0;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//读取绿色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//遍历区域，逐像素置为0
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i] = (GByte)0;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//读取蓝色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//遍历区域，逐像素置为0
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i] = (GByte)0;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);


	
	//清除内存
	CPLFree(buffTmp);
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}
