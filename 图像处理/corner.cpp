//代码里面有三种程序

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
	threshold(srcgray, srcbinary, 0, 255, THRESH_OTSU | THRESH_BINARY);//自动选择处理二值化阈值算法
	imshow("binary_picture", srcbinary);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));//自定义形态学处理核
	morphologyEx(srcbinary, srcbinary, MORPH_OPEN, kernel, Point(-1, -1));
	imshow("binary_picture1", srcbinary);

	/*
		//1、Harris角点检测
		cornerHarris(srcgray, dstImage, 3, 3, 0.01, BORDER_DEFAULT);
		//归一化与转换
		normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
		convertScaleAbs(normImage, scaledImage);
		Mat binaryImage;
		threshold(scaledImage, binaryImage, 0, 255, THRESH_OTSU | THRESH_BINARY);
	*/


	//2、Shi-Tomasi算法：确定图像强角点
	vector<Point2f> corners;//提供初始角点的坐标位置和精确的坐标的位置
	int maxcorners = 200;
	double qualityLevel = 0.01;  //角点检测可接受的最小特征值
	double minDistance = 10;	//角点之间最小距离
	int blockSize = 3;//计算导数自相关矩阵时指定的领域范围
	double  k = 0.04; //权重系数

	goodFeaturesToTrack(srcgray, corners, maxcorners, qualityLevel, minDistance, Mat(), blockSize, true, k);
	//Mat():表示感兴趣区域；false:表示不用Harris角点检测

	//输出角点信息
	cout << "角点信息为：" << corners.size() << endl;

	//绘制角点
	RNG rng(12345);
	for (unsigned i = 0; i < corners.size(); i++)
	{
		circle(srcImage, corners[i], 2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
		cout << "角点坐标：" << corners[i] << endl;
	}


	//3、寻找亚像素角点
	Size winSize = Size(5, 5);  //搜素窗口的一半尺寸
	Size zeroZone = Size(-1, -1);//表示死区的一半尺寸
	//求角点的迭代过程的终止条件，即角点位置的确定
	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 40, 0.001);
	//TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);

	cornerSubPix(srcgray, corners, winSize, zeroZone, criteria);


	//输出角点信息
	cout << "角点信息为：" << corners.size() << endl;

	//绘制角点
	for (unsigned i = 0; i < corners.size(); i++)
	{
		circle(srcImage, corners[i], 2, Scalar(255, 0, 0), -1, 8, 0);
		cout << "角点坐标：" << corners[i] << endl;
	}

	imshow("window", srcImage);
	waitKey(0);
	return(0);

}