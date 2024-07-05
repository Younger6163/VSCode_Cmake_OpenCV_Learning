#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv) {
	Mat img1 = imread("/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/digit-01.png", IMREAD_GRAYSCALE);
	Mat img2 = imread("/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/digit-02.png", IMREAD_GRAYSCALE);
	if (!img1.data || !img2.data) {
		return -1;
	}
	imshow("image1", img1);
	imshow("image2", img2);

	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	vector<KeyPoint> keypoints_1;
	vector<KeyPoint> keypoints_2;

	Mat descriptor_1, descriptor_2;
	detector->detectAndCompute(img1, Mat(), keypoints_1, descriptor_1);
	detector->detectAndCompute(img2, Mat(), keypoints_2, descriptor_2);

	BFMatcher matcher(NORM_L2);
	vector<DMatch> matches;
	matcher.match(descriptor_1, descriptor_2, matches);

	Mat matchesImg;
	drawMatches(img1, keypoints_1, img2, keypoints_2, matches, matchesImg);
	imshow("Descriptor Demo", matchesImg);

	waitKey(0);
	return 0;
}