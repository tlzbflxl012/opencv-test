#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<vector<int>> myColors{
	{124,48,114,143,17,255}, // purple
	{68,72,156,102,126,255}, // green
	{0,62,0,35,255,255} }; // orange

vector<Scalar> myColorValues{ 
	{255,0,255}, // purple 
	{0,255,0}, // green
	{51,153,255} }; // orange

void getContours(Mat imgDil) {
	vector<vector<Point>> contours; // 도형 하나를 구성하는 여러 개의 점(Point)들의 집합.
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// imgDil: 윤곽선을 찾을 입력 이미지. 반드시 이진 이미지(0 또는 255) 여야 됨.
	// contours: 결과로 저장될 윤곽선 리스트.
	// hierarchy: 윤곽선 간 계층 구조를 저장하는 용도(부모, 자식 등).
	// RETR_EXTERNAL: 가장 바깥쪽 윤곽선만 찾음(중첩된 도형 무시).
	// CHAIN_APPROX_SIMPLE: 윤곽선을 구성하는 점들을 간략화. 수평선이나 직선에 불필요한 중복 좌표들을 제거해서 메모리 절약.
	vector<vector<Point>> conPoly(contours.size()); 
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);

			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // 복잡한 곡선(윤곽선)을 단순한 다각형으로 근사해주는 함수

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			int objCor = (int)conPoly[i].size();

			if (objCor == 3) objectType = "Tri";
			if (objCor == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05)
				{
					objectType = "Square";
				}
				else
				{
					objectType = "Rect";
				}
			}
			if (objCor > 4) objectType = "Circle";

			drawContours(img, contours, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}

void findColor(Mat img)
{
	Mat imgHSv;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_sring(i), mask);
		getContours(mask);
	}
}

int main() {
	VideoCapture cap(1);
	Mat img;

	while (true)
	{
		cap.read(img);
		findColor(img);

		imshow("Image", img);
		waitKey(0);
	}
}