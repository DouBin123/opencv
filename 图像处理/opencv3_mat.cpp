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
	imshow("原图像", src);

	//Mat 对象的构造函数
	Mat dst;
	/*
	dst=Mat(src.size(), src.type());//尺寸类型			#1
	dst = Scalar(127, 0, 255);
	*/

	//dst = src;//克隆									#2
	//src.copyTo(dst);   //复制							#3
	cvtColor(src, dst, COLOR_RGB2GRAY);//				#4
	Mat m(3, 3, CV_8UC3, Scalar(0, 0, 255));//			#5
	/*
 [ 0,   0, 255,   0,   0, 255,   0,   0, 255;
   0,   0, 255,   0,   0, 255,   0,   0, 255;
   0,   0, 255,   0,   0, 255,   0,   0, 255]
	*/
	std::cout << m << std::endl;
	//Mat对象的方法和属性
	int cols = dst.cols;
	int rows = dst.rows;
	int channels = dst.channels();
	std::cout << "cols=" << cols << std::endl;
	std::cout << "row=" << rows << std::endl;
	std::cout << "channels=" << channels << std::endl;
	const uchar* firstrow = dst.ptr<uchar>(0);
	std::cout << "firstrow value:" << (int)*firstrow << std::endl;

	//mat 对象的使用，部分复制与完全复制
	//部分复制，只复制头和指针，不复制数据
	Mat b(src);
	//完全复制
	Mat c = src.clone();
	Mat d;
	src.copyTo(d);



	namedWindow("newwindow1", WINDOW_AUTOSIZE);
	imshow("新图像", dst);
	namedWindow("newwindow2", WINDOW_AUTOSIZE);
	imshow("新图像1", m);



	
	

	waitKey(0);


	return 0;
}