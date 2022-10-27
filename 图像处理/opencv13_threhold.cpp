//基本阈值操作
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

	Mat srca, dista,hdist;
	void Threhold_demo(int, void*);
	int threhlod_value = 127, threhold_max = 255;
	int type_value = 2;
	int type_max = 4;

int main13()
{


	char filename[]="E:\\opencv learning\\OpenCV_Logo.png";
	srca = imread(filename);
	if (!srca.data)
	{
		cout << "can't open the image";
		return -1;
	}


	namedWindow("input_window", WINDOW_AUTOSIZE);
	namedWindow("output_window", WINDOW_AUTOSIZE);
	imshow("input_imag", srca);
	
	createTrackbar("Threhold Value", "output_window", &threhlod_value, threhold_max, Threhold_demo);
	createTrackbar("Type Value", "output_window", &type_value, type_max, Threhold_demo);

	//Threhold_demo(0,0);

	
	waitKey(0);
	return 0;
}
void Threhold_demo(int,void*)
{
	cvtColor(srca, dista, COLOR_RGB2GRAY);
	/*cout << THRESH_BINARY;//0
	cout << THRESH_BINARY_INV;//1
	cout << THRESH_TRUNC;//2
	cout << THRESH_TOZERO;//3
	cout << THRESH_TOZERO_INV;//4*/

	threshold(dista, hdist, threhlod_value, threhold_max, type_value);//阈值处理
	//自动求阈值
	//threshold(dista, hdist, 0, 255, THRESH_OTSU | type_value);//阈值处理
	//threshold(dista, hdist, 0, 255, THRESH_TRIANGLE |type_value);//阈值处理

	imshow("ouput_window", hdist);
}