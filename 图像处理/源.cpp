// Camera2.cpp : 定义控制台应用程序的入口点。
//
#include<iostream>
#include <opencv2\opencv.hpp>  
using namespace cv;

//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-------------------------------------------------------------------------------------------------
int main00()
{
	//【1】从摄像头读入视频
	VideoCapture capture(1);
	if (capture.isOpened())
	{
		std::cout << "打开相机成功！" << std::endl;
		capture.set(CAP_PROP_FRAME_WIDTH, 1280);
		capture.set(CAP_PROP_FRAME_HEIGHT, 1280);
		capture.set(CAP_PROP_FPS, 20);


	}
		
	else
		std::cout << "打开相机失败！" << std::endl;


	//0默认—摄像机，若用笔记本相机;1 --是USB有限，无USB就 网络，若用笔记本；-1选择多个相机界面
	//【2】循环显示每一帧
	while (1)
	{
		Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
		capture >> frame;  //读取当前帧
		int a = 10;
		if (frame.empty())
			continue;
		imshow("读取视频", frame);  //显示当前帧
		std::cout << frame << std::endl;
		waitKey(30);  //延时30ms
	}
	return 0;

}



