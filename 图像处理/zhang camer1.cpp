// zhang's method.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "opencv2/core/core.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/calib3d/calib3d.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
#include <fstream>
#include <iomanip>

using namespace cv;
using namespace std;


void mainzb()
{
	ifstream fin("calibdata.txt"); /* �궨����ͼ���ļ���·�� */
	ofstream fout("caliberation_result.txt");  /* ����궨������ļ� */
											   //��ȡÿһ��ͼ�񣬴�����ȡ���ǵ㣬Ȼ��Խǵ���������ؾ�ȷ��   
	cout << "��ʼ��ȡ�ǵ㡭����������";

	int image_count = 0;  /* ͼ������ */
	Size image_size;  /* ͼ��ĳߴ� */
	Size board_size = Size(8,7);    /* �궨����ÿ�С��еĽǵ��� */
	vector<Point2f> image_points_buf;  /* ����ÿ��ͼ���ϼ�⵽�Ľǵ� */
	vector<vector<Point2f>> image_points_seq; /* �����⵽�����нǵ� */
	string filename;


	int count = 0;//���ڴ洢�ǵ������  
	while (getline(fin, filename))
	{
		image_count++;
		// ���ڹ۲�������  
		cout << "image_count = " << image_count << endl;
		//cout << "-->count = " << count<<endl;
		Mat imageInput = imread(filename);
		if (image_count == 1)  //�����һ��ͼƬʱ��ȡͼ������Ϣ  
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			
			cout << "image_size.width = " << image_size.width << endl;
			cout << "image_size.height = " << image_size.height << endl;
		}


		/* ��ȡ���̽ǵ� */
		if (0 == findChessboardCorners(imageInput, board_size, image_points_buf))//ֻ�Ǽ���Ƿ����������ֵΪ������
		//imageInput�����������ͼ
		//board_size������ͼÿ��ÿ�нǵ����
		//image_points_buf�����쵽�Ľǵ�

		{
			cout << "can not find chessboard corners!\n"; //�Ҳ����ǵ�  
			exit(1);
		}
		else
		{
			Mat view_gray;
			cvtColor(imageInput, view_gray, COLOR_RGB2GRAY);
			/* �����ؾ�ȷ�� */
			//��ȡ���Ľǵ����ֻ�����ؼ���Ĳ���������ʵ��Ҫ����Ҫ�Լ��Ľǵ��һ���Ż��������ر���Ϊ��С�ĵ�Ԫ������
			cornerSubPix(view_gray, image_points_buf, Size(5, 5), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
			//TermCriteria�������׼����������㷨��ֹ��������
			//�����ؾ�ȷ��������
			//Size(5,5)���������ڵĴ�С,Size(-1,-1)��ʾû������
			//���ĸ�����������ǵ�ĵ������̵���ֹ������������������ǵ㾫�ȵ���ϣ�������Ϊ��������30�ͽǵ㾫��0.1���ߵ����
			count += image_points_buf.size();
			image_points_seq.push_back(image_points_buf);//���������ؽǵ�
			drawChessboardCorners(view_gray, board_size, image_points_buf, true);
			//���ڻ��Ʊ��ɹ��궨�Ľǵ㣬����8λ�ҶȻ��߲�ɫͼ��
			//���ĸ������Ǳ�־λ������ָʾ����������ڽǵ��Ƿ�������̽�⵽
			//false��ʾ��δ��̽�⵽���ڽǵ㣬��ʱ��������ԲȦ��ǳ���⵽���ڽǵ�


			namedWindow("Camera Calibration", WINDOW_NORMAL);
			imshow("Camera Calibration", view_gray);//��ʾͼƬ
			waitKey(500);
		}
	}
	int total = image_points_seq.size();
	cout << "total = " << total << endl;
	int CornerNum = board_size.width * board_size.height;  //ÿ��ͼƬ���ܵĽǵ���  
	for (int ii = 0; ii < total; ii++)
	{
		if (0 == ii % CornerNum)// 54 ��ÿ��ͼƬ�Ľǵ���������ж������Ϊ����� ͼƬ�ţ����ڿ���̨�ۿ�   
		{
			int i = -1;
			i = ii / CornerNum;
			int j = i + 1;
			cout << "--> �� " << j << "ͼƬ������ --> : " << endl;
		}
		if (0 == ii % 3)  // ���ж���䣬ÿ���3�����У���ʽ����������ڿ���̨�鿴  
		{
			cout << endl;
		}
		else
		{
			cout.width(10);
		}
		//������еĽǵ�  
		cout << " -->" << image_points_seq[ii][0].x;
		cout << " -->" << image_points_seq[ii][0].y;
	}
	cout << "�ǵ���ȡ��ɣ�\n";

	//������������궨  
	cout << "��ʼ�궨������������";
	/*������ά��Ϣ*/
	Size square_size = Size(25, 25);  /* ʵ�ʲ����õ��ı궨����ÿ�����̸�Ĵ�С */
	vector<vector<Point3f>> object_points; /* ����궨���Ͻǵ����ά���� */
										   /*�������*/
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ������ڲ������� */
	vector<int> point_counts;  // ÿ��ͼ���нǵ������  
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* �������5������ϵ����k1,k2,p1,p2 */
	vector<Mat> tvecsMat;  /* ÿ��ͼ�����ת���� */
	vector<Mat> rvecsMat; /* ÿ��ͼ���ƽ������ */
						  /* ��ʼ���궨���Ͻǵ����ά���� */

	int i, j, t;
	for (t = 0; t < image_count; t++)//ѭ��������Ϊ���̱�����Ŀ������ÿ��ѭ����������
	{
		vector<Point3f> tempPointSet;
		for (i = 0; i < board_size.height; i++)
		{
			for (j = 0; j < board_size.width; j++)
			{
				Point3f realPoint;
				/* ����궨�������������ϵ��z=0��ƽ���� */
				//ʵ�ʵĸ��ӽǵ�����
				realPoint.x = i * square_size.width;
				realPoint.y = j * square_size.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
	}
	/* ��ʼ��ÿ��ͼ���еĽǵ��������ٶ�ÿ��ͼ���ж����Կ��������ı궨�� */
	for (i = 0; i < image_count; i++)
	{
		point_counts.push_back(board_size.width * board_size.height);
	}






	/* ��ʼ�궨 */
	calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);
	/*
	object_points:��������ϵ�еĵ�
	image_points_seq����Ӧ����������ϵ�ĵ�
	image_size��ͼ���С
	flag:�궨��ʹ�õ��㷨
	*/
	cout << "�궨��ɣ�\n";
	//�Ա궨�����������  
	cout << "��ʼ���۱궨���������������\n";
	double total_err = 0.0; /* ����ͼ���ƽ�������ܺ� */
	double err = 0.0; /* ÿ��ͼ���ƽ����� */
	vector<Point2f> image_points2; /* �������¼���õ���ͶӰ�� */

	cout << "\tÿ��ͼ��ı궨��\n";
	fout << "ÿ��ͼ��ı궨��\n";

	vector<vector<Point2f>> reproject_point;//��ͶӰ��

	for (i = 0; i < image_count; i++)
	{
		vector<Point3f> tempPointSet = object_points[i];
		/* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */
		projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points2);
		/* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/
		vector<Point2f> tempImagePoint = image_points_seq[i];
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);//1��56�е�2ͨ�����飬���ռ�⵽�Ľǵ�����
		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);//1��56�е�2ͨ�����飬������ͶӰ�������
		reproject_point.push_back(image_points2);

		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);//<Vec2f>2ͨ��
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);//���㣨m1-m2����2����
		total_err += err /= point_counts[i];
		std::cout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
		fout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
	}
	std::cout << "����ƽ����" << total_err / image_count << "����" << endl;
	fout << "����ƽ����" << total_err / image_count << "����" << endl << endl;

	std::cout << "������ɣ�" << endl;

	//���涨����      
	std::cout << "��ʼ���涨����������������" << endl;
	Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */
	fout << "����ڲ�������" << endl;
	fout << cameraMatrix << endl << endl;
	fout << "����ϵ����\n";
	fout << distCoeffs << endl << endl << endl;

	for (int i = 0; i < image_count; i++)
	{
		fout << "��" << i + 1 << "��ͼ�����ת������" << endl;
		fout << tvecsMat[i] << endl;
		/* ����ת����ת��Ϊ���Ӧ����ת���� */
		Rodrigues(tvecsMat[i], rotation_matrix);
		fout << "��" << i + 1 << "��ͼ�����ת����" << endl;
		fout << rotation_matrix << endl;
		fout << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
		fout << rvecsMat[i] << endl << endl;
	}
	std::cout << "��ɱ���" << endl;
	fout << endl;
	/************************************************************************
	��ʾ������
	*************************************************************************/
	Mat mapx = Mat(image_size, CV_32FC1);
	Mat mapy = Mat(image_size, CV_32FC1);
	Mat R = Mat::eye(3, 3, CV_32F);
	cout << "�������ͼ��" << endl;
	string imageFileName;
	std::stringstream StrStm;
	//��������ϵ����������ϵ��ת��
	Point2f p1,p2;
	p1 = reproject_point[0][0];
	p2 = reproject_point[0][1];
	float d1 = sqrt((p1.x-p2.x)* (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	float real_distance = 25;

	Point2f pt1 = p1;
	Point2f pt2;
	pt2 = Point2f(1946, 433);
	float d2 = sqrt((p1.x - pt2.x) * (p1.x - pt2.x) + (p1.y - pt2.y) * (p1.y - pt2.y));
	float s = 0;
	s = (d2 * real_distance) / d1;
	cout << "*************************************" << endl;
	cout << "ʵ�ʵľ���Ϊ��" << s << endl;
	cout << "���Ϊ��" << 150 - s << endl;
	cout << "*************************************" << endl;


	for (int i = 1; i <= image_count; i++)
	{
		cout << "Frame # " << i << "....." << endl;
		//�����޻��������ת��ӳ��
		initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix,
			image_size, CV_32FC1, mapx, mapy);//�����������ӳ��

		StrStm.clear();//�������
		imageFileName.clear();
		string filePath = "left";
		StrStm << setw(1) << i;
		StrStm >> imageFileName;
		filePath += imageFileName;
		filePath += ".jpg";
		//��ȡͼƬ·��
		Mat imageSource = imread(filePath);//��ȡͼ��
		if (0 == imageSource.data)
		{
			cout << "ͼƬ��ȡ����" << endl;
		}
		Mat newimage = imageSource.clone();//����ͼ��

		remap(imageSource, newimage, mapx, mapy, INTER_LANCZOS4);//����õ�ӳ��Ӧ�õ�ͼ����
															   //��initUndistortRectifyMap���ʹ�ã�Ϊ��������֮һ
		//ndistort(imageSource, newimage, cameraMatrix, distCoeffs);
															   //undistort(imageSource,newimage,cameraMatrix,distCoeffs);//����������
															   //���������newCameraMatrix=noArray()��Ĭ�ϸ�cameraMatrix����һ��,�ʿ�ʡ
		//�ڽ������ͼƬ�ϻ�����⵽�Ľǵ�
		int j;
		vector<Point2f> temp_point;
		temp_point= reproject_point[i-1];
		for (j = 0; j < temp_point.size(); j++)
		{

			circle(newimage, temp_point[j], 3, Scalar(0, 0, 255));
		}
		imageFileName += "_d.jpg";//������ͼƬ����
		imwrite(imageFileName, newimage);//����������ͼƬ
		imshow("Original Image", imageSource);
		waitKey(500);//��ͣ0.5s
		imshow("Undistorted Image", newimage);
		waitKey(500);

	}
	fin.close();
	fout.close();
	getchar();//�ȴ��������˳�
	return;
}