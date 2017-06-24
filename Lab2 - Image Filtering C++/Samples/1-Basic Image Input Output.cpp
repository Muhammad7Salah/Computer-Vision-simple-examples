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