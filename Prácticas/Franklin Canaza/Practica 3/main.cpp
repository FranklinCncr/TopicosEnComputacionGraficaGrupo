#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
double M_PI = 3.14159;

void Rotar(Mat imagen, Mat& salida, double angulo, double escala = 1)
{
	double w = imagen.size().width, h = imagen.size().height;
	double sa = sin(angulo * M_PI / 180), ca = cos(angulo * M_PI / 180);
	double cx = -w / 2 * ca - h / 2 * sa, cy = w / 2 * sa - h / 2 * ca;
	sa = fabs(sa); ca = fabs(ca);
	Size tam((w * ca + h * sa) * escala, (h * ca + w * sa) * escala);
	Mat M = getRotationMatrix2D(Point2f(0, 0), angulo, escala);
	M.at<double>(0, 2) = tam.width / 2 + cx * escala;
	M.at<double>(1, 2) = tam.height / 2 + cy * escala;
	warpAffine(imagen, salida, M, tam);
}

int main() {
	Mat img = imread("D:\\Multimedia\\Imagenes\\city.jpg");

	if (img.empty()) {
		cout << "No se cargo la imagen" << endl;
		return -1;
	}
	
	//Ejercicio 1 
	resize(img,img,Size(),2,2);
	imshow("resize", img);

	//Ejercicios 2
	flip(img,img,1);
	imshow("espejo horizontal", img);
	flip(img, img, -1);
	imshow("espejo vertical", img);

	//Ejercicio 3
	Rotar(img,img,45,0.5);	
	imshow("rotacion y escala", img); 
	Rotar(img, img, -45, 0.5);
	imshow("rotacion y escala", img);

	//Ejercicio 4
	double inc = tan(-60 * M_PI / 180.0);
	Mat c = (Mat_<double>(2, 3) << 1, inc, -inc * img.size().height / 2.0, 0, 1, 0);
	warpAffine(img, img, c, img.size());
	imshow("Inclinar", img);

	//Ejercicio 5
	Mat pt1(1, 3, CV_32FC2); 
	pt1.at<Vec2f>(0, 0) = Vec2f(0, 0); 
	pt1.at<Vec2f>(0, 1) = Vec2f(100, 0);
	pt1.at<Vec2f>(0, 2) = Vec2f(100, 100);
	Mat pt2(1, 3, CV_32FC2); 
	pt2.at<Vec2f>(0, 0) = Vec2f(10, 20); 
	pt2.at<Vec2f>(0, 1) = Vec2f(80, 40);
	pt2.at<Vec2f>(0, 2) = Vec2f(20, 70);
	Mat c = getAffineTransform(pt1, pt2);
	warpAffine(img, img, c, img.size());
	imshow("Transformación", img);


	waitKey();
	return 0;
}
