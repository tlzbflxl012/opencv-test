#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

// 윤곽선(contour)을 찾고, 그중에서 면적이 큰 것만 화면에 그려주는 작업
// 객체 인식, 도형 검출, 경계 추적.
void getContours(Mat imgDil, Mat img) {
	vector<vector<Point>> contours; // 도형 하나를 구성하는 여러 개의 점(Point)들의 집합.
	vector<Vec4i> hierarchy;

 	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// imgDil: 윤곽선을 찾을 입력 이미지. 반드시 이진 이미지(0 또는 255) 여야 됨.
	// contours: 결과로 저장될 윤곽선 리스트.
	// hierarchy: 윤곽선 간 계층 구조를 저장하는 용도(부모, 자식 등).
	// RETR_EXTERNAL: 가장 바깥쪽 윤곽선만 찾음(중첩된 도형 무시).
	// CHAIN_APPROX_SIMPLE: 윤곽선을 구성하는 점들을 간략화. 수평선이나 직선에 불필요한 중복 좌표들을 제거해서 메모리 절약.

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
			putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}

// 이미지에서 특정 색 범위를 인식하고 마스크로 추출
//int main() {
//	string path = "Resources/shapes.png";
//	Mat img = imread(path);
//
//	cvtColor(img, imgGray, COLOR_BGR2GRAY);
//
//	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
//	// Size(3, 3): 커널 크기(블러의 범위) 3x3 픽셀 블록 단위로 평균을 내어 흐리게 함. 값이 클수록 흐릿해짐.
//	// 3: X축 방향의 표준편차(sigmaX). 흐림 정도를 조절함. 값이 크면 더 퍼지게 됨.
//	// 0: Y축 방향의 표준편차, 0이면 OpenCV가 sigmaX를 기준으로 자동 계산.
//
//	Canny(imgBlur, imgCanny, 25, 75);
//	// 윤곽선(에지)을 검출. 밝기 변화가 큰 부분만 선처럼 추출.
//	// 25: 낮은 경계값. 이 값보다 낮은 변화는 무시.
//	// 75: 높은 경계값. 이 값보다 높은 변화는 확실한 에지로 인정
//	// 일반적으로 maxThreshold = minThreshold × 2~3 정도로 설정하면 자연스러움.
//
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//	// 형태학적 연산(팽창, 침식 등)에 사용할 **커널(마스크 형태)**을 생성.
//	// MORPH_RECT → 사각형 형태의 커널을 사용하겠다는 의미.
//	// Size(3, 3) → 3x3 크기의 커널. 중심 픽셀 기준으로 주변 8개 픽셀을 포함함.
//
//	dilate(imgCanny, imgDil, kernel);
//	// 에지를 두껍게 만듦. 끊어져 있는 에지를 연결하거나 더 눈에 띄게 만들 수 있음.
//	// imgCanny → 입력 이미지 (Canny 결과)
//	// imgDil → 출력 이미지 (팽창된 결과)
//	// kernel → 어떤 형태로 얼마나 넓힐지 결정하는 구조체 (여기선 3x3 사각형)
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