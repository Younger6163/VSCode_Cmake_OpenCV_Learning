#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

string convertToString(double d);
int main(int argc, char** argv) {
	Mat base, test1, test2;
	Mat hsvbase, hsvtest1, hsvtest2;
	base = imread("D:/vcprojects/images/test.jpg");
	if (!base.data) {
		printf("could not load image...\n");
		return -1;
	}
	test1 = imread("D:/vcprojects/images/lena.png");
	test2 = imread("D:/vcprojects/images/lenanoise.png");

	cvtColor(base, hsvbase, CV_BGR2HSV);
	cvtColor(test1, hsvtest1, CV_BGR2HSV);
	cvtColor(test2, hsvtest2, CV_BGR2HSV);

	int h_bins = 50; int s_bins = 60;     
	int histSize[] = { h_bins, s_bins };
	// hue varies from 0 to 179, saturation from 0 to 255     
	float h_ranges[] = { 0, 180 };     
	float s_ranges[] = { 0, 256 };
	const float* ranges[] = { h_ranges, s_ranges };
	// Use the o-th and 1-st channels     
	int channels[] = { 0, 1 };
	MatND hist_base;
	MatND hist_test1;
	MatND hist_test2;

	calcHist(&hsvbase, 1,  channels, Mat(), hist_base, 2, histSize, ranges, true, false);
	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvtest1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvtest2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
	normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());
	
	double basebase = compareHist(hist_base, hist_base, CV_COMP_INTERSECT);
	double basetest1 = compareHist(hist_base, hist_test1, CV_COMP_INTERSECT);
	double basetest2 = compareHist(hist_base, hist_test2, CV_COMP_INTERSECT);
	double tes1test2 = compareHist(hist_test1, hist_test2, CV_COMP_INTERSECT);
	printf("test1 compare with test2 correlation value :%f", tes1test2);

	Mat test12;
	test2.copyTo(test12);
	putText(base, convertToString(basebase), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(test1, convertToString(basetest1), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(test2, convertToString(basetest2), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(test12, convertToString(tes1test2), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	
	namedWindow("base", CV_WINDOW_AUTOSIZE);
	namedWindow("test1", CV_WINDOW_AUTOSIZE);
	namedWindow("test2", CV_WINDOW_AUTOSIZE);

	imshow("base", base);
	imshow("test1", test1);
	imshow("test2", test2);
	imshow("test12", test12);

	waitKey(0);
	return 0;
}

string convertToString(double d) {
	ostringstream os;
	if (os << d)
		return os.str();
	return "invalid conversion";
}