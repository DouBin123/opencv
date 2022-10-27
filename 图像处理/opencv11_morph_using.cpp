# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;


int main11()
{
	string filename = "E:\\opencv learning\\LINE.png";
	Mat src3, dist2,disth,distv,dista;
	src3 = imread(filename);
	if (!src3.data)
	{
		cout << "can not load image" << endl;
		return -1;
	}
	cvtColor(src3, dist2, COLOR_RGB2GRAY);
	Mat binImg;
	namedWindow("outputwindow", WINDOW_AUTOSIZE);
	adaptiveThreshold(~dist2, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	//（输入的灰度图像，二值图像，二值图像最大值，自适应方法，阈值类型，块大小，常量）
	
	//水平结构元素
	Mat hline = getStructuringElement(MORPH_RECT, Size(src3.cols / 16, 1), Point(-1, -1));
	//垂直结构元素
	Mat vline= getStructuringElement(MORPH_RECT, Size(1,src3.rows/16), Point(-1, -1));
	//矩形结构元素
	Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	Mat med,med2;
	erode(binImg, med, hline);
	dilate(med, disth, hline);
	bitwise_not(disth, disth);//前景色与背景色互换
	blur(disth, disth, Size(3, 3));
	
	//矩形
	morphologyEx(binImg, dista, MORPH_OPEN, kernel);


	morphologyEx(binImg, distv, MORPH_OPEN, vline);
	bitwise_not(distv, distv);
	blur(distv, distv, Size(3, 3));

	imshow("gray_image", dist2);
	imshow("binImg", binImg);
	namedWindow("output_window", WINDOW_AUTOSIZE);
	imshow("hline", disth);
	imshow("vline", distv);
	imshow("kernel", dista);

	waitKey(0);
	return 0;
}