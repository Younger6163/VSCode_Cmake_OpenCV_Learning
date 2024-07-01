#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

using namespace cv;
int main(int argc, char** argv)
{
	// 加载图像
	Mat testImage = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	CV_Assert(testImage.depth() == CV_8U);
	namedWindow("test_image", CV_WINDOW_AUTOSIZE);
	imshow("test_image", testImage);

	// 使用Filter2D函数
	Mat result;
	Mat kern = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(testImage, result, testImage.depth(), kern);

	// 显示结果
	namedWindow("result_image", CV_WINDOW_AUTOSIZE);
	imshow("result_image", result);
	waitKey(0);
	return 0;
}