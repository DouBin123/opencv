# include <opencv2/opencv.hpp>
# include <iostream>
using namespace cv;
int main()
{
	Mat img = imread("D:\\my_data\\programming\\c++\\opencv learning\\ming.jpg");//����ͼƬ
	if (img.empty())
	{
		std::cout << "couldn't load imag";
	}


	namedWindow("outputwindow", WINDOW_AUTOSIZE);
	Mat output_imag;
	resize(img, output_imag, Size(144, 192));
	//cvtColor(img, output_imag, COLOR_RGB2GRAY);//�޸ĸ�ʽ���任ɫ�ʿռ�
	imshow("output_imag", output_imag);
	imwrite("D:\my_data\programming\c++\opencv learning\ming2.jpg", output_imag);//����ͼƬ
	waitKey(0);

	return 0;
}



