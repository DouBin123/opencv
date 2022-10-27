# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat src_m, dist_m, map_x,map_y;
int index = 1;
void update_map();

int main21()
{
	
	
	string filename = "E:\\opencv learning\\OpenCV_Logo.png";
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

	//像素重映射
	map_x.create(src_m.size(), CV_32FC1);
	map_y.create(src_m.size(), CV_32FC1);
	
	int c = 0;
	while (1)
	{
	    c = waitKey(500);
		if ((char)c == 27)
		{
			break;
		}
		index = c % 4;
		update_map();
		remap(src_m, dist_m, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 255, 255));
		imshow(output, dist_m);
	}
		
		waitKey(0);
		return 0;
}
void update_map()
{
	for (int row = 0; row < src_m.rows; row++)
	{
		for (int col = 0; col < src_m.cols; col++)
		{
			switch (index)
			{
			case 0:
				if (col > (src_m.cols * 0.25) && col<=(src_m.cols * 0.75) && row>(src_m.rows * 0.25) && row <=(src_m.rows * 0.75))
				{
					map_x.at<float>(row, col) = 2 * (col - (src_m.cols * 0.25));//线性插值
					map_y.at<float>(row, col) = 2 * (row - (src_m.rows * 0.25));

				}
				else
				{
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
				break;
			case 1:
				map_x.at<float>(row, col) =( src_m.cols - col-1);
				map_y.at<float>(row, col) = row;
				break;
			case 2:
				map_x.at<float>(row, col) = col ;
				map_y.at<float>(row, col) = (src_m.rows-row - 1);
				break;
			case 3:
				map_x.at<float>(row, col) = src_m.cols - col - 1;
				map_y.at<float>(row, col) = src_m.rows - row - 1;
				break;

			}
		}
	}

}