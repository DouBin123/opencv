# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

string convertToString(double);

int main24()
{
	Mat src_m,src, dist_m, hsv_src, hsv_src_m;
	string filename1 = "E:\\opencv learning\\l.jpg";
	string filename2 = "E:\\opencv learning\\OpenCV_Logo.png";

	src_m = imread(filename1);
	if (!src_m.data)
	{
		cout << "cannot open the image1" << endl;
		return -1;
	}
	src = imread(filename2);
	if (!src.data)
	{
		cout << "cannot open the image2" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);

	//色彩空间转换
	cvtColor(src_m, hsv_src_m, COLOR_BGR2HSV);
	cvtColor(src, hsv_src, COLOR_BGR2HSV);

	
	//计算多通道直方图
	int h_bins = 50;//h坐标格子数
	int s_bins = 60;//s坐标格子数
	int histSize[] = { h_bins,s_bins };
	//hue varies from 0-179,saturation from 0-255
	float h_ranges[] = { 0,180 };//h坐标范围
	float s_ranges[] = { 0,256 };//s坐标范围
	const float* ranges[] = { h_ranges,s_ranges };
	//use the 0-th and 1-st channels
	int channels[] = { 0,1 };

	
	MatND hist_base;//多个Mat
	MatND hist_m;

	calcHist(&hsv_src, 1,channels, Mat(), hist_base, 2, histSize, ranges, true, false);
	calcHist(&hsv_src_m, 1, channels, Mat(), hist_m, 2, histSize, ranges, true, false);

	//归一化
	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist_m, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

	//直方图比较
	double base = compareHist(hist_base, hist_m, HISTCMP_BHATTACHARYYA);
	cout << "base compared with base_m 's result is:" << base << endl;
	putText(src_m, convertToString(base), Point(50, 50), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);

	imshow(output, src_m);
	waitKey(0);

	return 0;
}
string convertToString(double d)
{
	ostringstream os;
	if (os << d)
	{
		return os.str();
	}
	return "invalid conversion!";

}