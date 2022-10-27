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
	//��ֵģ��
	blur(src, dist, Size(9, 9), Point(-1, -1));//size():�ں˴�С��Point():ê��-1,-1Ĭ��������
	//��˹ģ��
	GaussianBlur(src, gdist, Size(9, 9), 11, 11);//����Ϊsigmax,sigmay
	//��ֵ�˲�
	medianBlur(src, mdist, 3);//ksizeΪ����˴�С��һ��Ϊ����
	//˫��ģ��
	bilateralFilter(src, ddist,15,150,3 );//(����ͼ�����ͼ������ֱ������ɫ�ռ�sigma������ռ�sigma)

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