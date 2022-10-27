//自定义线性滤波
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main14()
{
	Mat src, distx,disty ,distsx,distsy,distl,dist;
	string filename = "E:\\opencv learning\\OpenCV_Logo.png";
	src=imread(filename);
	if (!src.data)
	{
		cout << "can not open the image";
		return -1;
	}
	char outputname[] = "output_window";
	namedWindow("input_window", WINDOW_AUTOSIZE);
	namedWindow(outputname,WINDOW_AUTOSIZE);

	imshow("input_window", src);
//
//	Mat kernel_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);//卷积核,Robet算子x方向
//	Mat kernel_y = (Mat_<int>(2, 2) << 0,1,-1,0);//卷积核,Robet算子y方向
//	Mat kernel_sx = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);//sobel算子x方向
//	Mat kernel_sy = (Mat_<int>(3, 3) << -1,-2,-1,0,0,0,1,2,1);//sobel算子y方向
//	Mat kernel_l = (Mat_<int>(3, 3) << 0,-1,0,-1,4,-1,0,-1,0);//Laplace算子
//	
//
////掩膜操作
//	filter2D(src, distx, -1, kernel_x, Point(-1, -1), 0);
//	filter2D(src, disty, -1, kernel_y, Point(-1, -1), 0);
//	filter2D(src, distsx, -1, kernel_sx, Point(-1, -1), 0);
//	filter2D(src, distsy, -1, kernel_sy, Point(-1, -1), 0);
//	filter2D(src, distl, -1, kernel_l, Point(-1, -1), 0);
//
//
//	imshow(outputname, distx);
//	imshow("yImag", disty);
//	imshow("sxImag", distsx);
//	imshow("syImag", distsy);
//	imshow("lImag", distl);

	int c = 0;
	int index = 0;
	int ksize = 3;
	while(1)
	{
		c = waitKey(500);
		if ((char)c == 27)//	ESC
		{
			break;
		}
		ksize = 4 + (index % 5) * 2 + 1;
		Mat kernel = Mat::ones(Size(ksize,ksize),CV_32F)/(float)(ksize*ksize);//自定义核
		filter2D(src, dist, -1, kernel, Point(-1, -1), 0);
		index++;
		imshow("distimag", dist);
	}
	waitKey(0);
	return 0;

}