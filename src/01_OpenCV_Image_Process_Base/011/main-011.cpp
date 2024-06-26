#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <iostream> 
using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	// medianBlur(src, dst, 3);
	bilateralFilter(src, dst, 15, 100, 5);
	namedWindow("BiBlur Filter Result", CV_WINDOW_AUTOSIZE);
	imshow("BiBlur Filter Result", dst);

	Mat resultImg;
	Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(dst, resultImg, -1, kernel, Point(-1, -1), 0);
	imshow("Final Result", resultImg);

	waitKey(0);
	return 0;

}