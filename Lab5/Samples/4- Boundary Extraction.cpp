#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;


char* window_name = "Hit and Miss Demo Demo";




/** @function main */
int main( int argc, char** argv )
{
	cv::Mat src = cv::imread("boundary.jpg", 0);
	if (!src.data)
		return 0;

	cv::Mat kernel = cv::Mat::ones(3, 3, CV_8U);
	cv::Mat eroded;
	cv::erode(src, eroded, kernel);
	cv::Mat dst = src - eroded;

	namedWindow("hassan");
	imshow("hassan",dst);
	waitKey(0);
	return 0;
 }
