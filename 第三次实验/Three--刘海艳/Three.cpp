// Three.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include "./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")
using namespace std;



int main()
{
	//����spaceͼ��
	GDALDataset* poSrcDS1;
	//����superͼ��
	GDALDataset* poSrcDS2;
	//���ͼ��
	GDALDataset* poDstDS;
	//spaceͼ��Ŀ�Ⱥ͸߶�
	int imgXlen,imgYlen;
	//supermanͼ��Ŀ�Ⱥ͸߶�
	int supXlen,supYlen;
	//����ͼ���·��
	char* srcPath1 = "space.jpg";
	char* srcPath2 = "superman.jpg";
	//���ͼ��·��
	char* dstPath = "super.tif";
	//ͼ���ڴ�洢
	GByte* buffTmp;
	//space�ڴ�
	GByte* buffTmpSpaceR;
	GByte* buffTmpSpaceG;
	GByte* buffTmpSpaceB;
	//superman�ڴ�
	GByte* buffTmpSuperR;
	GByte* buffTmpSuperG;
	GByte* buffTmpSuperB;

	int i,j,bandNum,superbandNum;
	int StartX,StartY;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);

	//��ȡspaceͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	bandNum = poSrcDS1->GetRasterCount();

	//���Supermanͼ��Ŀ�ȸ߶ȺͲ�������
	supXlen = poSrcDS2->GetRasterXSize();
	supYlen = poSrcDS2->GetRasterYSize();
	superbandNum = poSrcDS2->GetRasterCount();

	//spaceͼ������ڴ�
	buffTmpSpaceR = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpSpaceG = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	buffTmpSpaceB = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	//supermanͼ������ڴ�
	buffTmpSuperR = (GByte*)CPLMalloc(supXlen*supYlen*sizeof(GByte));
	buffTmpSuperG = (GByte*)CPLMalloc(supXlen*supYlen*sizeof(GByte));
	buffTmpSuperB = (GByte*)CPLMalloc(supXlen*supYlen*sizeof(GByte));

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,supXlen,supYlen,superbandNum,GDT_Byte,NULL);

	//��ʼλ������
	StartX = 0;
	StartY = 0;

	//��ȡ����������buffTmpSpace��
	poSrcDS1-> GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,imgXlen,imgYlen,buffTmpSpaceR,imgXlen,imgYlen,GDT_Byte,0,0);
	poSrcDS1-> GetRasterBand(2)->RasterIO(GF_Read,StartX,StartY,imgXlen,imgYlen,buffTmpSpaceG,imgXlen,imgYlen,GDT_Byte,0,0);
	poSrcDS1-> GetRasterBand(3)->RasterIO(GF_Read,StartX,StartY,imgXlen,imgYlen,buffTmpSpaceB,imgXlen,imgYlen,GDT_Byte,0,0);

	//��ȡ����������buffTmpSuper��
	poSrcDS2-> GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,supXlen,supYlen,buffTmpSuperR,supXlen,supYlen,GDT_Byte,0,0);
	poSrcDS2-> GetRasterBand(2)->RasterIO(GF_Read,StartX,StartY,supXlen,supYlen,buffTmpSuperG,supXlen,supYlen,GDT_Byte,0,0);
	poSrcDS2-> GetRasterBand(3)->RasterIO(GF_Read,StartX,StartY,supXlen,supYlen,buffTmpSuperB,supXlen,supYlen,GDT_Byte,0,0);

	//��������
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

	//����д��poDstDS
	poDstDS-> GetRasterBand(1)->RasterIO(GF_Write,StartX,StartY,supXlen,supYlen,buffTmpSpaceR ,supXlen,supYlen,GDT_Byte,0,0);
	poDstDS-> GetRasterBand(2)->RasterIO(GF_Write,StartX,StartY,supXlen,supYlen,buffTmpSpaceG ,supXlen,supYlen,GDT_Byte,0,0);
	poDstDS-> GetRasterBand(3)->RasterIO(GF_Write,StartX,StartY,supXlen,supYlen,buffTmpSpaceB ,supXlen,supYlen,GDT_Byte,0,0);

	//����ڴ�
	
	CPLFree(buffTmpSpaceR);
	CPLFree(buffTmpSpaceG);
	CPLFree(buffTmpSpaceB);
	CPLFree(buffTmpSuperR);
	CPLFree(buffTmpSuperG);
	CPLFree(buffTmpSuperB);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS1);
	GDALClose(poSrcDS2);

	system("PAUSE");
	return 0;


}

