# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src1, dist;
int element_size = 3;
int max_size = 21;
void CallBack_Demo(int, void*);

int main9()
{
	string filename = "E:\\opencv learning\\R-C.jpg";

	src1 = imread(filename);
	if (!src1.data)
	{
		cout << "can not load image" << endl;
		return -1;
	}


	namedWindow("mywindow", WINDOW_AUTOSIZE);
	imshow("input_image", src1);

	namedWindow("output_window", WINDOW_AUTOSIZE);
	createTrackbar("Element Size:", "output_window", &element_size, max_size, CallBack_Demo);
	//���켣�������������ڵĴ���������Ҫ�ı�ı�����ַ�����ֵ����ʹ�õĺ�����ַ��
	CallBack_Demo(0, 0);
	//�ڲ�ͬ�Ĳ������и�ʴ�����Ͳ���
	waitKey(0);

	return 0;

}
void CallBack_Demo(int, void*)
{
	int s = element_size * 2 + 1;
	Mat structureElements = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));//�ṹԪSE
	dilate(src1, dist, structureElements, Point(-1, -1), 1);//����
	//������ͼ�����ͼ�񣬽ṹԪ��ê�㣬����������
	erode(src1, dist, structureElements);
	imshow("output_image", dist);
	return;

}