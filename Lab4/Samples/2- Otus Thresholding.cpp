#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables


/** @function main */
int main( int argc, char** argv )
{
	
	Mat src;
	Mat dst;
  /// Load an image
  src = imread( "ada2.jpg" );

  if( !src.data )
  { return -1; }
  cvtColor( src, src, CV_BGR2GRAY );
  threshold(src,dst,0,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
  namedWindow("threshold");
  imshow("threshold",dst);
  waitKey();

  return 0;
  }