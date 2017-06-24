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
	// applying custom designed filters in opencv
	Mat filt = (Mat_<char>(3,3)<< -1,-1,-1,-1,9,-1,-1,-1,-1);
	Mat avg = Mat::ones(30,30,CV_32FC1);
	avg = avg/30/30;

	Mat image2,image3 ;
	//Mat smooth(25,25,);
	// depth = number of channels
	filter2D(image,image2,image.depth(),avg);

	filter2D(image,image3,image.depth(),filt);

	
	// Create a window
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	// showing the image in the window "Display window"
	imshow("Display window", image2); // Show our image inside it.

	// Create a window
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	// showing the image in the window "Display window"
	imshow("Display window", image3); // Show our image inside it.

	

	imwrite("b.tif",image);

	// waitkey(0) wait for a keypress
	// waitkey(x) wait for a x milliseconds
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}