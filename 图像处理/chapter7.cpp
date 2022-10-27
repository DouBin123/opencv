# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat imgGray, imgBlur, imgCanny, imgDil;

void getContours(Mat imgDil, Mat img)
{
	vector<vector<Point>>  contours;//contours，定义为“vector<vector<Point>> contours”，是一个向量，
	//并且是一个双重向量，向量内每个元素保存了一组由连续的Point点构成的点的集合的向量，每一组Point点集就是一个轮廓。
    //	有多少轮廓，向量contours就有多少元素。
	vector<Vec4i> hierarchy;//hierarchy也是一个向量，向量内每个元素保存了一个包含4个int整型的数组。
	//向量hiararchy内的元素和轮廓向量contours内的元素是一一对应的，向量的容量相同。
	//	hierarchy向量内每一个元素的4个int型变量——hierarchy[i][0] ~hierarchy[i][3]，分别表示第
	//i个轮廓的后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号。如果当前轮廓没有对应的后一个
	//轮廓、前一个轮廓、父轮廓或内嵌轮廓的话，则hierarchy[i][0] ~hierarchy[i][3]的相应位被设置为
    //默认值 - 1。
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	/*
	int型的mode，定义轮廓的检索模式：
           取值一：CV_RETR_EXTERNAL只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略
           取值二：CV_RETR_LIST   检测所有的轮廓，包括内围、外围轮廓，但是检测到的轮廓不建立等级关
                  系，彼此之间独立，没有等级关系，这就意味着这个检索模式下不存在父轮廓或内嵌轮廓，
                  所以hierarchy向量内所有元素的第3、第4个分量都会被置为-1，具体下文会讲到
           取值三：CV_RETR_CCOMP  检测所有的轮廓，但所有轮廓只建立两个等级关系，外围为顶层，若外围
                  内的内围轮廓还包含了其他的轮廓信息，则内围内的所有轮廓均归属于顶层
           取值四：CV_RETR_TREE， 检测所有轮廓，所有轮廓建立一个等级树结构。外层轮廓包含内层轮廓，内
                   层轮廓还可以继续包含内嵌轮廓。
第五个参数：int型的method，定义轮廓的近似方法
           取值一：CV_CHAIN_APPROX_NONE 保存物体边界上所有连续的轮廓点到contours向量内
           取值二：CV_CHAIN_APPROX_SIMPLE 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours
                   向量内，拐点与拐点之间直线段上的信息点不予保留
           取值三和四：CV_CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使用teh-Chinl chain 近
                   似算法
第六个参数：Point偏移量，所有的轮廓信息相对于原始图像对应点的偏移量，相当于在每一个检测出的轮廓点上加
            上该偏移量，并且Point还可以是负值！
	*/
	vector<vector<Point>> conPoly(contours.size());//对i个轮廓的点的降维
	vector<Rect>boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);//计算轮廓面积
		cout <<"第" << i+1 <<"个图形的面积为：" << area << "平方像素" << endl;
	
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);//计算轮廓长度
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//逼近曲线
			boundRect[i] = boundingRect(conPoly[i]);//边界矩形
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