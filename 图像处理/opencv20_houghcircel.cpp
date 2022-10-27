# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main20()
{
	Mat src, dist, gray_src;
	string filename = "E:\\opencv learning\\hough.png";
	src = imread(filename);
	if (!src.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src);

	//÷–÷µ¬À≤®
	Mat moutput;
	medianBlur(src,moutput,3);
	cvtColor(moutput, gray_src, COLOR_BGR2GRAY);
	
	//ªÙ∑ÚºÏ≤‚
	vector<Vec3f> pcircle;
	HoughCircles(gray_src,pcircle,HOUGH_GRADIENT,1,10,100,40,0,0);//40 «≈–∂œ‘≤≤ª‘≤µƒ„–÷µ
	src.copyTo(dist);
	for (size_t i = 0; i < pcircle.size(); i++)
	{
		Vec3f cc = pcircle[i];
		circle(dist, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255), 2, LINE_AA);//‘≤
		circle(dist, Point(cc[0], cc[1]), 2, Scalar(0, 154, 255), 2, LINE_AA);//‘≤–ƒ

	}
	//imshow("output",gray_src);
	imshow(output, dist);

	waitKey(0);
	return 0;
}