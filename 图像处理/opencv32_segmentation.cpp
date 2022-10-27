//图像分割
# include <opencv2/opencv.hpp>   

# include <iostream>

using namespace std;
using namespace cv;

int main32()

{
	Mat src_s, bin_s;

	string filename = "C:\\my_data\\programming\\opencv learning\\puke.jpg";
	const char* input_win = "input-win";
	char output_win[] = "output_win";
	src_s = imread(filename);

	if (!src_s.data) {
		cout << "can not load the image!";
		return -1;
	}

	namedWindow(input_win, WINDOW_AUTOSIZE);
	namedWindow(output_win, WINDOW_AUTOSIZE);
	imshow(input_win, src_s);
	
//1、change background

	for (int row = 0; row < src_s.rows; row++)
	{
		for (int col = 0; col < src_s.cols; col++)
		{

			if (abs(src_s.at<Vec3b>(row, col)[0]-216<15)&& abs(src_s.at<Vec3b>(row, col)[1] - 216 < 15)&& abs(src_s.at<Vec3b>(row, col)[2] - 216 < 13))
			{
				src_s.at<Vec3b>(row, col)[0] = 0;
				src_s.at<Vec3b>(row, col)[1] = 0;
				src_s.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	
//2、sharp
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	Mat laplace_img;
	Mat sharpen_img;
	filter2D(src_s, laplace_img, CV_32F, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
	src_s.convertTo(sharpen_img,CV_32F);//same kind image
	Mat result = sharpen_img - laplace_img;

	result.convertTo(result, CV_8UC3);
	laplace_img.convertTo(laplace_img, CV_8UC3);
	//imshow("SHARPEN", result);
	//imshow("laplace", laplace_img);
	     src_s = result;//copy back

//3、binary transform
	cvtColor(src_s, result, COLOR_BGR2GRAY);
	threshold(result, bin_s, 40, 255, THRESH_BINARY | THRESH_OTSU);//自动求阈值
	//imshow("binary", bin_s);

//4、distance transform
	Mat dis_s;
	distanceTransform(bin_s, dis_s, DIST_L1, 3, 5);
	normalize(dis_s, dis_s, 0, 1, NORM_MINMAX);
	//imshow("ditance", dis_s);

//5、binary agin
	Mat bin_d;
	threshold(dis_s, bin_d, 0.4,1, THRESH_BINARY);
	//imshow("binary-after-distance", bin_d);

//************************有多个重叠区域时需要腐蚀操作****************************
//6、erode      
	Mat erode_s;
	Mat kernelr = Mat::ones(3, 3, CV_8UC1);
	erode(bin_d, erode_s, kernelr, Point(-1, -1));
	//imshow("erode", erode_s);

//7、marker
	Mat dist_8u;
	erode_s.convertTo(dist_8u, CV_8U);
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;

	findContours(dist_8u, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	//create markers
	Mat marks = Mat::zeros(src_s.size(), CV_32SC1);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(marks, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1),-1);//为了后面不同轮廓的颜色下标查找
	}
	circle(marks, Point(5, 5), 3, Scalar(255, 255, 255), -1);
	//imshow("marker", marks);


//8、perform watershed transform
	
	watershed(src_s, marks);
	Mat mark = Mat::zeros(marks.size(), CV_8UC1);
	marks.convertTo(mark, CV_8UC1);
	bitwise_not(mark, mark, Mat());
	imshow("watershed", mark);

//9、generate random color
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++)//根据轮廓随机颜色
	{
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

//10、filled with color and display final result
	Mat dst = Mat::zeros(marks.size(), CV_8UC3);
	for (int row = 0; row < dst.rows; row++)
	{
		for (int col = 0; col < dst.cols; col++)
		{
			int index = marks.at<int>(row, col);
			if (index > 0 && index <= static_cast<int>(contours.size()))
			{
				dst.at<Vec3b>(row, col) = colors[index - 1];
			}
		}
	}


	//cout << src_s.at<Vec3b>(10, 10) << endl;
	imshow("blackbackground", src_s);
	imshow("finally result", dst);
	waitKey(0);
	return 0;


}