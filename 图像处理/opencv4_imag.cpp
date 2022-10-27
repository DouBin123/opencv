# include <opencv2/opencv.hpp>
# include <iostream>
# include <cmath>

using namespace std;
using namespace cv;

int main4(int argc,char**argv[])
{
	Mat src,gray_src;
	string filename = "E:\\opencv learning\\R-C.jpg";
	src = imread(filename);
	if (src.empty())
	{
		cout << "can not load" << endl;
		return -1;
	}
	namedWindow("firstwindow", WINDOW_AUTOSIZE);
	imshow("first_imag", src);


	cvtColor(src, gray_src, COLOR_RGB2GRAY);
	namedWindow("secondwindow", WINDOW_AUTOSIZE);
	//imshow("gray_imag", gray_src);

	int rows = gray_src.rows;
	int cols = gray_src.cols;
	//单通道
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			int gray=gray_src.at<uchar>(row, col);//像素值
			gray = gray_src.at<uchar>(row, col) = 255 - gray;//反向
		}

	}
	imshow("reverse_imag", gray_src);

	Mat dst;
	dst.create(src.size(), src.type());
	int height = src.rows;
	int width = src.cols;
	int nc = src.channels();
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (nc == 1)//单通道
			{
			int gray = gray_src.at<uchar>(row, col);//像素值
			gray = gray_src.at<uchar>(row, col) = 255 - gray;//反向

			}
			else if(nc==3)
			{
				int b = src.at<Vec3b>(row, col)[0];
				int g = src.at<Vec3b>(row, col)[1];
				int r = src.at<Vec3b>(row, col)[2];
				dst.at<Vec3b>(row, col)[0] =b;
				dst.at<Vec3b>(row, col)[1] =0;
				dst.at<Vec3b>(row, col)[2] =r;
				gray_src.at<uchar>(row, col) = min(r, min(g, b));
				//gray_src.at<uchar>(row, col) = max(r, max(g, b));

			}
		}

	}

	imshow("gray1_imag", gray_src);
	
	Mat dst1;
	src.convertTo(dst1, CV_32F);//将CV_8UC1转换为CV_32F   8位uchar转32位float
	//bitwise_not(src, dst1);
	imshow("reverse2", dst);
	//imshow("reverse3", dst1);


	waitKey(0);

	return 0;
}