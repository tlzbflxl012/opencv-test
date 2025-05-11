#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//int main() {
//	string path = "Resources/test.png";
//	Mat img = imread(path);
//	
//	// CascadeClassifier: Haar Cascade 분류기를 사용하여 얼굴과 같은 객체를 감지하는 데 사용
//	CascadeClassifier faceCascade;
//
//	// load() 함수: Haar Cascade 분류기를 XML 파일로 불러오는 역할
//	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
//	if (faceCascade.empty()) { cout << "XML File not loaded." << endl; }
//
//	// faces는 얼굴을 저장할 벡터, Rect는 직사각형을 표현하는 OpenCV의 자료형. 
//	// 얼굴을 감지하면 detectMultiScale() 함수가 얼굴의 위치를 이 Rect 객체로 반환.
//	// img: 얼굴을 감지할 이미지.
//	// faces: 감지된 얼굴 정보를 저장할 벡터. 감지된 각 얼굴의 좌표가 faces에 저장.
//	// 1.1: 스케일 팩터. 이미지 크기를 줄여가며 얼굴을 감지하는데, 이 값이 1.1이면 이미지 크기를 10 % 씩 줄여가며 여러 스케일에서 얼굴을 찾음.
//	// 10: 최소 이웃 개수. 감지된 얼굴이 실제 얼굴일 확률을 높이기 위해, 최소 몇 개의 인접한 직사각형(검출된 영역)이 있어야 얼굴로 판단할지를 설정. 숫자가 클수록 더 정확하지만, 지나치게 높이면 감지하지 못할 수도 있음
//	vector<Rect> faces;
//	faceCascade.detectMultiScale(img, faces, 1.1, 10);
//
//	for (int i = 0; i < faces.size(); i++)
//	{
//		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
//	}
//
//	imshow("Image", img);
//	waitKey(0);
//}