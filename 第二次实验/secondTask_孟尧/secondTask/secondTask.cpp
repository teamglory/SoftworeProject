// firstDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/*int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/


using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main(){
	//输入图像
	GDALDataset* poSrcDS;
	//输出图像
	GDALDataset* poDstDS_1, * poDstDS_2;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输入图像路径
	char* srcPath = "D:/softwareClass/second/picture/begin.jpg"; 
	//输出图像路径
	char* dstPath_1 = "D:/softwareClass/second/picture/result_1.jpg";
	char* dstPath_2 = "D:/softwareClass/second/picture/result_2.jpg";
	//图像内存存储
	GByte* imgTmp_1, * imgTmp_2, * buffTmp_1, * buffTmp_2, * buffTmp_3;
	//图像波段数
	int i, j, k, bandNum;

	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//获取图像宽度，高度和波段数量
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//输出获取的结果
	cout << " Image X Length: " << imgXlen << endl;
	cout << " Image Y Length: " << imgYlen << endl;
	cout << " Band number :   " << bandNum << endl;

	//根据宽高分配内存
	imgTmp_1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	imgTmp_2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));

	//创建输出图像
	poDstDS_1 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath_1, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	poDstDS_2 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath_2, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//一个个波段的输入，然后一个个波段的输出
	for (i = 0; i < bandNum; i++) {
		poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, imgTmp_1, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, imgTmp_2, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS_1->GetRasterBand(i+1)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, imgTmp_1, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS_2->GetRasterBand(i+1)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, imgTmp_2, imgXlen, imgYlen, GDT_Byte, 0, 0);
		printf(" ... ... band %d processing ... ... \n", i);
	}

	//任务1
	//起始位置坐标
	int StartX, StartY;
	//区域宽度和高度
	int tmpXlen, tmpYlen;
	StartX = 100;
	StartY = 100;
	tmpXlen = 200;
	tmpYlen = 150;
	//分配内存
	buffTmp_1 = (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
	//读取红色通道缓存在buffTmp_1中
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,
		StartX, StartY, tmpXlen, tmpYlen, buffTmp_1, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//遍历区域，逐像素置为255
	for (j = 0; j < tmpYlen; j++)
	{
		for (i = 0; i < tmpXlen; i++)
		{
			buffTmp_1[j*tmpXlen+i] = (GByte)255;
		}
	}
	//数据写入psDstDS
	poDstDS_1->GetRasterBand(1)->RasterIO(GF_Write,
		StartX, StartY, tmpXlen, tmpYlen, buffTmp_1, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	
	//任务2
	//起始位置坐标
	int StartX1, StartX2, StartY1, StartY2;
	//区域宽度和高度
	int tmpXlen1, tmpYlen1, tmpXlen2, tmpYlen2;
	StartX1 = StartY1 = 300;  
	StartX2 = StartY2 = 500;
	tmpXlen1 = 100; tmpYlen1 = 50;
	tmpXlen2 = 50; tmpYlen2 = 100;
	//分配内存
	buffTmp_2 = (GByte*)CPLMalloc(tmpXlen1*tmpYlen1*sizeof(GByte));
	buffTmp_3 = (GByte*)CPLMalloc(tmpXlen2*tmpYlen2*sizeof(GByte));
	//遍历区域，逐像素置为255
	for (k = 0; k < bandNum; k++)
	{
		poSrcDS->GetRasterBand(k+1)->RasterIO(GF_Read,
		StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp_2, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
		poSrcDS->GetRasterBand(k+1)->RasterIO(GF_Read,
		StartX2, StartY2, tmpXlen2, tmpYlen2, buffTmp_3, tmpXlen2, tmpYlen2, GDT_Byte, 0, 0);
		for (j = 0; j < tmpYlen1; j++)
		{
			for (i = 0; i < tmpXlen1; i++)
			{
				buffTmp_2[j*tmpXlen1+i] = (GByte)255;
			}
		}
		for (j = 0; j < tmpYlen2; j++)
		{
			for (i = 0; i < tmpXlen2; i++)
			{
				buffTmp_3[j*tmpXlen2+i] = (GByte)0;
			}
		}
		//数据写入psDstDS_2
		poDstDS_2->GetRasterBand(k+1)->RasterIO(GF_Write,
		StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp_2, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
		poDstDS_2->GetRasterBand(k+1)->RasterIO(GF_Write,
		StartX2, StartY2, tmpXlen2, tmpYlen2, buffTmp_3, tmpXlen2, tmpYlen2, GDT_Byte, 0, 0);
	}
	
	
	//清除内存
	CPLFree(buffTmp_1);
	CPLFree(buffTmp_2);
	CPLFree(imgTmp_1);
	CPLFree(imgTmp_2);
	//关闭dataset
	GDALClose(poDstDS_1);
	GDALClose(poDstDS_2);
	GDALClose(poSrcDS);
	
	system("PAUSE");
	return 0;
}