# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;


int main31()
{
	const int r = 100;
	Mat src = Mat::zeros(r * 4, r * 4, CV_8UC1);

	vector<Point2f> vert(6);
	vert[0] = Point(3 * r / 2, static_cast<float>(1.34 * r));
	vert[1] = Point(1* r,2*r);
	vert[2] = Point(3 * r / 2, static_cast<float>(2.866 * r));
	vert[3] = Point(5 * r / 2, static_cast<float>(2.866 * r));
	vert[4] = Point(3 * r , 2*r);
	vert[5] = Point(5 * r / 2, static_cast<float>(1.34 * r));

	for (int i = 0; i < 6; i++)
	{
		line(src, vert[i], vert[(i + 1) % 6], Scalar(255, 0, 0), 3, 8, 0);
	}
	vector<vector<Point>> countours;
	vector<Vec4i> hierachy;
	findContours(src, countours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat raw_dist = Mat::zeros(src.size(), CV_32FC1);//点对于多边形的位置图（像素范围-1,0，1）
	for (int row = 0; row < raw_dist.rows; row++)
	{
		for (int col = 0; col < raw_dist.cols; col++)
		{
			double dist = pointPolygonTest(countours[0], Point2f(static_cast<float>(col), static_cast<float>(row)), true);
			raw_dist.at<float>(row, col) = static_cast<float>(dist);
		}
	}
	double minValue, maxValue;
	minMaxLoc(raw_dist, &minValue, &maxValue, 0, 0, Mat());
	Mat drawing = Mat::zeros(src.size(), CV_8UC3);//距离分布效果图
	for (int row = 0; row < drawing.rows; row++)
	{
		for (int col = 0; col < drawing.cols; col++)
		{
			float dist_d = raw_dist.at<float>(row, col);
			if (dist_d > 0)
			{
				drawing.at<Vec3b>(row, col)[0] = (uchar)(abs(dist_d / maxValue) * 255);
			}
			else if (dist_d < 0)
			{
				drawing.at<Vec3b>(row, col)[2] = (uchar)(abs(1.0-dist_d / minValue) * 255);
			}
			else
			{
				//white(255,255,255)
				drawing.at<Vec3b>(row, col)[0] = (uchar)(abs(255-dist_d));
				drawing.at<Vec3b>(row, col)[1] = (uchar)(abs(255 - dist_d));
				drawing.at<Vec3b>(row, col)[2] = (uchar)(abs(255 - dist_d));

			}
		}
	}

	const char* output_win = "point polygon test demo";
	char input[] = "input image";
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output_win, WINDOW_AUTOSIZE);

	imshow(input, src);
	imshow("distance_image", raw_dist);
	imshow(output_win, drawing);
	waitKey(0);
	return 0;

}