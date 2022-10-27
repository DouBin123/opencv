//ͼ����������ϲ����뽵����
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main12()
{

	string filename = "E:\\opencv learning\\OpenCV_Logo.png";
	Mat src, distu,distd;

	src = imread(filename);
	if (!src.data)
	{
		cout << "can not load image" << endl;
		return -1;
	}

	namedWindow("input image", WINDOW_AUTOSIZE);
	imshow("input", src);
	//cvtColor(src, dist, COLOR_RGB2GRAY);

	//�ϲ���
	pyrUp(src, distu, Size(src.cols * 2, src.rows * 2));

	//������
	pyrDown(src, distd, Size(src.cols / 2, src.rows / 2));


	char output_window[] = "output_window";
	namedWindow(output_window, WINDOW_AUTOSIZE);
	imshow("output_image", distu);
	
	namedWindow("downselect_window", WINDOW_AUTOSIZE);
	imshow("downselect_image", distd);

	//DOG,��˹��ͬ
	Mat gray_g, g1, g2,dogImag;
	cvtColor(src, gray_g, COLOR_RGB2GRAY);
	GaussianBlur(gray_g, g1, Size(5,5), 0, 0);
	GaussianBlur(g1, g2, Size(5, 5), 0);//Size(3,3)Ϊ�˺���
	
	subtract(g1, g2, dogImag, Mat());//��˹��ͬ
	//��һ����ʾ
	normalize(dogImag, dogImag, 255, 0, NORM_MINMAX);//��ͼ��ɫ�ʿռ�Ͷ����0-255֮�䣬�������Сֵ��ʽ
	imshow("dog_imag", dogImag);


	waitKey(0);
	
	return 0;

}

