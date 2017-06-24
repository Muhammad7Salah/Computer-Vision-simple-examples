#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// code for reading command line arguments
	//if (argc != 2)
	//{
	//	cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
	//	return -1;
	//}

	Mat image;

	// function to read image
	image = imread("a.tif", IMREAD_GRAYSCALE); // Read the file

	// checking if data pointer isn't null --> image isn't read correctly
	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	
	// drawing a circle, there're also rectangle, and line functions to draw rectangles and lines
	// negative thickness means to fill the shape
	circle(image,Point(100,100),20,Scalar(20),1);
	// 
	putText(image,"Hello World",Point(100,200),FONT_HERSHEY_DUPLEX,3,Scalar(1));

	// drawing ellipse
	RotatedRect rotrect(Point(100,300),Size(90,200),20);
	ellipse(image,rotrect,Scalar(0),1);

	// Create a window
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	// showing the image in the window "Display window"
	imshow("Display window", image); // Show our image inside it.

	imwrite("b.tif",image);

	// waitkey(0) wait for a keypress
	// waitkey(x) wait for a x milliseconds
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}