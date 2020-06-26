#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
double M_PI = 3.14159;

int main() {
	Mat img = imread("D:\\Multimedia\\Imagenes\\city.jpg");

	if (img.empty()) {
		cout << "No se cargo la imagen" << endl;
		return -1;
	}
	
	double w = img.size().width, h = img.size().height;
	Mat pt1(1, 4, CV_32FC2); 
	pt1.at<Vec2f>(0, 0) = Vec2f(0, 0);
	pt1.at<Vec2f>(0, 1) = Vec2f(w, 0);
	pt1.at<Vec2f>(0, 2) = Vec2f(w, h);
	pt1.at<Vec2f>(0, 3) = Vec2f(0, h);
	Mat pt2(1, 4, CV_32FC2); 
	pt2.at<Vec2f>(0, 0) = Vec2f(w * 0.3, 0);
	pt2.at<Vec2f>(0, 1) = Vec2f(w * 0.7, 0);
	pt2.at<Vec2f>(0, 2) = Vec2f(w, h);
	pt2.at<Vec2f>(0, 3) = Vec2f(0, h);
	Mat c = getPerspectiveTransform(pt1, pt2);
	Mat resultado;
	warpPerspective(img, resultado, c, img.size());
	imshow("Perspectiva de una imagen", resultado);
	
	int m = 10;

	Mat mapa1(img.size(), CV_32FC1);
	Mat mapa2(img.size(), CV_32FC1);
	for (int y = 0; y < img.size().height; y++)
		for (int x = 0; x < img.size().width; x++) {
			mapa1.at<float>(y, x) = x + rand() % (2 * m + 1) - m; 
			mapa2.at<float>(y, x) = y + rand() % (2 * m + 1) - m; 
		}
	Mat resultado;
	remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
	imshow("Transformacion con un radio de deformación", resultado);

	int m = 10;

	Mat mapa1(img.size(), CV_32FC1);
	Mat mapa2(img.size(), CV_32FC1);
	for (int y = 0; y < img.size().height; y++)
		for (int x = 0; x < img.size().width; x++) {
			mapa1.at<float>(y, x) = x - x % m + y % m;
			mapa2.at<float>(y, x) = y - y % m + x % m;
		}
	Mat resultado;
	remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
	imshow("Transformacion de acristalado", resultado);





	waitKey();
	return 0;
}
