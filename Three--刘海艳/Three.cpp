// Three.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include "./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")
using namespace std;



int main()
{
	//输入space图像
	GDALDataset* poSrcDS1;
	//输入super图像
	GDALDataset* poSrcDS2;
	//输出图像
	GDALDataset* poDstDS;
	//space图像的宽度和高度
	int imgXlen,imgYlen;
	//superman图像的宽度和高度
	int supXlen,supYlen;
	//输入图像的路径
	char* srcPath1 = "space.jpg";
	char* srcPath2 = "superman.jpg";
	//输出图像路径
	char* dstPath = "super.tif";
	//图像内存存储
	GByte* buffTmp;
	//space内存
	GByte* buffTmpSpaceR;
	GByte* buffTmpSpaceG;
	GByte* buffTmpSpaceB;
	//superman内存
	GByte* buffTmpSuperR;
	GByte* buffTmpSuperG;
	GByte* buffTmpSuperB;

	int i,j,bandNum,superbandNum;
	int StartX,StartY;

	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);

	//获取space图像宽度，高度和波段数量
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	bandNum = poSrcDS1->GetRasterCount();

	//获得Superman图像的宽度高度和波段数量
	supXlen = poSrcDS2->GetRasterXSize();
	supYlen = poSrcDS2->GetRasterYSize();
	superbandNum = poSrcDS2->GetRasterCount();

	//space图像分配内存
	buffTmpSpaceR = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpSpaceG = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpSpaceB = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	//superman图像分配内存
	buffTmpSuperR = (GByte*)CPLMalloc(supXlen*supYlen*sizeof(GByte));
	buffTmpSuperG = (GByte*)CPLMalloc(supXlen*supYlen*sizeof(GByte));
	buffTmpSuperB = (GByte*)CPLMalloc(supXlen*supYlen*sizeof(GByte));

	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,supXlen,supYlen,superbandNum,GDT_Byte,NULL);

	//起始位置坐标
	StartX = 0;
	StartY = 0;

	//读取背景缓存在buffTmpSpace中
	poSrcDS1-> GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,imgXlen,imgYlen,buffTmpSpaceR,imgXlen,imgYlen,GDT_Byte,0,0);
	poSrcDS1-> GetRasterBand(2)->RasterIO(GF_Read,StartX,StartY,imgXlen,imgYlen,buffTmpSpaceG,imgXlen,imgYlen,GDT_Byte,0,0);
	poSrcDS1-> GetRasterBand(3)->RasterIO(GF_Read,StartX,StartY,imgXlen,imgYlen,buffTmpSpaceB,imgXlen,imgYlen,GDT_Byte,0,0);

	//读取背景缓存在buffTmpSuper中
	poSrcDS2-> GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,supXlen,supYlen,buffTmpSuperR,supXlen,supYlen,GDT_Byte,0,0);
	poSrcDS2-> GetRasterBand(2)->RasterIO(GF_Read,StartX,StartY,supXlen,supYlen,buffTmpSuperG,supXlen,supYlen,GDT_Byte,0,0);
	poSrcDS2-> GetRasterBand(3)->RasterIO(GF_Read,StartX,StartY,supXlen,supYlen,buffTmpSuperB,supXlen,supYlen,GDT_Byte,0,0);

	//遍历区域
	for(j=0;j<supYlen;j++)
	{
		for(i=0;i<supXlen;i++)
		{
			if ( !(buffTmpSuperR[j*supXlen+i] > (GByte)10 && buffTmpSuperR[j*supXlen+i] < (GByte)160 && buffTmpSuperG[j*supXlen+i]>(GByte)100 && buffTmpSuperG[j*supXlen+i] < (GByte)220 && buffTmpSuperB[j*supXlen+i]>(GByte)10 && buffTmpSuperB[j*supXlen+i] < (GByte)110))
			{
				buffTmpSpaceR[j*supXlen + i] = buffTmpSuperR[j*supXlen + i];
				buffTmpSpaceG[j*supXlen + i] = buffTmpSuperG[j*supXlen + i];
				buffTmpSpaceB[j*supXlen + i] = buffTmpSuperB[j*supXlen + i];
			}

		}

	}

	//数据写入poDstDS
	poDstDS-> GetRasterBand(1)->RasterIO(GF_Write,StartX,StartY,supXlen,supYlen,buffTmpSpaceR ,supXlen,supYlen,GDT_Byte,0,0);
	poDstDS-> GetRasterBand(2)->RasterIO(GF_Write,StartX,StartY,supXlen,supYlen,buffTmpSpaceG ,supXlen,supYlen,GDT_Byte,0,0);
	poDstDS-> GetRasterBand(3)->RasterIO(GF_Write,StartX,StartY,supXlen,supYlen,buffTmpSpaceB ,supXlen,supYlen,GDT_Byte,0,0);

	//清除内存
	
	CPLFree(buffTmpSpaceR);
	CPLFree(buffTmpSpaceG);
	CPLFree(buffTmpSpaceB);
	CPLFree(buffTmpSuperR);
	CPLFree(buffTmpSuperG);
	CPLFree(buffTmpSuperB);
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS1);
	GDALClose(poSrcDS2);

	system("PAUSE");
	return 0;


}

