# include <opencv2/opencv.hpp>
# include <iostream>
using namespace cv;
int main1()
{
	Mat img = imread("E:\\opencv learning\\OpenCV_Logo.png");//加载图片
	if (img.empty())
	{
		std::cout << "couldn't load imag";
	}
	namedWindow("windowtitle", WINDOW_AUTOSIZE);
	imshow("opencv", img);


	namedWindow("outputwindow", WINDOW_AUTOSIZE);
	Mat output_imag;
	cvtColor(img, output_imag, COLOR_RGB2GRAY);//修改格式，变换色彩空间
	imshow("output_imag", output_imag);
	// imwrite("E:\\opencv learning\\OpenCV_gay.png", output_imag);//保存图片
	waitKey(0);

	return 0;
}



