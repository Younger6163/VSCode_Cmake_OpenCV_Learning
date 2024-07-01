#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <iostream> 
using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char input_title[] = "input image";
	char output_title[] = "blur image";
	namedWindow(input_title, CV_WINDOW_AUTOSIZE);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow(input_title, src);

	blur(src, dst, Size(3, 3), Point(-1, -1));
	imshow(output_title, dst);

	Mat gblur;
	GaussianBlur(src, gblur, Size(11, 11), 11, 11);
	imshow("gaussian blur", gblur);
 
	waitKey(0);
	return 0;
}