//直方图反向投影
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

void  Hist_And_Backprojection(int,void*);
Mat src_h, dist_h,hsv,hue;

int bins = 10;

int main25()
{
	

	string filename = "E:\\opencv learning\\l.jpg";
	src_h = imread(filename);
	if (!src_h.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	resize(src_h, src_h, Size(500, 344));
	
	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src_h);

	cvtColor(src_h, hsv, COLOR_BGR2HSV);
	hue.create(hsv.size(), hsv.depth());
	int nchannels[] = { 0,0 };
	//从输入中拷贝某通道到输出中的特定的通道
	mixChannels(&hsv, 1, &hue, 1, nchannels, 1);

	createTrackbar("Histogram Bins", input, &bins, 180, Hist_And_Backprojection);


	waitKey(0);
	return 0;
}

void  Hist_And_Backprojection(int, void*)
{
	//计算直方图
	float range[] = { 0,180 };
	const float* histRange = { range };
	Mat h_hist;

	calcHist(&hue, 1, 0, Mat(), h_hist, 1, &bins, &histRange, true, false);
	normalize(h_hist, h_hist, 0, 255, NORM_MINMAX, -1, Mat());

	Mat backproj;
	calcBackProject(&hue, 1, 0, h_hist, backproj, &histRange, 1, true);
	imshow("Backproj", backproj);

	//绘制直方图

	int hist_h = 400;
	int hist_w = 400;
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	int bin_w = hist_w / bins;

	for (int i = 1; i < bins; i++)
	{
		rectangle(histImage,
			Point(bin_w * (i - 1), (hist_h -cvRound( h_hist.at<float>(i - 1) * (400 / 255)))), 
			//Point(bin_w * (i), (hist_h - cvRound(h_hist.at<float>(i) * (400 / 255)))),
			Point(i*bin_w,hist_h),
			Scalar(0, 0, 255), -1);
	}
	imshow("Histogram", histImage);
	return;

}