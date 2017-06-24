#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;


char* window_name = "Hit and Miss Demo Demo";



void hitmiss(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel)
{
  CV_Assert(src.type() == CV_8U && src.channels() == 1);

  cv::Mat k1 = (kernel == 1) / 255;
  cv::Mat k2 = (kernel == -1) / 255;

  cv::normalize(src, src, 0, 1, cv::NORM_MINMAX);

  cv::Mat e1, e2;
  cv::erode(src, e1, k1, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT, cv::Scalar(0));
  cv::erode(1-src, e2, k2, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT, cv::Scalar(0));
  dst = e1 & e2;
}

/** @function main */
int main( int argc, char** argv )
{
	cv::Mat a = (cv::Mat_<uchar>(8,8) << 0, 0, 0, 0, 0, 0, 0, 0,
										 0, 1, 1, 1, 0, 0, 0, 0, 
										 0, 1, 0, 1, 0, 0, 0, 1,
										 0, 1, 1, 1, 0, 1, 0, 0,
										 0, 0, 1, 0, 0, 0, 0, 0,
										 0, 0, 1, 0, 0, 1, 1, 0,
										 0, 1, 0, 1, 0, 0, 1, 0,
										 0, 1, 1, 1, 0, 0, 0, 0 );

	cv::Mat b = (cv::Mat_<char>(3,3) << 0, 1, 0, 1,-1, 1, 0, 1, 0 );
	Mat k;
	hitmiss(a, a, b);
 /// Create window
 namedWindow( window_name, CV_WINDOW_AUTOSIZE );
std::cout << a << std::endl;
for (int i = 0; i < a.rows; i++)
{
	for (int j = 0; j < a.cols; j++)
	{
		if(a.at<uchar>(i,j) == 1)
		{
			a.at<uchar>(i,j) = 255;
		}
	}

}
std::cout << a << std::endl;
 imshow(window_name,a);
 imwrite("a.jpg",a);
 
 waitKey(0);
 return 0;
 }
