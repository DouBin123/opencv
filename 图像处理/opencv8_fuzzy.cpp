# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;




int main8(int argc, char** argv[])
{
	string filename = "E:\\opencv learning\\R-C.jpg";
	Mat src,dist,gdist,mdist,ddist;
	src = imread(filename);
	if (src.empty())
	{
		cout << "can not load image" << endl;
		return -1;
	}
	//均值模糊
	blur(src, dist, Size(9, 9), Point(-1, -1));//size():内核大小。Point():锚点-1,-1默认在中心
	//高斯模糊
	GaussianBlur(src, gdist, Size(9, 9), 11, 11);//后面为sigmax,sigmay
	//中值滤波
	medianBlur(src, mdist, 3);//ksize为卷积核大小，一般为奇数
	//双边模糊
	bilateralFilter(src, ddist,15,150,3 );//(输入图像，输出图像，领域直径，颜色空间sigma，坐标空间sigma)

	namedWindow("mywindow", WINDOW_AUTOSIZE);
	namedWindow("blurwindow", WINDOW_AUTOSIZE);
	imshow("my_image", src);
	imshow("blur_image", dist);
	imshow("gblur_image", gdist);
	imshow("mblur_image", mdist);
	imshow("bblur_image", ddist);


	waitKey(0);

	return 0;
}