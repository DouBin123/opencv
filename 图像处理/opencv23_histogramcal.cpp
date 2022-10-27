# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;


int main23()
{
	Mat src_m, dist_m, gray_src;
	string filename = "E:\\opencv learning\\l.jpg";
	src_m = imread(filename);
	if (!src_m.data)
	{
		cout << "cannot open the image" << endl;
		return -1;
	}

	char input[] = "inputwindow";
	char output[] = "outputwindow";

	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src_m);
	
	//直方图计算
	vector<Mat>bgr_planes;
	split(src_m, bgr_planes);

	int histsize = 256;//每个使用维度的数量
	float range[] = { 0,256 };
	const float* histranges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histsize, &histranges, true,false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histsize, &histranges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histsize, &histranges, true, false);

	//归一化
	int hist_h = 400;
	int hist_w = 512;
	int bin_w = cvRound((double)hist_w / histsize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

	//绘制直方图
	for (int i = 1; i < histsize; i++)
	{
	
		
		line(histImage, Point((i - 1) * bin_w, hist_h- cvRound(b_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);//cvRound:取整
		int x = 0;

		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);

		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar( 0, 0,255), 2, LINE_AA);
	}
	
	imshow(output, histImage);
	waitKey(0);
	return 0;
}