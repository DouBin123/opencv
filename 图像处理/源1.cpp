#include <opencv2/opencv.hpp>  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;


Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 30; //��ǰ��ֵ  
int max_thresh = 175; //�����ֵ  

void on_CornerHarris(int, void*);//�ص�����  

int mainjd(int argc, char** argv)
{
	g_srcImage = imread("C:\\Users\\db245\\Desktop\\ʵ������\\left1.jpg", 1);
	if (!g_srcImage.data)
	{
		printf("��ȡͼƬ���� \n");
		return -1;
	}
	resize(g_srcImage, g_srcImage,Size(640,322));
	imshow("ԭʼͼ", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	//����һ�ŻҶ�ͼ  
	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);

	//�������ں͹�����  
	namedWindow("�ǵ���", WINDOW_AUTOSIZE);
	createTrackbar("��ֵ: ", "�ǵ���", &thresh, max_thresh, on_CornerHarris);

	//����һ�λص����������г�ʼ��  
	on_CornerHarris(0, 0);

	waitKey(0);
	return(0);
}


void on_CornerHarris(int, void*)
{
	Mat dstImage;//Ŀ��ͼ  
	Mat normImage;//��һ�����ͼ  
	Mat scaledImage;//���Ա任��İ�λ�޷������͵�ͼ  

	//���㵱ǰ��Ҫ��ʾ������ͼ���������һ�ε��ô˺���ʱ���ǵ�ֵ  
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	//���нǵ���  
	//������������ʾ�����С�����ĸ�������ʾSobel���ӿ׾���С�������������ʾHarris����
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// ��һ����ת��  
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//����һ�����ͼ���Ա任��8λ�޷�������   

	// ����⵽�ģ��ҷ�����ֵ�����Ľǵ���Ƴ���  
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			//Mat::at<float>(j,i)��ȡ����ֵ��������ֵ�Ƚ�
			if ((int)normImage.at<float>(j, i) > thresh + 80)
			{
				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}

	imshow("�ǵ���", g_srcImage1);
	imshow("�ǵ���2", scaledImage);

}
