#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;



int main(int argc, char** argv)
{
    Mat img = imread("coins.png", 0);
    if(img.empty())
    {
      
        return -1;
    }

    Mat cimg;
    medianBlur(img, img, 5);
    cvtColor(img, cimg, COLOR_GRAY2BGR);

    vector<Vec3f> circles;
    HoughCircles(img, circles, CV_HOUGH_GRADIENT, 1, 10,
                 100, 30, 1, 30 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( cimg, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
        circle( cimg, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
    }

    imshow("detected circles", cimg);
    waitKey();

    return 0;
}
