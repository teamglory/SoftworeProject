// FourDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int imFilter(char* srcPath, char* dstPath, int flag);
int Sharpness_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
int Edge_Filter (float* imgIn, float* imgOut, int imgXlen, int imgYlen);
int Embossing_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
int Box_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
int Gaussian_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
int Motion_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);

int main()
{
	char* srcPath = "lena.jpg";

	GDALAllRegister();

	imFilter(srcPath, "01_boxfilter.tif", 1);
   
    imFilter(srcPath, "02_motionfilter.tif", 2);
   
    imFilter(srcPath, "03_edgefilter.tif", 3);
   
    imFilter(srcPath, "04_sharpenfilter.tif", 4);
 
    imFilter(srcPath, "05_embossfilter.tif", 5);
  
    imFilter(srcPath, "06_gaussfilter.tif", 6);
	return 0;
}
int imFilter(char* srcPath, char* dstPath, int flag)
{
    // the input dataset
    GDALDataset* poSrcDS;
    // the output dataset
    GDALDataset* poDstDS;
    int imgXlen, imgYlen, bandNum;
    int i;
    float* imgIn;
    float* imgOut;

    poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
    imgXlen = poSrcDS->GetRasterXSize();
    imgYlen = poSrcDS->GetRasterYSize();
    bandNum = poSrcDS->GetRasterCount();

    poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
        dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

    imgIn  = (float*)CPLMalloc(imgXlen * imgYlen * sizeof(float));
    imgOut = (float*)CPLMalloc(imgXlen * imgYlen * sizeof(float));


    for (i = 0 ; i < bandNum; i++)
    {
        poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read,
            0, 0, imgXlen, imgYlen, imgIn, imgXlen, imgYlen, GDT_Float32, 0, 0);
        if (flag == 1)
        {
            Box_Filter(imgIn, imgOut, imgXlen, imgYlen);
        }
        else if (flag == 2)
        {
            Motion_Filter(imgIn, imgOut, imgXlen, imgYlen);
        }
        else if (flag == 3)
        {
            Edge_Filter(imgIn, imgOut, imgXlen, imgYlen);
        }
        else if (flag == 4)
        {
            Sharpness_Filter(imgIn, imgOut, imgXlen, imgYlen);
        }
        else if (flag == 5)
        {
            Embossing_Filter(imgIn, imgOut, imgXlen, imgYlen);
        }
        else if (flag == 6)
        {
            Gaussian_Filter(imgIn, imgOut, imgXlen, imgYlen);
        }

        poDstDS->GetRasterBand(i+1)->RasterIO(GF_Write,
            0, 0, imgXlen, imgYlen, imgOut, imgXlen, imgYlen, GDT_Float32, 0, 0);
    }


    CPLFree(imgIn);
    CPLFree(imgOut);
    GDALClose(poDstDS);
    GDALClose(poSrcDS);

    return 0;
}
int Sharpness_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen)
{
	/*-1 -1 -1
	  -1  9 -1
	  -1 -1 -1*/
	int i,j;
	for(j=1; j<imgYlen-1; j++)
	{
		for(i=1; i<imgXlen-1; i++)
		{
			imgOut[j*imgXlen+i] =(-imgIn[(j-1)*imgXlen+i-1]
            	                  -imgIn[(j-1)*imgXlen+i]
            	                  -imgIn[(j-1)*imgXlen+i+1]
                                  -imgIn[j*imgXlen+i-1]
                                  +imgIn[j*imgXlen+i]*9
                                  -imgIn[j*imgXlen+i+1]
                                  -imgIn[(j+1)*imgXlen+i-1]
                                  -imgIn[(j+1)*imgXlen+i]
                                  -imgIn[(j+1)*imgXlen+i+1]);
		}
	}
	return 0;

}
int Edge_Filter (float* imgIn, float* imgOut, int imgXlen, int imgYlen)
{
	/*-1 -1 -1
	  -1  8 -1 
	  -1 -1 -1*/
	int i,j;
	for(j=1; j<imgYlen-1; j++)
	{
		for(i=1; i<imgXlen-1; i++)
		{
			imgOut[j*imgXlen+i] =(-imgIn[(j-1)*imgXlen+i-1]
            	                  -imgIn[(j-1)*imgXlen+i]
            	                  -imgIn[(j-1)*imgXlen+i+1]
                                  -imgIn[j*imgXlen+i-1]
                                  +imgIn[j*imgXlen+i]*8
                                  -imgIn[j*imgXlen+i+1]
                                  -imgIn[(j+1)*imgXlen+i-1]
                                  -imgIn[(j+1)*imgXlen+i]
                                  -imgIn[(j+1)*imgXlen+i+1]);
		}
	}
	return 0;

}
int Embossing_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen)
{
	/*-1 -1  0 
	  -1  0  1 
	   0  1  1*/
	int i,j;
	for(j=1; j<imgYlen-1; j++)
	{
		for(i=1; i<imgXlen-1; i++)
		{
			 imgOut[j*imgXlen+i] = (-imgIn[(j-1)*imgXlen+i-1]
            	                   -imgIn[(j-1)*imgXlen+i]
                                   -imgIn[j*imgXlen+i-1]
                                   +imgIn[j*imgXlen+i+1]
                                   +imgIn[(j+1)*imgXlen+i]
                                   +imgIn[(j+1)*imgXlen+i+1]);
		}
	}
	return 0;
}
int Box_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen)
{
	/*0   0.2   0
	  0.2 0.2 0.2
	  0   0.2   0*/
	int i,j;
	for(j=1; j<imgYlen-1; j++)
	{
		for(i=1; i<imgXlen-1; i++)
		{
			imgOut[j*imgXlen+i] =(imgIn[(j-1)*imgXlen+i]          	                 
                                  +imgIn[j*imgXlen+i-1]
                                  +imgIn[j*imgXlen+i]
                                  +imgIn[j*imgXlen+i+1]                               
                                  +imgIn[(j+1)*imgXlen+i])/5.0f;
		}
	}
	return 0;
}
int Gaussian_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen)
{
	/* 0.0120  0.1253  0.2736  0.1253  0.0120 
       0.1253  1.3054  2.8514  1.3054  0.1253 
       0.2736  2.8514  6.2279  2.8514  0.2736 
       0.1253  1.3054  2.8514  1.3054  0.1253 
       0.0120  0.1253  0.2736  0.1253  0.0120 */

	int i, j;
    for (j=2; j<imgYlen-2; j++)
    {
        for (i=2; i<imgXlen-2; i++)
        {
            imgOut[j*imgXlen+i] = (0.0120*imgIn[(j-2)*imgXlen+i-2] +
            	                   0.1253*imgIn[(j-2)*imgXlen+i-1] +
            	                   0.2736*imgIn[(j-2)*imgXlen+i] +
                                   0.1253*imgIn[(j-2)*imgXlen+i+1] +
                                   0.0120*imgIn[(j-2)*imgXlen+i+2] +
                                   0.1253*imgIn[(j-1)*imgXlen+i-2] +
                                   1.3054*imgIn[(j-1)*imgXlen+i-1] +
                                   2.8514*imgIn[(j-1)*imgXlen+i] +
                                   1.3054*imgIn[(j-1)*imgXlen+i+1] +
                                   0.1253*imgIn[(j-1)*imgXlen+i+2] +
                                   0.2763*imgIn[j*imgXlen+i-2] +
                                   2.8514*imgIn[j*imgXlen+i-1] +
                                   6.2279*imgIn[j*imgXlen+i] +
                                   2.8514*imgIn[j*imgXlen+i+1] +
                                   0.2763*imgIn[j*imgXlen+i+2] +
                                   0.1253*imgIn[(j+1)*imgXlen+i-2] +
                                   1.3054*imgIn[(j+1)*imgXlen+i-1] +
                                   2.8514*imgIn[(j+1)*imgXlen+i] +
                                   1.3054*imgIn[(j+1)*imgXlen+i+1] +
                                   0.1253*imgIn[(j+1)*imgXlen+i+2] +
                                   0.0120*imgIn[(j+2)*imgXlen+i-2] +
                                   0.1253*imgIn[(j+2)*imgXlen+i-1] +
                                   0.2736*imgIn[(j+2)*imgXlen+i] +
                                   0.1253*imgIn[(j+2)*imgXlen+i+1] +
                                   0.0120*imgIn[(j+2)*imgXlen+i+2]) / 25.0f;
        }
    }
	return 0;
}
int Motion_Filter(float* imgIn, float* imgOut, int imgXlen, int imgYlen)
{
	/*1 0 0 0 0
	  0 1 0 0 0 
	  0 0 1 0 0 
	  0 0 0 1 0
	  0 0 0 0 1*/
	int i, j;
    for (j=2; j<imgYlen-2; j++)
    {
        for (i=2; i<imgXlen-2; i++)
        {
			 imgOut[j*imgXlen+i] = (imgIn[(j-2)*imgXlen+i-2]
                                   +imgIn[(j-1)*imgXlen+i-1]
                                   +imgIn[j*imgXlen+i]                                   
                                   +imgIn[(j+1)*imgXlen+i+1]
								   +imgIn[(j+2)*imgXlen+i+2]) /5.0f;
        }
    }
	return 0;
	
}





