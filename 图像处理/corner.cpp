//�������������ֳ���

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;


int mainco(int argv, char** argc)
{
	Mat srcImage = imread("C:/Users/db245/Desktop/1.png");

	if (srcImage.empty())
	{
		printf("could not load image..\n");
		return false;
	}
	Mat srcgray, dstImage, normImage, scaledImage;

	cvtColor(srcImage, srcgray, COLOR_BGR2GRAY);

	Mat srcbinary;
	threshold(srcgray, srcbinary, 0, 255, THRESH_OTSU | THRESH_BINARY);//�Զ�ѡ�����ֵ����ֵ�㷨
	imshow("binary_picture", srcbinary);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));//�Զ�����̬ѧ�����
	morphologyEx(srcbinary, srcbinary, MORPH_OPEN, kernel, Point(-1, -1));
	imshow("binary_picture1", srcbinary);

	/*
		//1��Harris�ǵ���
		cornerHarris(srcgray, dstImage, 3, 3, 0.01, BORDER_DEFAULT);
		//��һ����ת��
		normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
		convertScaleAbs(normImage, scaledImage);
		Mat binaryImage;
		threshold(scaledImage, binaryImage, 0, 255, THRESH_OTSU | THRESH_BINARY);
	*/


	//2��Shi-Tomasi�㷨��ȷ��ͼ��ǿ�ǵ�
	vector<Point2f> corners;//�ṩ��ʼ�ǵ������λ�ú;�ȷ�������λ��
	int maxcorners = 200;
	double qualityLevel = 0.01;  //�ǵ���ɽ��ܵ���С����ֵ
	double minDistance = 10;	//�ǵ�֮����С����
	int blockSize = 3;//���㵼������ؾ���ʱָ��������Χ
	double  k = 0.04; //Ȩ��ϵ��

	goodFeaturesToTrack(srcgray, corners, maxcorners, qualityLevel, minDistance, Mat(), blockSize, true, k);
	//Mat():��ʾ����Ȥ����false:��ʾ����Harris�ǵ���

	//����ǵ���Ϣ
	cout << "�ǵ���ϢΪ��" << corners.size() << endl;

	//���ƽǵ�
	RNG rng(12345);
	for (unsigned i = 0; i < corners.size(); i++)
	{
		circle(srcImage, corners[i], 2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
		cout << "�ǵ����꣺" << corners[i] << endl;
	}


	//3��Ѱ�������ؽǵ�
	Size winSize = Size(5, 5);  //���ش��ڵ�һ��ߴ�
	Size zeroZone = Size(-1, -1);//��ʾ������һ��ߴ�
	//��ǵ�ĵ������̵���ֹ���������ǵ�λ�õ�ȷ��
	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 40, 0.001);
	//TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);

	cornerSubPix(srcgray, corners, winSize, zeroZone, criteria);


	//����ǵ���Ϣ
	cout << "�ǵ���ϢΪ��" << corners.size() << endl;

	//���ƽǵ�
	for (unsigned i = 0; i < corners.size(); i++)
	{
		circle(srcImage, corners[i], 2, Scalar(255, 0, 0), -1, 8, 0);
		cout << "�ǵ����꣺" << corners[i] << endl;
	}

	imshow("window", srcImage);
	waitKey(0);
	return(0);

}