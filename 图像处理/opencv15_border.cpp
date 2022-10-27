//±ßÔµ²Ù×÷
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main15()
{
	Mat src, dist;
	string filename = "E:\\opencv learning\\OpenCV_Logo.png";
	src = imread(filename);
	if (!src.data)
	{
		cout << "can not open the image";
		return -1;
	}

	namedWindow("input_window", WINDOW_AUTOSIZE);
	char  output[] = "output_window";
	namedWindow(output, WINDOW_AUTOSIZE);

	imshow("input_window", src);

	int top =(int) (0.05 * src.rows);
	int bottom = (int)(0.05 * src.rows);
	int right = (int)(0.05 * src.cols);
	int left = (int)(0.05 * src.cols);

	RNG rng(12345);
	int borderType = BORDER_DEFAULT;

	int c = 0;
	while (1)
	{
		c = waitKey(500);
		//ESC
		if ((char)c == 27)
		{
			
		}
		else if((char)c=='r')
		{
			borderType = BORDER_REPLICATE;
			
		}
		else if((char)c=='v')
		{
			borderType = BORDER_WRAP;
		}
		else if ((char)c == 'c')
		{
			borderType = BORDER_CONSTANT;
		}
		
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(src, dist, top, bottom, left, right, borderType, color);
		imshow(output, dist);
	}



	waitKey(0);
	return 0;
}