#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	int ksize = 0;

	// src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "Custom Blur Filter Result";
	namedWindow(INPUT_WIN, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);

	imshow(INPUT_WIN, src);

	// // Robert X 方向
	// Mat kernel_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
	// filter2D(src, dst, -1, kernel_x, Point(-1, -1), 0.0);

	// // Robert Y 方向
	// Mat yimg;
	// Mat kernel_y = (Mat_<int>(2, 2) << 0, -1, 1, 0);
	// filter2D(src, yimg, -1, kernel_y, Point(-1, -1), 0.0);
	
	// // Sobel X 方向
	// Mat kernel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2,0,2,-1,0,1);
	// filter2D(src, dst, -1, kernel_x, Point(-1, -1), 0.0);

	// // Sobel Y 方向
	// Mat yimg;
	// Mat kernel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0,0,0, 1,2,1);
	// filter2D(src, yimg, -1, kernel_y, Point(-1, -1), 0.0);

	// 拉普拉斯算子
	// Mat kernel_y = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	// filter2D(src, dst, -1, kernel_y, Point(-1, -1), 0.0);

	int c = 0;
	int index = 0;
	while (true) {
		c = waitKey(500);
		if ((char)c == 27) {// ESC 
			break;
		}
		ksize = 5 + (index % 8) * 2;
		Mat kernel = Mat::ones(Size(ksize, ksize), CV_32F) / (float)(ksize * ksize);
		filter2D(src, dst, -1, kernel, Point(-1, -1));
		index++;
		imshow(OUTPUT_WIN, dst);	
	}

	// imshow("Sobel Y", yimg);
	// imshow("X", dst);
	// imshow("Y", yimg);
	waitKey(0);
	return 0;
}