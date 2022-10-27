//countoursfind
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src_c, dist_c, gray_src_c,canny_c;
void Demo_Countours(int, void*);
char output1[] = "outputwindow";

int threholdvalue = 100;
int threholdmax = 255;

int main27()
{
	
	string filename = "E:\\opencv learning\\l.jpg";
	src_c = imread(filename);
	if (!src_c.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}
	char input[] = "inputwindow";
	
	
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output1, WINDOW_AUTOSIZE);
	imshow(input, src_c);
	cvtColor(src_c, gray_src_c, COLOR_BGR2GRAY);
	GaussianBlur(gray_src_c, gray_src_c, Size(3, 3), 1);
	const char* trackbartitle = "Threhold value";
	createTrackbar(trackbartitle, output1, &threholdvalue, threholdmax, Demo_Countours);
	
	waitKey(0);
	return 0;
}

void Demo_Countours(int, void*)
{
	vector<vector<Point>> countours;
	vector<Vec4i> hierachy;
	Canny(gray_src_c, canny_c, threholdvalue,threholdvalue*2,3,false);
	findContours(canny_c, countours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	dist_c = Mat::zeros(src_c.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < countours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dist_c, countours, i, color, 1, 8, hierachy, 0, Point(0, 0));
	}
	imshow(output1, dist_c);
}