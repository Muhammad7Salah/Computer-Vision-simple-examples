#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;


void Shift(Mat & src)
{
	src = src(Rect(0, 0, src.cols & -2, src.rows & -2));

    int cx = src.cols/2;
    int cy = src.rows/2;

    // rearrange the quadrants of Fourier image
    // so that the origin is at the image center
    Mat tmp;
    Mat q0(src, Rect(0, 0, cx, cy));
    Mat q1(src, Rect(cx, 0, cx, cy));
    Mat q2(src, Rect(0, cy, cx, cy));
    Mat q3(src, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);	
    tmp.copyTo(q2);
}


Mat GenerateILPF(int cutoff, int width,int height)
{
	if(cutoff > width)
		cutoff = width/4;
	if(cutoff > height)
		cutoff = width/4;
	Mat temp(height,width,CV_32F);
	int cx = width/2;
	int cy = height/2;
	for( int i = 0; i < temp.rows; ++i)
	{
		for(int u=0;u<temp.cols;++u)
		{
			double dist = sqrt(pow(abs(u-cx),2) + pow(abs(i-cy),2));
			if(dist<cutoff)
			{
				temp.at<float>(i,u)=1;
				temp.at<float>(i,u)=1;
			}
			else
			{
				temp.at<float>(i,u)=0;
				temp.at<float>(i,u)=0;
			}
		}
	}
	return temp;
	
}


   //// generate gaussian high pass filter

double pixelDistance(double u, double v)
{
    return cv::sqrt(u*u + v*v);
}

double gaussianCoeff(double u, double v, double d0)
{
    double d = pixelDistance(u, v);
    return 1.0 - cv::exp((-d*d) / (2*d0*d0));
	//return  cv::exp((-d*d) / (2*d0*d0));
}

cv::Mat createGaussianHighPassFilter(cv::Size size, double cutoffInPixels)
{
    Mat ghpf(size, CV_32F);

    cv::Point center(size.width / 2, size.height / 2);

    for(int u = 0; u < ghpf.rows; u++)
    {
        for(int v = 0; v < ghpf.cols; v++)
        {
            ghpf.at<float>(u, v) = gaussianCoeff(u - center.y, v - center.x, cutoffInPixels);
        }
    }

    return ghpf;
}

void ApplyFilter(const Mat & src, const Mat & kernel,Mat & dst)
{
	//dst = Mat::zeros(src.size(),src.type());
	float k,c;
	for (int i = 0; i < src.rows; i++)
	{

		for (int j = 0; j < src.cols; j++)
		{
			dst.at<float>(i,j) = src.at<float>(i,j)* kernel.at<float>(i,j);
		}

	}
}

int main(int argc, const char ** argv)
{

		Mat img;
		img=imread("C:/Users/Yomna/Desktop/Computer Vision - Dr. Mahmoud Khalil/pout.jpg",CV_LOAD_IMAGE_GRAYSCALE);

		int M = getOptimalDFTSize( img.rows );
		int N = getOptimalDFTSize( img.cols );
		Mat padded;
		copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));

		Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
		Mat complexImg;
		merge(planes, 2, complexImg);

		dft(complexImg, complexImg,cv::DFT_SCALE|cv::DFT_COMPLEX_OUTPUT);

		split(complexImg, planes);

		Mat filter1;
		planes[0].copyTo(filter1);
		Mat filter2;
		planes[1].copyTo(filter2);

		Shift(filter1);
		Shift(filter2);

		//Mat kernel = GenerateILPF(20,filter1.cols,filter1.rows);
		Mat kernel  = createGaussianHighPassFilter(Size(128, 128), 16.0);
		ApplyFilter(filter1,kernel,filter1);
		ApplyFilter(filter2,kernel,filter2);

		Shift(filter1);
		Shift(filter2);
		

		Mat inverse[] = {filter1,filter2};
		Mat filterspec;
		merge(inverse, 2, filterspec);
		
		cv::Mat inverseTransform;
		cv::dft(filterspec, inverseTransform,cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
		cv::Mat finalImage;
		inverseTransform.convertTo(finalImage, CV_8U);
		imshow("Ideal Low Pass Filter",kernel);
		imshow("Filtered Image",finalImage);
		waitKey(0);
    return 0;
}
