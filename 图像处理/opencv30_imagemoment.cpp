# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src_mo, dist_m0, gray_mo,gauss_mo;
RNG rng_mo(12345);
char output_mo[] = "outputwindow";
int therhold_mo_value = 100;
int therhold_max_mo = 255;
void Demo_moment(int, void*);

int main30()
{
	
	string filename = "E:\\opencv learning\\mcircle.jpg";
	src_mo = imread(filename);
	if (!src_mo.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output_mo, WINDOW_AUTOSIZE);
	imshow(input, src_mo);

	cvtColor(src_mo, gray_mo, COLOR_BGR2GRAY);
	GaussianBlur(gray_mo, gauss_mo, Size(3, 3), 0, 0, 4);

	const char* trackbartitle = "therholdvalue";

	createTrackbar(trackbartitle, output_mo, &therhold_mo_value, therhold_max_mo, Demo_moment);



	waitKey(0);
	return 0;
}
void Demo_moment(int, void*)
{
	Mat canny_imge;
	vector<vector<Point>> countours;
	vector<Vec4i> hierachy;
	
	Canny(gauss_mo, canny_imge, therhold_mo_value, therhold_mo_value*2,3,false);
	findContours(canny_imge, countours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments> countours_moments(countours.size());
	vector<Point2f> ccs(countours.size());//中心位置,质心
	for (size_t i = 0; i < countours.size(); i++)
	{
		countours_moments[i]=moments(countours[i]);
		ccs[i] = Point(saturate_cast<float>(countours_moments[i].m10 / countours_moments[i].m00),//x
			saturate_cast<float>(countours_moments[i].m01 / countours_moments[i].m00));//y
	}

	Mat drawing;
	src_mo.copyTo(drawing);
	
	for (size_t t = 0; t < countours.size(); t++)

	{
		Scalar color = Scalar(rng_mo.uniform(0, 255), rng_mo.uniform(0, 255), rng_mo.uniform(0, 255));
		if (contourArea(countours[t]) > 20)
		{
			cout << "countours[" << t << "] area:" << contourArea(countours[t]) << endl;
			cout << "countours[" << t << "] length:" << arcLength(countours[t], 1) << endl;
			drawContours(drawing, countours, t, color, 1, 8, hierachy, 0, Point(0, 0));
			circle(drawing, ccs[t], 3, color, 3, 8);
			cout << "countours[" << t << "] center is (" << ccs[t].x << ", " << ccs[t].y << ")" << endl;
		}
		
	}
	imshow("cannny image", canny_imge);
	imshow(output_mo, drawing);


}