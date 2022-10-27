# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;
int main5(int argc, char** argv[])
{
	string filename1 = "E:\\opencv learning\\R.jpg";
	string filename2 = "E:\\opencv learning\\l.jpg";
	Mat src1,src2,dist;
	src1 = imread(filename1);
	src2 = imread(filename2);

	if (src1.empty())
	{
		cout << "can not load imag" << endl;
		return -1;
	}
	if (!src2.data)
	{
		cout << "can not load imag" << endl;
		return -1;
	}
	double alpha = 0.5;
	
	if (src1.rows == src2.rows && src1.cols == src2.cols && src1.type() == src2.type())
	{
		addWeighted(src1, alpha, src2, (1 - alpha), 0.0, dist);
		//add(src1, src2, dist);
		//multiply(src1, src2, dist, 1.0);
	}
	else
	{
		cout << "Í¼Ïñ²»Æ¥Åä£¡" << endl;
		return -1;
	}

	namedWindow("firstwindow", WINDOW_AUTOSIZE);
	imshow("input_imag", dist);
	waitKey(0);


	return 0;
}