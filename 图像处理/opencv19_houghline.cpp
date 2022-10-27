//霍夫直线变换
# include<opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main19()
{
	Mat src, dist,gray_src;
	string filename = "E:\\opencv learning\\hough.png";
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
	
	//extract edge
	Canny(src, gray_src, 150, 200);
	cvtColor(gray_src, dist, COLOR_GRAY2RGB);
	imshow(output, gray_src);

	//hough
	vector<Vec4f> pline;
	cout <<"pline1:" << pline.size() << endl;//此处pline未被初始化
	HoughLinesP(gray_src, pline, 1, CV_PI / 180.0, 10, 40, 10);
	cout <<"pline2:" << pline.size() << endl;//经过霍夫变化pline被初始化

	Scalar color = Scalar(0, 0, 255);
	for (size_t i = 0; i < pline.size(); i++)
	{
		Vec4f hline = pline[i];
		line(dist, Point(hline[0], hline[1]), Point(hline[2], hline[3]),color
		,3,LINE_AA);
	}
	imshow("hough", dist);
	waitKey(0);
	return 0;
}
