# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src;
const char* drawdemo_win = "draw shape and text demo";
void mylines();
void myrectangle();
void myellipse();
void mycircle();
void myploygon();
void Randomline();

string filename = "E:\\opencv learning\\OpenCV_Logo.png";

int main7()
{
	src = imread(filename);
	if (!src.data)
	{
		cout << "can not load image" << endl;
		return -1;
	}
	/*mylines();
	myrectangle();
	myellipse();
	mycircle();
	myploygon();*/
    Randomline();

	//putText(src, "Hello opencv", Point(100, 250), FONT_HERSHEY_SCRIPT_COMPLEX, 2.0, Scalar(20, 12, 45), 1, 8);
	//（图片，文字，起始点，字体，字号大小，颜色，线宽，线型）


	//namedWindow("mywindow", WINDOW_AUTOSIZE);
	//imshow("my image", src);



	waitKey(0);
	return 0;
}
void mylines()
{
	Point p1 = Point(20, 30);
	Point p2;
	p2.x = 300;
	p2.y = 300;
	Scalar color = Scalar(0, 0, 255);//red
	line(src, p1, p2, color, 1, LINE_AA);//两点连线

}
void myrectangle()
{
	Rect rect = Rect(20,10,30,30);//(x,y,width,height),指定矩形的坐标和大小
	Scalar color = Scalar(0, 255, 0);
	rectangle(src, rect, color, 2, LINE_8);//（图像，矩形位置大小，颜色，线宽，线型）

}
void myellipse()
{
	Scalar color = Scalar(255, 0, 0);
	ellipse(src, Point(src.cols / 2, src.rows / 2), Size(src.cols / 4, src.rows / 8), 0, 0, 360, color, 2, LINE_8);
	//（图像，中心，坐标轴（长轴，短轴），旋转角度，起始角度，终止角度，颜色，线宽，线型）
}
void mycircle()
{
	Scalar color = Scalar(0, 255, 0);
	Point center = Point(src.rows / 2, src.cols / 2);
	circle(src, center, 80, color, 2, 8);//80为半径
}
void myploygon()
{
	Point pts[1][5];
	pts[0][0] = Point(100, 100);
	pts[0][1] = Point(100, 200);
	pts[0][2] = Point(200, 200);
	pts[0][3] = Point(200, 100);
	pts[0][4] = Point(100, 100);

	const Point* ppts[] = { pts[0] };//指针数组，包含5个点
	int npt[] = {5};
	Scalar color = Scalar(0, 255, 130);
	fillPoly(src, ppts, npt,1, color, 8);//npt[]包含每一个多边形的点的数量，1表示只有一个多边形,填充后的多边形
}
void Randomline()
{
	RNG  rng(12345);
	Point pt1;
	Point pt2;

	Mat b = Mat::zeros(src.size(), src.type());
	for (int i = 0; i < 10000; i++)
	{
	pt1.x = rng.uniform(0, src.cols);
	pt2.x = rng.uniform(0, src.cols);
	pt1.y = rng.uniform(0, src.rows);
	pt2.y = rng.uniform(0, src.rows);
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	namedWindow("newwindow", WINDOW_AUTOSIZE);
	if (waitKey(50) > 0)
	{
		break;
	}
	line(b, pt1, pt2, color, 2, 8);
	imshow("radom_image", b);

	}
	

}