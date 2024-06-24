#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src1, src2, dst;
	src1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	src2 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!src1.data) {
		cout << "could not load image Linux Logo..." << endl;
		return -1;
	}
	if (!src2.data) {
		cout << "could not load image WIN7 Logo..." << endl;
		return -1;
	}

	double alpha = 0.5;
	if (src1.rows == src2.rows && src1.cols == src2.cols && src1.type() == src2.type()) {
		// addWeighted(src1, alpha, src2, (1.5 - alpha), 0.0, dst);
		multiply(src1, src2, dst, 1.0);
		
		imshow("linuxlogo", src1);
		imshow("win7logo", src2);
		namedWindow("blend demo", CV_WINDOW_AUTOSIZE);
		imshow("blend demo", dst);
	}
	else {
		printf("could not blend images , the size of images is not same...\n");
		return -1;
	}

	waitKey(0);
	return 0;
}