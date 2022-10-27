//cannyÀ„∑®
# include<opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat vsrc, vdist;
int t1_value=50;
int max_value=255;
Mat  gray_src;
void Cannydemo(int,void*);

int main18()
{
	
	string filename = "E:\\opencv learning\\box.jpg";
	vsrc = imread(filename);
	if (!vsrc.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, vsrc);

	

	//GaussianBlur(src, gdist, Size(3, 3), 0, 0);

	cvtColor(vsrc, gray_src, COLOR_RGB2GRAY);

	createTrackbar("Threhold_value", output, &t1_value, max_value,Cannydemo);

	Cannydemo(0,0);
	cout << vsrc << endl;
	waitKey(0);
	return 0;


}
void Cannydemo(int,void*)
	{
	Mat edist;
	blur(gray_src, gray_src, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
	Canny(gray_src,edist,t1_value,t1_value*2,3,false);

	//vdist.create(vsrc.size(), vsrc.type());
	//vsrc.copyTo(vdist, edist);
	imshow("output", ~edist);

	}