//Histogram
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;


int main22()
{
	Mat src_m, dist_m,gray_src;
	string filename = "E:\\opencv learning\\l.jpg";
	src_m = imread(filename);
	if (!src_m.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src_m);
	cvtColor(src_m, gray_src, COLOR_BGR2GRAY);
	equalizeHist(gray_src, dist_m);
	imshow(output, dist_m);
	waitKey(0);
	return 0;
}