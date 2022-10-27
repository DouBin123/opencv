# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main6()
{
	Mat src, dist,dist2;
	src = imread("E:\\opencv learning\\OpenCV_Logo.png");
	if (!src.data)
	{
		cout << "can not load imag" << endl;
		return -1;
	}
	char input_win[] = "input image";

	

	//contrast and bright changed
	int height = src.rows;
	int width = src.cols;
	int cn = src.channels();
	double alpha = 0.8;//对比度
	double beta = 10;//亮度
	dist = Mat::zeros(src.size(), src.type());
	Mat m1,m2;
	src.convertTo(m1, CV_32F);
	cvtColor(src, m2, COLOR_RGB2GRAY);
	dist2 = Mat::zeros(m2.size(), m2.type());
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (cn == 3)
			{
				float b = m1.at<Vec3f>(row, col)[0];
				float g = m1.at<Vec3f>(row, col)[1];
				float r = m1.at<Vec3f>(row, col)[2];

				dist.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
				dist.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
				dist.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);

			}
			else if (cn== 1)
			{
				float v = m2.at<uchar>(row, col);
				dist2.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha + beta);

			}

		}
	}
	char ouput_title[] = "contrast and bright change demo";
	namedWindow(ouput_title, WINDOW_AUTOSIZE);
	imshow("output", dist);
	namedWindow("gray_win", WINDOW_AUTOSIZE);
	imshow("opencv", dist2);
	waitKey(0);
	return 0;
}