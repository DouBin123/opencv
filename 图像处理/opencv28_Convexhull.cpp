//凸包
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src_convex, dist_convex, gray_src_convex,bin_convex;
char output_convex[] = "outputwindow";
RNG rng(12345);
int therhold_convex_value = 100;
int therhold_convex_max = 255;

void Therhold_Callback(int, void*);

int main28()
{
	
	string filename = "E:\\opencv learning\\l.jpg";
	src_convex = imread(filename);
	if (!src_convex.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output_convex, WINDOW_AUTOSIZE);
	imshow(input, src_convex);
	const char* trackbar_title = "Therhold";

	cvtColor(src_convex, gray_src_convex, COLOR_BGR2GRAY);
	blur(gray_src_convex, gray_src_convex, Size(3, 3), Point(-1, -1), BORDER_REPLICATE);

	createTrackbar(trackbar_title, output_convex, &therhold_convex_value, therhold_convex_max, Therhold_Callback);

	waitKey(0);
	return 0;
}
void Therhold_Callback(int, void*)
{
	threshold(gray_src_convex, bin_convex, therhold_convex_value, therhold_convex_max, THRESH_BINARY);//二值化
	vector<vector<Point>> countours;
	vector<Vec4i> hierachy;
	findContours(bin_convex, countours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>>  convexs(countours.size());
	for (size_t i = 0; i < countours.size(); i++)
	{
		convexHull(countours[i], convexs[i], false, true);

	}
	//绘制
	dist_convex = Mat::zeros(src_convex.size(), CV_8UC3);
	vector<Vec4i> empty;
	for (size_t i = 0; i < countours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dist_convex, countours, i, color, 2, 8,hierachy, 0, Point(0, 0));
		drawContours(dist_convex, convexs, i, color, 2, 8, empty, 0, Point(0, 0));

	}
	imshow(output_convex, dist_convex);

}