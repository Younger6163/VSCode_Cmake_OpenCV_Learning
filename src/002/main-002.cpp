#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	// src = imread("D:/vcprojects/images/test.png");
	src = imread(argv[1], IMREAD_COLOR);
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);
	
	int cols = (src.cols-1) * src.channels();
	int offsetx = src.channels();
	int rows = src.rows;

	// dst = Mat::zeros(src.size(), src.type());
	// for (int row = 1; row < (rows - 1); row++) {
	// 	const uchar* previous = src.ptr<uchar>(row - 1);
	// 	const uchar* current = src.ptr<uchar>(row);
	// 	const uchar* next = src.ptr<uchar>(row + 1);
	// 	uchar* output = dst.ptr<uchar>(row);
	// 	for (int col = offsetx; col < cols; col++) {
	// 		// output[col] = (5 * current[col] - (current[col- offsetx] + current[col+ offsetx] + previous[col] + next[col]));
	// 		output[col] = saturate_cast<uchar>(5 * current[col] - (current[col- offsetx] + current[col+ offsetx] + previous[col] + next[col]));
	// 	}
	// }
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	double t = getTickCount();
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	// Mat M(3, 3, CV_8UC3, Scalar(0, 0, 255));
	Mat M2;
	M2.create(4, 3, CV_8UC2);
	M2 = Scalar(0, 1);
	std::cout << M2 << std::endl;
	filter2D(src, dst, src.depth(), kernel);
	double timeconsume = (getTickCount() - t) / getTickFrequency();
	printf("time consume %.2f\n", timeconsume);

	namedWindow("contrast image demo", CV_WINDOW_AUTOSIZE);
	imshow("contrast image demo", dst);

	waitKey(0);
	return 0;
}