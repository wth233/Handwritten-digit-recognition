#include "stdio.h"
#include "cv.h"
#include "highgui.h"
#include <vector>
#include <cmath>
using namespace std;


#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"highgui.lib")
#pragma comment(lib,"cvaux.lib")
#pragma comment(lib,"cvcam.lib")

//ͳ����ͼ��ɫ����
int ImageBlackCount(IplImage *inputImg)
{
	int nCount=0;
	char *data=inputImg->imageData;
	int wp=inputImg->widthStep;
	for(int i=0;i<inputImg->height;i++)
		for(int j=0;j<inputImg->width;j++)
		{
			int r=data[i*wp+3*j];
			int g=data[i*wp+3*j+1];
			int b=data[i*wp+3*j+2];
			if(r==0&&g==0&&b==0)
				nCount++;
		}

	return nCount;

}

//�ָ�ͼ��
void CutImage(IplImage *inputImg, int row,int col,vector<int> &featureVector,int a,int b)
{
	int w = inputImg->width;
	int h = inputImg->height;
	int nWidth=w/col;
	int nHeight=h/row;

	char name[100];
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
		{
			cvResetImageROI(inputImg);
			cvSetImageROI(inputImg,cvRect(j*nWidth,i*nHeight,nWidth,nHeight));
			IplImage *img=cvCreateImage(cvSize(nWidth,nHeight),8,3);
			cvCopy(inputImg,img);

			int count=ImageBlackCount(img);
			featureVector.push_back(count);
			sprintf(name,"C:\\�����Ӿ�\\ʵ��\\cutImg\\%d\\train%d\\wutianhao_cut%d.jpg",a,b,i*row+j+1);
			cvSaveImage(name,img);

		}
}
//����
double CalDist(vector<int> trainingFeaVector, vector<int> featureVector)
{
	double dist=0;
	if(trainingFeaVector.size()==featureVector.size())
	{
		for(int i=0;i<trainingFeaVector.size();i++)
		{
			dist+=(trainingFeaVector[i]-featureVector[i])*(trainingFeaVector[i]-featureVector[i]);
		}
		dist=sqrt(dist);
	}
	return dist;
}
//����
int Test(vector<int> featureVector,vector< vector<int> > featureVVevtor)
{
	vector<double> distVector;
	for(int i=0;i<featureVVevtor.size();i++)
	{
		double dist=CalDist(featureVector,featureVVevtor[i]);
		distVector.push_back(dist);
	}

	double mindist=10000000;
	int index;
	for(i=0;i<distVector.size();i++)
	{
		if(distVector[i]<mindist)
		{
			mindist=distVector[i];
			index=i;
		}
	}
	return index;

}

int main()
{
	//cvNamedWindow("ͼ����ʾ",CV_WINDOW_AUTOSIZE);

	int i,j,numoftraining;
	char str[100];
	IplImage *inputImg;
	vector <int> featureVector;
	vector < vector<int> > featureVVector;
	vector < vector<int> > mean_featureVVec;

	vector <int> mean_featureVec;

	//����ͼ��
	for(i=0;i<10;i++)
		for(j=6;j<11;j++)
		{
			sprintf(str,"C:\\�����Ӿ�\\��д����\\%d\\%d-%d.bmp",i,i,j);
			inputImg = cvLoadImage(str,1);


			featureVector.clear();
			CutImage(inputImg,4,4,featureVector,i,j);
		    featureVVector.push_back(featureVector);
			numoftraining=j;


			//cvShowImage("ͼ����ʾ",inputImg);
			//cvWaitKey(0);
		}
	int num=0;
	printf("ÿ�����ֵ�ѵ������������\n");
	for(i=0;i< featureVVector.size();++i)
	{
		if((i)%numoftraining==0)
		{
			printf("����%d��\n",num);
			num++;
		}
		for(j=0;j< featureVVector[i].size();++j)
		{
			printf("%d ",featureVVector[i][j]);
		}
		printf("\n");
		
	}
	printf("\n");
	printf("ƽ����������_wutianhao\n");


	
	i=0;
	j=0;

	int n=0;
	//printf("%d %d\n",featureVVector.size(),featureVVector[i].size());

	for(int k=0;k<featureVVector.size();k=k+5)
	{
	printf("\n");
	for(j=0;j<16;j++)//featureVVector[i].size()
	{
		int sum=0;
		
		for(i=k;i<k+5;i++)//featureVVector.size()
		{
			//printf("%d ",featureVVector[i][j]);
			sum=sum+featureVVector[i][j];
		}
		//printf("\n");
		sum=sum/5;
	    printf("%d ",sum);
		mean_featureVec.push_back(sum);
		
	
	}
	//
	mean_featureVVec.push_back(mean_featureVec);
	mean_featureVec.clear();
	}

	
/*

	printf("\n");
	num=0;
	for(i=0;i< mean_featureVVec.size();++i)
	{
		//if((i)%numoftraining==0)
		//{
		//	printf("����%d��\n",num);
		//	num++;
		//}
		for(j=0;j< mean_featureVVec[i].size();++j)
		{
			printf("%d ",mean_featureVVec[i][j]);
		}
		printf("\n");
		
	}*/
	printf("\n");
	printf("\n");
	printf("ʶ����\n");
	for(i=0;i<10;i++)
	{
		for(j=1;j<6;j++)
		{
			sprintf(str,"C:\\�����Ӿ�\\��д����\\%d\\%d-%d.bmp",i,i,j);
			inputImg = cvLoadImage(str,1);


			featureVector.clear();
			CutImage(inputImg,4,4,featureVector,i,j);
		    int m=Test(featureVector,mean_featureVVec);
			printf("%d ",m);
		}
		printf("\n");
	}

	sprintf(str,"C:\\�����Ӿ�\\��д����\\5\\5-7.bmp");
	inputImg = cvLoadImage(str,1);

	/*cvNamedWindow("wutianhao_ͼ����ʾ",CV_WINDOW_AUTOSIZE);

	cvShowImage("wutianhao_ͼ����ʾ",inputImg);
	cvWaitKey(0);
	cvReleaseImage(&inputImg);
    cvDestroyWindow("ͼ����ʾ");
	featureVector.clear();
	CutImage(inputImg,4,4,featureVector,5,7);
    int m=Test(featureVector,mean_featureVVec);
	printf("\n���������%d\n",m);*/
	
	return 0;
}
