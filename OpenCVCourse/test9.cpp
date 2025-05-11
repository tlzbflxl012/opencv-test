#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	VideoCapture cap(1);
	Mat img;

	while (true)
	{
		cap.read(img);

		imshow("Image", img);
		waitKey(0);
	}
}