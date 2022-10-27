//虚拟色彩空间
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;


///////////////////////project1//////////////////////
VideoCapture cap(0);

Mat img;
vector<vector<int>> newPoint;// { {x,y,color},{x,y,1/0}}

int hmin=0, smin=0, vmin=0, hmax=179, smax=255, vmax=255;

//hmin,smin,vmin,hmax,smax,vmax
vector<vector<int>> mycolor{    //存储需要检测的颜色的lower和upper,即色彩范围
	{124,48,117,143,170,255},	//purple
	{68,72,156,102,126,255}		//green
};
vector<Scalar> mycolorValues{	//需要绘制的颜色
	{255,0,255},				//purple
	{0,255,0}					//green
};



void findColor(Mat img)
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	for (int i = 0; i < mycolor.size(); i++)//多种颜色
	{
	Scalar lower(mycolor[i][0], mycolor[i][1], mycolor[i][2]);
	Scalar upper(mycolor[i][3], mycolor[i][4], mycolor[i][5]);
	Mat mask;
	inRange(imgHSV, lower, upper, mask);
	//imshow(to_string(i), mask);//显示每个颜色的选择窗口
	Point myPoints = getContours(mask);
		if (myPoints.x != 0 && myPoints.y != 0)
		{
			newPoint.push_back({ myPoints.x, myPoints.y, i });//vector
		}
	
	}

}
void DrawCanvas(vector<vector<int>> newPoint, vector<Scalar> mycolorValues)
{
	for (int i = 0; i < newPoint.size(); i++)
	{
		circle(img, Point(newPoint[i][0], newPoint[i][1]), 10, mycolorValues[newPoint[i][2]], FILLED);
	}
} 

Point getContours(Mat imgDil)
{
	vector<vector<Point>>  contours;
	vector<Vec4i> hierarchy;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());//对i个轮廓的点的降维
	vector<Rect>boundRect(contours.size());

	Point myPoints;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);//计算轮廓面积
		cout << area << endl;
		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);//计算轮廓长度
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//逼近曲线
			boundRect[i] = boundingRect(conPoly[i]);//边界矩形
			myPoints.x = boundRect[i].x + boundRect[i].width / 2;//中点
			myPoints.y = boundRect[i].y;

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			}
	}

	return myPoints;
}


int mainc8()
{
	//namedWindow("Trackbars", (640, 200));
	//createTrackbar("Hue Min", "Trackbars", &hmin, 175);
	//createTrackbar("Hue Max", "Trackbars", &hmax, 175);
	//createTrackbar("Sat Min", "Trackbars", &smin, 255);
	//createTrackbar("Sat Max", "Trackbars", &smax, 255);
	//createTrackbar("Val Min", "Trackbars", &vmin, 255);
	//createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (1)
	{
		cap.read(img);
		findColor(img);
		DrawCanvas(newPoint,mycolorValues);
		imshow("img", img);
		
		waitKey(1);
	}
	
	return 0;
}