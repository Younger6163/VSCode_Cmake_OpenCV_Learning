#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const size_t width = 300;
const size_t height = 300;
const float meanVal = 127.5;
const float scaleFactor = 0.007843f;
const char* classNames[] = { "background",
"aeroplane", "bicycle", "bird", "boat",
"bottle", "bus", "car", "cat", "chair",
"cow", "diningtable", "dog", "horse",
"motorbike", "person", "pottedplant",
"sheep", "sofa", "train", "tvmonitor" };

String modelFile = "/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/007_models/MobileNetSSD_deploy.caffemodel";
String model_text_file = "/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/007_models/MobileNetSSD_deploy.prototxt";

//! 读取视频报错：CAP_IMAGES: Stop scanning. Can't read image file：xxx

int main(int argc, char** argv) {
	VideoCapture capture;
	capture.open("/home/younger/VSCode_WorkSpace/Project_CPP/VSCode_Cmake_OpenCV_Learning/images/001/sample.mp4");
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	int w = capture.get(CAP_PROP_FRAME_WIDTH);
	int h = capture.get(CAP_PROP_FRAME_HEIGHT);
	printf("frame width : %d, frame height : %d", w, h);

	// set up net
	Net net = readNetFromCaffe(model_text_file, modelFile);

	Mat frame;
	while (capture.read(frame)) {
		imshow("input", frame);

		// 预测
		Mat inputblob = blobFromImage(frame, scaleFactor, Size(width, height), meanVal, false);
		net.setInput(inputblob, "data");
		Mat detection = net.forward("detection_out");

		// 绘制
		Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
		float confidence_threshold = 0.25;
		for (int i = 0; i < detectionMat.rows; i++) {
			float confidence = detectionMat.at<float>(i, 2);
			if (confidence > confidence_threshold) {
				size_t objIndex = (size_t)(detectionMat.at<float>(i, 1));
				float tl_x = detectionMat.at<float>(i, 3) * frame.cols;
				float tl_y = detectionMat.at<float>(i, 4) * frame.rows;
				float br_x = detectionMat.at<float>(i, 5) * frame.cols;
				float br_y = detectionMat.at<float>(i, 6) * frame.rows;

				Rect object_box((int)tl_x, (int)tl_y, (int)(br_x - tl_x), (int)(br_y - tl_y));
				rectangle(frame, object_box, Scalar(0, 0, 255), 2, 8, 0);
				putText(frame, format("%s", classNames[objIndex]), Point(tl_x, tl_y), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 2);
			}
		}
		imshow("ssd-video-demo", frame);
		char c = waitKey(5);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();
	waitKey(0);
	return 0;
}