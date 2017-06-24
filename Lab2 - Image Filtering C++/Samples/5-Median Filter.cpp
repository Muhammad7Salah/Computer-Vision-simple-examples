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
	// visualising average filter
	Mat image2[20];
	int size = 7;
	for (int i = 0; i < 20; i++)
	{
		GaussianBlur(image,image2[i],Size(size,size),3);
		size+=8;
		namedWindow("Display window"+i+1, WINDOW_AUTOSIZE); // Create a window for display.
	// showing the image in the window "Display window"
		
		//imwrite("b"+to_string(i)+".tif",image2[i]);
		imshow("Display window"+i+1, image2[i]); // Show our image inside it.
		//waitKey(0);
	}
	

	imwrite("b.tif",image);

	// waitkey(0) wait for a keypress
	// waitkey(x) wait for a x milliseconds
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}