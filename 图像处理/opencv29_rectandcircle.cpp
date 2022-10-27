//最小外接矩形与椭圆
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src_rc, dist_rc, gray_rc;
int ther_rc_value = 170;
int ther_rc_max = 255;
char output_rc[] = "outputwindow";
void  Countours_Callback(int,void*);
RNG rng1;

int main29()
{
	
	string filename = "E:\\opencv learning\\R.jpg";
	src_rc = imread(filename);
	resize(src_rc,src_rc,Size(800,400));
	if (!src_rc.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output_rc, WINDOW_AUTOSIZE);
	imshow(input, src_rc);
	cvtColor(src_rc, gray_rc, COLOR_BGR2GRAY);
	blur(gray_rc, gray_rc, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);


	const char* trackbar_title = "ther_rc";

	createTrackbar(trackbar_title, output_rc, &ther_rc_value, ther_rc_max, Countours_Callback);




	waitKey(0);
	return 0;
}
void  Countours_Callback(int,void*)
{
	Mat binary_output;
	threshold(gray_rc, binary_output, ther_rc_value, ther_rc_max, THRESH_BINARY);
	vector<vector<Point>> countours;
	vector<Vec4i> hierachy;
	findContours(binary_output, countours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(-1, -1));

	vector<vector<Point>> conpolys(countours.size());//多边形角点
	vector<Rect> poly_rects(countours.size());//矩形
	vector<Point2f> ccs(countours.size());//圆心
	vector<float> radius(countours.size());//半径

	//旋转矩形
	vector<RotatedRect> minRects(countours.size());//旋转矩形
	vector<RotatedRect> myellipse(countours.size());

	for (size_t i = 0; i < countours.size(); i++)
	{
		approxPolyDP(Mat(countours[i]), conpolys[i], 3, true);//多边形拟合
		poly_rects[i]=boundingRect(conpolys[i]);//边界矩形
		minEnclosingCircle(conpolys[i], ccs[i], radius[i]);//包围二维点集的最小圆
		
		if (conpolys[i].size() > 5)//至少为6个点
		{
			myellipse[i] = fitEllipse(conpolys[i]);//拟合的最小外接矩形
			minRects[i] = minAreaRect(conpolys[i]);
		}
		
	}
	//draw it
	src_rc.copyTo(dist_rc);
	Point2f pts[4];

	for (size_t t = 0; t < (countours.size()); t++)
	{
		Scalar color = Scalar(rng1.uniform(0, 255), rng1.uniform(0, 255), rng1.uniform(0, 255));
		//rectangle(dist_rc, poly_rects[t], color);
		//circle(dist_rc, ccs[t], radius[t], color, 1, 8);

		ellipse(dist_rc, myellipse[t], color,1,8);
		minRects[t].points(pts);//
		for (int r = 0; r < 4; r++)
		{
			line(dist_rc, pts[r], pts[(r + 1) % 4], color,1,8);
		}

	}


	imshow(output_rc, dist_rc);
}