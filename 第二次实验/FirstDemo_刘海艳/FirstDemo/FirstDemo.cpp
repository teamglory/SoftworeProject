// FirstDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
typedef unsigned char GByte;

int main()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen,imgYlen;
	//����ͼ���·��
	char* srcPath = "shandong.jpg";
	//���ͼ��·��
	char* dstPath = "qingdao1.tif";
	//ͼ���ڴ�洢
	GByte* buffTmp;
	//ͼ�񲨶���
	int i, bandNum;

	int StartX,StartY,j,tmpXlen,tmpYlen;
	

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath,GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//�����ȡ���
	cout << "Image X Length: "<< imgXlen << endl;
	cout << "Image Y Length: "<< imgYlen << endl;
	cout << "Band number: "<< bandNum << endl;
	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
	//һ�������ε����룬Ȼ��һ�������ε����
	for (i=0; i<bandNum; i++)
	{
		poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read,0, 0, imgXlen, imgYlen,buffTmp,imgXlen, imgYlen,GDT_Byte,0,0);
		poDstDS->GetRasterBand(i+1)->RasterIO(GF_Write,0, 0, imgXlen, imgYlen,buffTmp,imgXlen, imgYlen,GDT_Byte,0,0);
		printf("... ... bnad %d processing ... ...\n", i);
	}

	//��ʼλ������
	StartX = 100;
	StartY = 100;
	//�����Ⱥ͸߶�
	tmpXlen=200;
	tmpYlen=150;
	//�����ڴ�
	buffTmp= (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
	//��ȡ��ɫͨ��������buffTmp��
	poSrcDS-> GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//����������������Ϊ255
	for(j=0;j<tmpYlen;j++)
	{
		for(i=0;i<tmpXlen;i++)
		{
			buffTmp[j*tmpXlen+i]=(GByte)255;
		}
	}
	//����д��poDstDS
	poDstDS-> GetRasterBand(1)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);




	//����ڴ�
	CPLFree(buffTmp);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}

