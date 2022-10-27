//形态学操作，主要针对二值图像处理，开闭顶帽黑帽，形态学梯度
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src2, dist1;

int main10()
{
	string filename = "E:\\opencv learning\\R-C.jpg";

	src2 = imread(filename);
	if (!src2.data)
	{
		cout << "can not load image" << endl;
		return -1;
	}


	namedWindow("mywindow", WINDOW_AUTOSIZE);
	imshow("input_image", src2);
	char output_title[] = "morphologyex window";
	namedWindow(output_title, WINDOW_AUTOSIZE);
	Mat kernel;
	kernel = getStructuringElement(MORPH_RECT, Size(11, 11),Point(-1,-1));
	morphologyEx(src2, dist1, MORPH_BLACKHAT, kernel);//MORPH_OPEN,MORPH_CLOSE,MORPH_TOPHAT,MORPH_BLACKHAT
	imshow("open_image", dist1);
	imwrite("hat.jpg",dist1);
	waitKey(0);

	return 0;

}