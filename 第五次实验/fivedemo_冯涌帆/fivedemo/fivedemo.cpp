//fiveDemo.cpp: 定义控制台应用程序的入口点。
//

#include"stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	//输入图像
	GDALDataset* poSrc1,*poSrc2;
	//输出图像
	GDALDataset* poDst1,*poDst2;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输出图像路径
	char* dstPath = "out.tif";
	//图像内存存储
	float *buffTmp[3],*buffTmp2,*buffTmpH,*buffTmpI,*buffTmpS;
	//图像波段数
	int i,j, bandNum;
	//起始位置坐标
	//int StartX,StartY;
	//区域宽度和高度
	//int tmpXlen,tmpYlen;

	//注册驱动
	GDALAllRegister();

	char *srcPath1 = "American_MUL.bmp";
	char *srcPath2 = "American_PAN.bmp";
	//打开图像
	poSrc1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrc2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//获取图像高度，宽度和波段数量
	imgXlen = poSrc1->GetRasterXSize();
	imgYlen = poSrc1->GetRasterYSize();
	bandNum = poSrc1->GetRasterCount();
	
	//根据图像的宽度和高度分配内存
	//buffTmp[3] = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));

	//创建输出图像
	poDst1 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	
	//一个个波段的输入，然后一个个波段的输出
	for(i=0; i<bandNum; i++)
	{
		buffTmp[i] = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	}


	//分配内存
	buffTmpH = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	buffTmpI = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	buffTmpS = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
	buffTmp2 = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));

	for(i=0;i<bandNum;i++)
	{
		poDst1->GetRasterBand(i+1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen, buffTmp[i],imgXlen,imgYlen,GDT_Float32,0,0);
	}

	//数据写入
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


	//清理内存

	for(j=0;j<3;j++)
		CPLFree(buffTmp[j]);
	CPLFree(buffTmp2);
	CPLFree(buffTmpH);
	CPLFree(buffTmpI);
	CPLFree(buffTmpS);

	//关闭dataset
	GDALClose(poSrc1);
	GDALClose(poDst1);
	GDALClose(poSrc2);
	system("PAUSE");
	return 0;
}