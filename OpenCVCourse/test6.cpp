#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

// 이미지에서 특정 색 범위를 인식하고 마스크로 추출
//int main() {
//	string path = "Resources/shapes.png";
//	Mat img = imread(path);
//
//	cvtColor(img, imgHSV, COLOR_BGR2HSV);
//
//	namedWindow("Trackbars", (640, 200));
//	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
//	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
//	createTrackbar("Sat Min", "Trackbars", &smin, 255);
//	createTrackbar("Sat Max", "Trackbars", &smax, 255);
//	createTrackbar("Val Min", "Trackbars", &vmin, 255);
//	createTrackbar("Val Max", "Trackbars", &vmax, 255);
//
//	while (true) {
//		Scalar lower(hmin, smin, vmin);
//		Scalar upper(hmax, smax, vmax);
//		inRange(imgHSV, lower, upper, mask);
//
//		imshow("Image", img);
//		imshow("Image HSV", imgHSV);
//		imshow("Image mask", mask);
//
//		waitKey(1);
//	}
//}