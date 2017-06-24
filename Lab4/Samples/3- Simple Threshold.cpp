#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
/** @function main */
#define x
int main( int argc, char** argv )
{
	
	Mat src;
	Mat dst;
  /// Load an image
  src = imread( "ada2.jpg" );

  if( !src.data )
  { return -1; }
  cvtColor( src, src, CV_BGR2GRAY );

#if defined x
  dst = src>150;
  imshow("threshold",dst);
  waitKey();
#else
  threshold(src, dst, 150, 255, CV_THRESH_BINARY);
  imshow("threshold",dst);
  waitKey();
#endif
  return 0;
  }