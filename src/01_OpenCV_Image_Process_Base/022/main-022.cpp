#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	Mat src, src_gray, dst;
	src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_TITLE[] = "input image";
	char OUTPUT_TITLE[] = "hough-line-detection";
	namedWindow(INPUT_TITLE, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_TITLE, src);

	// extract edge
	Canny(src, src_gray, 150, 200);
	cvtColor(src_gray, dst, CV_GRAY2BGR);
	imshow("edge image", src_gray);

	// vector<Vec2f> lines;     
	// HoughLines(src_gray, lines, 1, CV_PI / 180, 150, 0, 0);
	// for (size_t i = 0; i < lines.size(); i++) { 
	// 	float rho = lines[i][0]; // 极坐标中的r长度
	// 	float theta = lines[i][1]; // 极坐标中的角度
	// 	Point pt1, pt2;         
	// 	double a = cos(theta), b = sin(theta);         
	// 	double x0 = a*rho, y0 = b*rho;      
	// 	// 转换为平面坐标的四个点
	// 	pt1.x = cvRound(x0 + 1000 * (-b));        
	// 	pt1.y = cvRound(y0 + 1000 * (a));         
	// 	pt2.x = cvRound(x0 - 1000 * (-b));         
	// 	pt2.y = cvRound(y0 - 1000 * (a));         
	// 	line(dst, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA); 
	// }


	vector<Vec4f> plines;
	HoughLinesP(src_gray, plines, 1, CV_PI / 180.0, 10, 0, 10);
	Scalar color = Scalar(0, 0, 255);
	for (size_t i = 0; i < plines.size(); i++) {
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA);
	}

	imshow(OUTPUT_TITLE, dst);

	waitKey(0);
	return 0;
}