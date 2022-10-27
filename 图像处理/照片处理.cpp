# include <opencv2/opencv.hpp>
# include <iostream>
using namespace cv;
int main()
{
	Mat img = imread("D:\\my_data\\programming\\c++\\opencv learning\\ming.jpg");//加载图片
	if (img.empty())
	{
		std::cout << "couldn't load imag";
	}


	namedWindow("outputwindow", WINDOW_AUTOSIZE);
	Mat output_imag;
	resize(img, output_imag, Size(144, 192));
	//cvtColor(img, output_imag, COLOR_RGB2GRAY);//修改格式，变换色彩空间
	imshow("output_imag", output_imag);
	imwrite("D:\my_data\programming\c++\opencv learning\ming2.jpg", output_imag);//保存图片
	waitKey(0);

	return 0;
}



