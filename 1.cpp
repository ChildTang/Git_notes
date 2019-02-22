#include <imgproc\imgproc.hpp>
#include <highgui\highgui.hpp>
#include <photo\photo.hpp>
 
using namespace cv;
 
//全区域阈值处理+Mask膨胀处理
int main()
{
	Mat imageSource = imread("1.jpg");
	if (!imageSource.data)
	{
		return -1;
	}
	imshow("原图", imageSource);
	Mat imageGray;
	//转换为灰度图
	cvtColor(imageSource, imageGray, CV_RGB2GRAY, 0);
	Mat imageMask = Mat(imageSource.size(), CV_8UC1, Scalar::all(0));
 
	//通过阈值处理生成Mask
	threshold(imageGray, imageMask, 240, 255, CV_THRESH_BINARY);
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//对Mask膨胀处理，增加Mask面积
	dilate(imageMask, imageMask, Kernel);
 
	//图像修复
	inpaint(imageSource, imageMask, imageSource, 5, INPAINT_TELEA);
	imshow("Mask", imageMask);
	imshow("修复后", imageSource);
	waitKey();
}

