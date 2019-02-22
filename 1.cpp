#include <imgproc\imgproc.hpp>
#include <highgui\highgui.hpp>
#include <photo\photo.hpp>
 
using namespace cv;
 
//ȫ������ֵ����+Mask���ʹ���
int main()
{
	Mat imageSource = imread("1.jpg");
	if (!imageSource.data)
	{
		return -1;
	}
	imshow("ԭͼ", imageSource);
	Mat imageGray;
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(imageSource, imageGray, CV_RGB2GRAY, 0);
	Mat imageMask = Mat(imageSource.size(), CV_8UC1, Scalar::all(0));
 
	//ͨ����ֵ��������Mask
	threshold(imageGray, imageMask, 240, 255, CV_THRESH_BINARY);
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//��Mask���ʹ�������Mask���
	dilate(imageMask, imageMask, Kernel);
 
	//ͼ���޸�
	inpaint(imageSource, imageMask, imageSource, 5, INPAINT_TELEA);
	imshow("Mask", imageMask);
	imshow("�޸���", imageSource);
	waitKey();
}

