#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat image = imread(argv[1], IMREAD_COLOR);
	if (image.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	imshow("input image", image);
	cvtColor(image, image, COLOR_BGR2GRAY);
	Mat means, stddev;
	meanStdDev(image, means, stddev);
	printf("means rows : %d, means cols %d\n", means.rows, means.cols);
	printf("stddev rows : %d, stddev cols %d\n", stddev.rows, stddev.cols);
	for (int row = 0; row < means.rows; row++) {
		printf("mean %d = %.3f\n", row, means.at<double>(row));
		printf("stddev %d = %.3f\n", row, stddev.at<double>(row));
	}

	Mat samples = (Mat_<double>(5, 3) << 90, 60, 90, 90, 90, 30, 60, 60, 60, 60, 60, 90, 30, 30, 30);
	Mat cov, mu;
	// calcCovarMatrix(image, cov, mu, CV_COVAR_NORMAL | CV_COVAR_ROWS);
	calcCovarMatrix(samples, cov, mu, CV_COVAR_NORMAL | CV_COVAR_ROWS);

	cout << "=============================" << endl;
	cout << "cov : " << endl;
	cout << cov/5 << endl;

	cout << "means : "<< endl;
	cout << mu << endl;

	waitKey(0);
	return 0;
}