#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

String model_bin_file = "/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/007_models/bvlc_googlenet.caffemodel";
String model_txt_file = "/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/007_models/bvlc_googlenet.prototxt";
String labels_txt_file = "/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/007_models/classification_classes_ILSVRC2012.txt";
vector<String> readLabels();
int main(int argc, char** argv) {
	Mat src = imread(argv[1], IMREAD_COLOR);
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);
	vector<String> labels = readLabels();
	Net net = readNetFromCaffe(model_txt_file, model_bin_file);
	if (net.empty()) {
		printf("read caffe model data failure...\n");
		return -1;
	}
	double scale = src.cols / 224.0f;	//! 图像缩放到224的推理尺寸
	Mat inputBlob = blobFromImage(src, scale, Size(224, 224), Scalar(104, 117, 123));
	Mat prob;
	for (int i = 0; i < 10; i++) {
		net.setInput(inputBlob, "data");
		prob = net.forward("prob");
	}
	Mat probMat = prob.reshape(1, 1);
	Point classNumber;
	double classProb;
	minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	int classidx = classNumber.x;
	printf("\n current image classification : %s, possible : %.2f", labels.at(classidx).c_str(), classProb);

	putText(src, labels.at(classidx), Point(20, 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8);
	imshow("Image Classification", src);

	waitKey(0);
	return 0;
}
vector<String> readLabels() {
	vector<String> classNames;
	ifstream fp(labels_txt_file);
	if (!fp.is_open()) {
		printf("could not open the file");
		exit(-1);
	}
	string name;
	while (!fp.eof()) {
		getline(fp, name);
		if (name.length()) {
			// classNames.push_back(name.substr(name.find(' ') + 1));
			classNames.push_back(name);
		}
	}
	fp.close();
	return classNames;
}
