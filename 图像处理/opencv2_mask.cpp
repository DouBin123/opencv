# include <opencv2/opencv.hpp>
# include <iostream>
using namespace cv;
int main2()
{
	std::string filename = "E:\\opencv learning\\R-C.jpg";
	Mat src = imread(filename);
	if (src.empty())
	{
		std::cout << "can not load imag" << std::endl;
		return -1;
	}
	int cols = src.cols * src.channels();//rgbΪ��ͨ��
	int rows = src.rows;
	int offsetx=src.channels();
	Mat dst = Mat::zeros(src.size(), src.type());//��ͼ�������ͬ�ĳߴ�

	//��ȡͼ������ؽ�����Ĥ����,�ĸ��߽����������Ĥ����ʱ�ò���
	for (int row = 1; row < rows - 1; row++)
	{
		//��ȡ��ָ��
		const uchar* previous = src.ptr<uchar>(row-1);
		const uchar* current = src.ptr<uchar>(row);
		const uchar* next = src.ptr<uchar>(row+1);
		//��ͼ��ĵ�ǰ��ָ��
		uchar* output = dst.ptr<uchar>(row);
		//��һ�а���ͨ����������ʼ��Ϊͨ����*1
		for (int col = offsetx; col < cols - 1; col++)
		{
			output[col] =saturate_cast<char>( 5 * current[col] - previous[col] - current[col - offsetx] - current[col + offsetx] - next[col]);
			//saturate_cast<char>(n)ȷ��RGB��Χ��0-255֮��
			//��ά�����˼��

		}
	}
	double t = getTickCount();
	Mat dst1;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	
	filter2D(src, dst1, src.depth(), kernel);
	double time = (getTickCount()-t)/getTickFrequency();

	std::cout << "time consume: " << time<< std::endl;
	namedWindow("initialwindow", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", src);
	namedWindow("maskwindow", WINDOW_AUTOSIZE);
	imshow("��Ĥ�������ͼ��", dst);
	namedWindow("kernelwindow", WINDOW_AUTOSIZE);
	imshow("kernel���ͼ��", dst);

	waitKey(0);


	return 0;
}