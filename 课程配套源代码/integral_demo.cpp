#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char** argv) {
	Mat src = imread("D:/vcprojects/images/test.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	Mat sumii = Mat::zeros(src.rows + 1, src.cols + 1, CV_32FC1);
	Mat sqsumii = Mat::zeros(src.rows + 1, src.cols + 1, CV_64FC1);
	integral(src, sumii, sqsumii);

	Mat iiResult;
	normalize(sumii, iiResult, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("Integral Image", iiResult);

	waitKey(0);
	return 0;
}