# include <opencv2/opencv.hpp>
# include <iostream>
using namespace cv;
int main3()
{
	std::string filename = "E:\\opencv learning\\R-C.jpg";
	Mat src;
	src = imread(filename);
	if (src.empty())
	{
		std::cout << "can not load imag" << std::endl;
		return -1;
	}
	namedWindow("initialwindow", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", src);

	//Mat ����Ĺ��캯��
	Mat dst;
	/*
	dst=Mat(src.size(), src.type());//�ߴ�����			#1
	dst = Scalar(127, 0, 255);
	*/

	//dst = src;//��¡									#2
	//src.copyTo(dst);   //����							#3
	cvtColor(src, dst, COLOR_RGB2GRAY);//				#4
	Mat m(3, 3, CV_8UC3, Scalar(0, 0, 255));//			#5
	/*
 [ 0,   0, 255,   0,   0, 255,   0,   0, 255;
   0,   0, 255,   0,   0, 255,   0,   0, 255;
   0,   0, 255,   0,   0, 255,   0,   0, 255]
	*/
	std::cout << m << std::endl;
	//Mat����ķ���������
	int cols = dst.cols;
	int rows = dst.rows;
	int channels = dst.channels();
	std::cout << "cols=" << cols << std::endl;
	std::cout << "row=" << rows << std::endl;
	std::cout << "channels=" << channels << std::endl;
	const uchar* firstrow = dst.ptr<uchar>(0);
	std::cout << "firstrow value:" << (int)*firstrow << std::endl;

	//mat �����ʹ�ã����ָ�������ȫ����
	//���ָ��ƣ�ֻ����ͷ��ָ�룬����������
	Mat b(src);
	//��ȫ����
	Mat c = src.clone();
	Mat d;
	src.copyTo(d);



	namedWindow("newwindow1", WINDOW_AUTOSIZE);
	imshow("��ͼ��", dst);
	namedWindow("newwindow2", WINDOW_AUTOSIZE);
	imshow("��ͼ��1", m);



	
	

	waitKey(0);


	return 0;
}