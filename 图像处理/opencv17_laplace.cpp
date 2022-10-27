//Laplace����
# include<opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main17()
{
	Mat src, dist;
	string filename = "E:\\opencv learning\\OpenCV_Logo.png";
	src = imread(filename);
	if (!src.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src);

	Mat gdist, gray_src;

	GaussianBlur(src, gdist, Size(3, 3), 0, 0);

	cvtColor(gdist, gray_src, COLOR_RGB2GRAY);

	Laplacian(gray_src, dist, CV_16S, 3);

	convertScaleAbs(dist, dist);//�����ڽ�CV_16S��CV_32F���������͵����ͼ��ת���CV_8U�͵�ͼ��


	threshold(dist, dist, 0, 255, THRESH_OTSU | THRESH_BINARY);//��ֵ��
	imshow(output, dist);



	waitKey(0);
	return 0;
}