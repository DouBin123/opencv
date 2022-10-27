# include <opencv2/opencv.hpp>
# include <iostream>
using namespace cv;
int main2()
{
	std::string filename = "E:\\opencv learning\\R-C.jpg";
	Mat src = imread(filename);
	if (src.empty())
	{
		std::cout << "can not load imag" << std::endl;
		return -1;
	}
	int cols = src.cols * src.channels();//rgb为三通道
	int rows = src.rows;
	int offsetx=src.channels();
	Mat dst = Mat::zeros(src.size(), src.type());//两图像具有相同的尺寸

	//读取图像的像素进行掩膜操作,四个边界的像素在掩膜操作时用不到
	for (int row = 1; row < rows - 1; row++)
	{
		//获取行指针
		const uchar* previous = src.ptr<uchar>(row-1);
		const uchar* current = src.ptr<uchar>(row);
		const uchar* next = src.ptr<uchar>(row+1);
		//新图像的当前行指针
		uchar* output = dst.ptr<uchar>(row);
		//第一列包括通道数，故起始列为通道数*1
		for (int col = offsetx; col < cols - 1; col++)
		{
			output[col] =saturate_cast<char>( 5 * current[col] - previous[col] - current[col - offsetx] - current[col + offsetx] - next[col]);
			//saturate_cast<char>(n)确保RGB范围在0-255之间
			//二维数组的思想

		}
	}
	double t = getTickCount();
	Mat dst1;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	
	filter2D(src, dst1, src.depth(), kernel);
	double time = (getTickCount()-t)/getTickFrequency();

	std::cout << "time consume: " << time<< std::endl;
	namedWindow("initialwindow", WINDOW_AUTOSIZE);
	imshow("原图像", src);
	namedWindow("maskwindow", WINDOW_AUTOSIZE);
	imshow("掩膜操作后的图像", dst);
	namedWindow("kernelwindow", WINDOW_AUTOSIZE);
	imshow("kernel后的图像", dst);

	waitKey(0);


	return 0;
}