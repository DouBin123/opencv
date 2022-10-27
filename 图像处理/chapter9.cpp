//doument detection
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;


Mat img,imgCanny,imgGray,imgBlur,imgThre,imgDil,imgWarp,imgCrop;
vector<Point> initialPoints,docPoints;
float w = 420, h = 596;

Mat processing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25,75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	return imgDil;

}

vector<Point> getCountours(Mat imgThre)
{
	vector<vector<Point>> countours;
	vector<Vec4i> hierarchy;

	findContours(imgThre, countours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(countours.size());
	vector<Rect> boundRect(countours.size());

	vector<Point> biggest;
	int maxArea=0;
	for (int i = 0; i < countours.size(); i++)
	{
		int area = contourArea(countours[i]);//计算轮廓面积
		cout << area << endl;
		if (area > 1000)
		{
			float peri = arcLength(countours[i], true);//计算轮廓长度
			approxPolyDP(countours[i], conPoly[i], 0.02 * peri, true);//逼近曲线
			
			if (area > maxArea &&conPoly[i].size()==4)
			{
				//drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
				biggest = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };
				maxArea = area;
			}

			//drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return biggest;

}

void DrawPoints(vector<Point>points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(img, points[i], 10, color, FILLED);
		putText(img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 2, color, 2);
	}


}
vector<Point> reorder(vector<Point>points)
{
	vector<Point> newPoints;//{(23,45),(300,23),(34,145),(23,565)}
	vector<int> sumPoint,subPoint;
	for (int i = 0; i < points.size(); i++)
	{
		sumPoint.push_back (points[i].x + points[i].y);
		subPoint.push_back(points[i].x -points[i].y);
	}
	//迭代器找索引
	newPoints.push_back(points[min_element(sumPoint.begin(), sumPoint.end()) - sumPoint.begin()]);//0
	newPoints.push_back(points[max_element(subPoint.begin(), subPoint.end()) - subPoint.begin()]);//1
	newPoints.push_back(points[min_element(subPoint.begin(), subPoint.end()) - subPoint.begin()]);//1
	newPoints.push_back(points[max_element(sumPoint.begin(), sumPoint.end()) - sumPoint.begin()]);//3
	return newPoints;
}
Mat getWarp(Mat img1,vector<Point>points,float w,float h)
{
	Mat img2;
	Point2f  src[4] = { points[0],points[1], points[2], points[3] };
	Point2f dst[4] = { {0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img1, img2, matrix, Point(w, h));
	return img2;
}

int main()
{
	
	string path = "E:\\opencv learning\\paper.jpg";
	img = imread(path);

	resize(img, img, Size(), 0.5, 0.5);

	//prcessing
	imgThre=processing(img);
	
	//get contours--biggest
	initialPoints=getCountours(imgThre);
	//DrawPoints(initialPoints, Scalar(0, 0, 255));
	docPoints=reorder(initialPoints);
	//DrawPoints(docPoints, Scalar(0, 255,0));
	//warp the img
	imgWarp = getWarp(img, docPoints, w, h);
	//Crop
	int cropval=10;
	Rect roi(cropval, cropval, w - (2 * cropval), h - (2 * cropval));//需要裁剪的部分
	imgCrop = imgWarp(roi);

	imshow("img", img);
	imshow("imgThre", imgThre);
	imshow("imgwarp", imgWarp);
	imshow("imgCrop", imgCrop);

	



	waitKey(0);
	return 0;
}