#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;



/** @function main */
int main( int argc, char** argv )
{
cv::Mat src = cv::imread("coins.png", CV_LOAD_IMAGE_GRAYSCALE);
threshold(src,src,0,255,THRESH_OTSU | THRESH_BINARY);
if (src.empty())
    return -1;

//cv::normalize(src, src, 0, 1, cv::NORM_MINMAX);

cv::Mat dst;
dst = cv::Mat::zeros(src.size(), CV_8U);
dst.at<uchar>(75,75) = 1;

cv::Mat prev;
cv::Mat kernel = (cv::Mat_<uchar>(3,3) << 0, 1, 0, 1, 1, 1, 0, 1, 0);

do {
    dst.copyTo(prev);
    cv::dilate(dst, dst, kernel);
    dst &= (1 - src);
} 
while (cv::countNonZero(dst - prev) > 0);

cv::normalize(src, src, 0, 255, cv::NORM_MINMAX);
cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX);
dst = 255-dst;
//// binary image contains white connected objects
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  // it modifies the image so take care
  Mat x = dst.clone();
  findContours( x, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
cout<<contours.size();


	cv::imshow("filled image", dst);
	//cv::imshow("Final image", newImage);
	//cv::imwrite("final.jpg", newImage);
	cv::waitKey(0);

	return 0;

 }
