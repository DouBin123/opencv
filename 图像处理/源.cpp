// Camera2.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include<iostream>
#include <opencv2\opencv.hpp>  
using namespace cv;

//-----------------------------------��main( )������--------------------------------------------
//		����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
//-------------------------------------------------------------------------------------------------
int main00()
{
	//��1��������ͷ������Ƶ
	VideoCapture capture(1);
	if (capture.isOpened())
	{
		std::cout << "������ɹ���" << std::endl;
		capture.set(CAP_PROP_FRAME_WIDTH, 1280);
		capture.set(CAP_PROP_FRAME_HEIGHT, 1280);
		capture.set(CAP_PROP_FPS, 20);


	}
		
	else
		std::cout << "�����ʧ�ܣ�" << std::endl;


	//0Ĭ�ϡ�����������ñʼǱ����;1 --��USB���ޣ���USB�� ���磬���ñʼǱ���-1ѡ�����������
	//��2��ѭ����ʾÿһ֡
	while (1)
	{
		Mat frame;  //����һ��Mat���������ڴ洢ÿһ֡��ͼ��
		capture >> frame;  //��ȡ��ǰ֡
		int a = 10;
		if (frame.empty())
			continue;
		imshow("��ȡ��Ƶ", frame);  //��ʾ��ǰ֡
		std::cout << frame << std::endl;
		waitKey(30);  //��ʱ30ms
	}
	return 0;

}



