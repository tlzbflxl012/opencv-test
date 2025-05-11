#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

// ������(contour)�� ã��, ���߿��� ������ ū �͸� ȭ�鿡 �׷��ִ� �۾�
// ��ü �ν�, ���� ����, ��� ����.
void getContours(Mat imgDil, Mat img) {
	vector<vector<Point>> contours; // ���� �ϳ��� �����ϴ� ���� ���� ��(Point)���� ����.
	vector<Vec4i> hierarchy;

 	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// imgDil: �������� ã�� �Է� �̹���. �ݵ�� ���� �̹���(0 �Ǵ� 255) ���� ��.
	// contours: ����� ����� ������ ����Ʈ.
	// hierarchy: ������ �� ���� ������ �����ϴ� �뵵(�θ�, �ڽ� ��).
	// RETR_EXTERNAL: ���� �ٱ��� �������� ã��(��ø�� ���� ����).
	// CHAIN_APPROX_SIMPLE: �������� �����ϴ� ������ ����ȭ. �����̳� ������ ���ʿ��� �ߺ� ��ǥ���� �����ؼ� �޸� ����.

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
			putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}

// �̹������� Ư�� �� ������ �ν��ϰ� ����ũ�� ����
//int main() {
//	string path = "Resources/shapes.png";
//	Mat img = imread(path);
//
//	cvtColor(img, imgGray, COLOR_BGR2GRAY);
//
//	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
//	// Size(3, 3): Ŀ�� ũ��(���� ����) 3x3 �ȼ� ��� ������ ����� ���� �帮�� ��. ���� Ŭ���� �帴����.
//	// 3: X�� ������ ǥ������(sigmaX). �帲 ������ ������. ���� ũ�� �� ������ ��.
//	// 0: Y�� ������ ǥ������, 0�̸� OpenCV�� sigmaX�� �������� �ڵ� ���.
//
//	Canny(imgBlur, imgCanny, 25, 75);
//	// ������(����)�� ����. ��� ��ȭ�� ū �κи� ��ó�� ����.
//	// 25: ���� ��谪. �� ������ ���� ��ȭ�� ����.
//	// 75: ���� ��谪. �� ������ ���� ��ȭ�� Ȯ���� ������ ����
//	// �Ϲ������� maxThreshold = minThreshold �� 2~3 ������ �����ϸ� �ڿ�������.
//
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//	// �������� ����(��â, ħ�� ��)�� ����� **Ŀ��(����ũ ����)**�� ����.
//	// MORPH_RECT �� �簢�� ������ Ŀ���� ����ϰڴٴ� �ǹ�.
//	// Size(3, 3) �� 3x3 ũ���� Ŀ��. �߽� �ȼ� �������� �ֺ� 8�� �ȼ��� ������.
//
//	dilate(imgCanny, imgDil, kernel);
//	// ������ �β��� ����. ������ �ִ� ������ �����ϰų� �� ���� ��� ���� �� ����.
//	// imgCanny �� �Է� �̹��� (Canny ���)
//	// imgDil �� ��� �̹��� (��â�� ���)
//	// kernel �� � ���·� �󸶳� ������ �����ϴ� ����ü (���⼱ 3x3 �簢��)
//
//	getContours(imgDil, img);
//
//	imshow("Image", img);
//	/*imshow("Image Gray", imgGray);
//	imshow("Image Blur", imgBlur);
//	imshow("Image Canny", imgCanny);
//	imshow("Image Dil", imgDil);*/
//
//	waitKey(0);
//}