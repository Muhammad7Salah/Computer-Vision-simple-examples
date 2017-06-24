#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main( int argc, char** argv )
{
	Mat src;
	Mat dst;
	/// Load an image
	src = imread( "ada2.jpg" );

	if( !src.data )
	{ return -1; }
	cvtColor( src, src, CV_BGR2GRAY );

	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,11,2);
	imshow("threshold",dst);
	waitKey();
	return 0;
  }