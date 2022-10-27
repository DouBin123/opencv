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
	//������ĻҶ�ͼ�񣬶�ֵͼ�񣬶�ֵͼ�����ֵ������Ӧ��������ֵ���ͣ����С��������
	
	//ˮƽ�ṹԪ��
	Mat hline = getStructuringElement(MORPH_RECT, Size(src3.cols / 16, 1), Point(-1, -1));
	//��ֱ�ṹԪ��
	Mat vline= getStructuringElement(MORPH_RECT, Size(1,src3.rows/16), Point(-1, -1));
	//���νṹԪ��
	Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	Mat med,med2;
	erode(binImg, med, hline);
	dilate(med, disth, hline);
	bitwise_not(disth, disth);//ǰ��ɫ�뱳��ɫ����
	blur(disth, disth, Size(3, 3));
	
	//����
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