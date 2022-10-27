//sobel����
# include<opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

int main16()
{
	Mat src, dist;
	string filename = "E:\\opencv learning\\OpenCV_Logo.png";
	src = imread(filename);
	if (!src.data)
	{
		cout << "cannot open the image"<<endl;
		return -1;
	}
	
	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src);

	GaussianBlur(src, dist, Size(3, 3), 0, 0);//��˹ģ��

	Mat gray_src;
	cvtColor(src, gray_src, COLOR_RGB2GRAY);

	Mat gradx, grady;
	Scharr(gray_src, gradx, CV_16S, 1, 0);//scharr�˲�����Ҫ�����sobel��������ģ�
	//�ֱ����x�����y�����ͼ����
	Scharr(gray_src, grady, CV_16S, 0, 1);
	//��ȻSobel���ӿ�����Ч����ȡͼ���Ե�����Ƕ�ͼ���н����ı�Ե��ȡЧ���ϲ
	//���Ϊ���ܹ���Ч����ȡ�������ı�Ե����Ҫ������ֵ��Ĳ�������������Scharr���ӡ�
	//Scharr�����Ƕ�Sobel���Ӳ����Ե���ǿ���������֮����ڼ��ͼ���Ե��ԭ���ʹ�÷�ʽ����ͬ��

	//Sobel(gray_src, gradx, -1, 1, 0, 3);//�õ���ͼ���Ǻ�����
	//Sobel(gray_src, gradx, CV_16S, 1, 0, 3);//��ֹ�������ΪCV_16S
	//Sobel(gray_src, grady, CV_16S, 0, 1, 3);

	//���ݴ�����ֹ��ֵ

	convertScaleAbs(gradx, gradx);//����ֵת��
	convertScaleAbs(grady, grady);
	//��ʾ���

	imshow(output, gray_src);
	imshow("xgrad", gradx);
	imshow("ygrad", grady);

	//���
	//Mat fdist;
	//addWeighted(gradx, 0.5, grady, 0.5, 0, fdist);
	Mat fdist = Mat(gradx.size(), gradx.type());
	cout << "gradxtype:" << gradx.type() << endl;
	int width = gradx.cols;
	int height = grady.rows;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int xg = gradx.at<uchar>(row, col);
			int yg = grady.at<uchar>(row, col);
			fdist.at<char>(row, col) =saturate_cast<uchar> (xg + yg);
		}
	}

	imshow(output, fdist);
	waitKey(0);
	return 0;
}