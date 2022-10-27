//sobel算子
# include<opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main16()
{
	Mat src, dist;
	string filename = "E:\\opencv learning\\OpenCV_Logo.png";
	src = imread(filename);
	if (!src.data)
	{
		cout << "cannot open the image"<<endl;
		return -1;
	}
	
	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src);

	GaussianBlur(src, dist, Size(3, 3), 0, 0);//高斯模糊

	Mat gray_src;
	cvtColor(src, gray_src, COLOR_RGB2GRAY);

	Mat gradx, grady;
	Scharr(gray_src, gradx, CV_16S, 1, 0);//scharr滤波器主要是配合sobel算子运算的，
	//分别计算x方向或y方向的图像差分
	Scharr(gray_src, grady, CV_16S, 0, 1);
	//虽然Sobel算子可以有效的提取图像边缘，但是对图像中较弱的边缘提取效果较差。
	//因此为了能够有效的提取出较弱的边缘，需要将像素值间的差距增大，因此引入Scharr算子。
	//Scharr算子是对Sobel算子差异性的增强，因此两者之间的在检测图像边缘的原理和使用方式上相同。

	//Sobel(gray_src, gradx, -1, 1, 0, 3);//得到的图像不是很清晰
	//Sobel(gray_src, gradx, CV_16S, 1, 0, 3);//防止溢出设置为CV_16S
	//Sobel(gray_src, grady, CV_16S, 0, 1, 3);

	//数据处理，防止负值

	convertScaleAbs(gradx, gradx);//将负值转化
	convertScaleAbs(grady, grady);
	//显示输出

	imshow(output, gray_src);
	imshow("xgrad", gradx);
	imshow("ygrad", grady);

	//混合
	//Mat fdist;
	//addWeighted(gradx, 0.5, grady, 0.5, 0, fdist);
	Mat fdist = Mat(gradx.size(), gradx.type());
	cout << "gradxtype:" << gradx.type() << endl;
	int width = gradx.cols;
	int height = grady.rows;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int xg = gradx.at<uchar>(row, col);
			int yg = grady.at<uchar>(row, col);
			fdist.at<char>(row, col) =saturate_cast<uchar> (xg + yg);
		}
	}

	imshow(output, fdist);
	waitKey(0);
	return 0;
}