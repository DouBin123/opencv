# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat imgGray, imgBlur, imgCanny, imgDil;

void getContours(Mat imgDil, Mat img)
{
	vector<vector<Point>>  contours;//contours������Ϊ��vector<vector<Point>> contours������һ��������
	//������һ��˫��������������ÿ��Ԫ�ر�����һ����������Point�㹹�ɵĵ�ļ��ϵ�������ÿһ��Point�㼯����һ��������
    //	�ж�������������contours���ж���Ԫ�ء�
	vector<Vec4i> hierarchy;//hierarchyҲ��һ��������������ÿ��Ԫ�ر�����һ������4��int���͵����顣
	//����hiararchy�ڵ�Ԫ�غ���������contours�ڵ�Ԫ����һһ��Ӧ�ģ�������������ͬ��
	//	hierarchy������ÿһ��Ԫ�ص�4��int�ͱ�������hierarchy[i][0] ~hierarchy[i][3]���ֱ��ʾ��
	//i�������ĺ�һ��������ǰһ������������������Ƕ������������š������ǰ����û�ж�Ӧ�ĺ�һ��
	//������ǰһ������������������Ƕ�����Ļ�����hierarchy[i][0] ~hierarchy[i][3]����Ӧλ������Ϊ
    //Ĭ��ֵ - 1��
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	/*
	int�͵�mode�����������ļ���ģʽ��
           ȡֵһ��CV_RETR_EXTERNALֻ�������Χ��������������Χ�����ڵ���Χ����������
           ȡֵ����CV_RETR_LIST   ������е�������������Χ����Χ���������Ǽ�⵽�������������ȼ���
                  ϵ���˴�֮�������û�еȼ���ϵ�������ζ���������ģʽ�²����ڸ���������Ƕ������
                  ����hierarchy����������Ԫ�صĵ�3����4���������ᱻ��Ϊ-1���������Ļὲ��
           ȡֵ����CV_RETR_CCOMP  ������е�����������������ֻ���������ȼ���ϵ����ΧΪ���㣬����Χ
                  �ڵ���Χ������������������������Ϣ������Χ�ڵ����������������ڶ���
           ȡֵ�ģ�CV_RETR_TREE�� �������������������������һ���ȼ����ṹ��������������ڲ���������
                   �����������Լ���������Ƕ������
�����������int�͵�method�����������Ľ��Ʒ���
           ȡֵһ��CV_CHAIN_APPROX_NONE ��������߽������������������㵽contours������
           ȡֵ����CV_CHAIN_APPROX_SIMPLE �����������Ĺյ���Ϣ�������������յ㴦�ĵ㱣����contours
                   �����ڣ��յ���յ�֮��ֱ�߶��ϵ���Ϣ�㲻�豣��
           ȡֵ�����ģ�CV_CHAIN_APPROX_TC89_L1��CV_CHAIN_APPROX_TC89_KCOSʹ��teh-Chinl chain ��
                   ���㷨
������������Pointƫ���������е�������Ϣ�����ԭʼͼ���Ӧ���ƫ�������൱����ÿһ���������������ϼ�
            �ϸ�ƫ����������Point�������Ǹ�ֵ��
	*/
	vector<vector<Point>> conPoly(contours.size());//��i�������ĵ�Ľ�ά
	vector<Rect>boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);//�����������
		cout <<"��" << i+1 <<"��ͼ�ε����Ϊ��" << area << "ƽ������" << endl;
	
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);//������������
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//�ƽ�����
			boundRect[i] = boundingRect(conPoly[i]);//�߽����
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			int objCor = (int)conPoly[i].size();
			if (objCor == 3) { objectType = "Tri"; }
			if (objCor == 4)
			{
				float aspRatio = boundRect[i].width / boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05)
				{
					objectType = "Square";
				}
				else
				objectType = "Rect";
			}
			if (objCor >4) { objectType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255), 2);
		}
	}

	
}

int mainc7()
{

	string path="E:\\opencv learning\\box.jpg";
	Mat img = imread(path);

	//Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dil", imgDil);*/


	waitKey(0);
	return 0;
}