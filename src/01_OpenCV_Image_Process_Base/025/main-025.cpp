#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace cv; 
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	cvtColor(src, src, CV_BGR2GRAY);
	equalizeHist(src, dst);
	char INPUT_T[] = "input image";
	char OUTPUT_T[] = "result image";
	namedWindow(INPUT_T, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_T, CV_WINDOW_AUTOSIZE);

	imshow(INPUT_T, src);
	imshow(OUTPUT_T, dst);

	waitKey(0);
	return 0;
}