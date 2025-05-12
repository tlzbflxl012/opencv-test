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
	vector<vector<Point>> contours; // ���� �ϳ��� �����ϴ� ���� ���� ��(Point)���� ����.
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// imgDil: �������� ã�� �Է� �̹���. �ݵ�� ���� �̹���(0 �Ǵ� 255) ���� ��.
	// contours: ����� ����� ������ ����Ʈ.
	// hierarchy: ������ �� ���� ������ �����ϴ� �뵵(�θ�, �ڽ� ��).
	// RETR_EXTERNAL: ���� �ٱ��� �������� ã��(��ø�� ���� ����).
	// CHAIN_APPROX_SIMPLE: �������� �����ϴ� ������ ����ȭ. �����̳� ������ ���ʿ��� �ߺ� ��ǥ���� �����ؼ� �޸� ����.
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

			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // ������ �(������)�� �ܼ��� �ٰ������� �ٻ����ִ� �Լ�

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