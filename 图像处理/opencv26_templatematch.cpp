//模板匹配
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src_m1, src11, dist_m1, gray_src1;
int match_method = TM_SQDIFF;
int max_track = 5;
void Match_Demo(int, void*);
char input[] = "inputwindow";
char output[] = "outputwindow";
char match_t[] = "match window";

int main26()
{

	
	string filename = "E:\\opencv learning\\l1.jpg";//待检测图像
	string filename1 = "E:\\opencv learning\\l.jpg";//模板图像
	src_m1= imread(filename);
	src11= imread(filename1);
	if (!src_m1.data&&!src11.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}


	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	namedWindow(match_t, WINDOW_AUTOSIZE);


	imshow(input, src_m1);
	const char* trackbar_title = "Match Algo Type";
	createTrackbar(trackbar_title, output, &match_method, max_track, Match_Demo);

	waitKey(0);
	return 0;
}
void Match_Demo(int, void*)
{
	int width = src11.cols - src_m1.cols + 1;
	int height = src11.rows - src_m1.rows + 1;

	Mat result(width,height,CV_32FC1);

	matchTemplate(src11, src_m1, result, match_method, Mat());
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	//匹配值的最小值与最大值的位置
	Point minLoc;
	Point maxLoc;
	double min, max;
	src11.copyTo(dist_m1);
	Point temLoc;
	minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());
	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)//
	{
		temLoc = minLoc;
	}
	else
	{
		temLoc = maxLoc;
	}

	//绘制矩形
	rectangle(dist_m1, Rect(temLoc.x, temLoc.y, src_m1.cols, src_m1.rows), Scalar(0, 0, 255), 2, 8);
	rectangle(result, Rect(temLoc.x, temLoc.y, src_m1.cols, src_m1.rows), Scalar(0, 0, 255), 2, 8);

	imshow(output, result);
	imshow(match_t, dist_m1);
}