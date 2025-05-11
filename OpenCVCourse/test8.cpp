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
//	// CascadeClassifier: Haar Cascade �з��⸦ ����Ͽ� �󱼰� ���� ��ü�� �����ϴ� �� ���
//	CascadeClassifier faceCascade;
//
//	// load() �Լ�: Haar Cascade �з��⸦ XML ���Ϸ� �ҷ����� ����
//	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
//	if (faceCascade.empty()) { cout << "XML File not loaded." << endl; }
//
//	// faces�� ���� ������ ����, Rect�� ���簢���� ǥ���ϴ� OpenCV�� �ڷ���. 
//	// ���� �����ϸ� detectMultiScale() �Լ��� ���� ��ġ�� �� Rect ��ü�� ��ȯ.
//	// img: ���� ������ �̹���.
//	// faces: ������ �� ������ ������ ����. ������ �� ���� ��ǥ�� faces�� ����.
//	// 1.1: ������ ����. �̹��� ũ�⸦ �ٿ����� ���� �����ϴµ�, �� ���� 1.1�̸� �̹��� ũ�⸦ 10 % �� �ٿ����� ���� �����Ͽ��� ���� ã��.
//	// 10: �ּ� �̿� ����. ������ ���� ���� ���� Ȯ���� ���̱� ����, �ּ� �� ���� ������ ���簢��(����� ����)�� �־�� �󱼷� �Ǵ������� ����. ���ڰ� Ŭ���� �� ��Ȯ������, ����ġ�� ���̸� �������� ���� ���� ����
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