// Transformaciones de Perspectiva.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main()
{   
    //Transformacion de la prespectiva ---
    /*Mat img = cv::imread("d1.jpg");
    double w = img.size().width, h = img.size().height;
    Mat pt1(1, 4, CV_32FC2);       // Cuatro puntos en el origen
    pt1.at<Vec2f>(0, 0) = Vec2f(0, 0);
    pt1.at<Vec2f>(0, 1) = Vec2f(w, 0);
    pt1.at<Vec2f>(0, 2) = Vec2f(w, h);
    pt1.at<Vec2f>(0, 3) = Vec2f(0, h);
    Mat pt2(1, 4, CV_32FC2);       // Cuatro puntos en el destino
    pt2.at<Vec2f>(0, 0) = Vec2f(w * 0.3, 0);
    pt2.at<Vec2f>(0, 1) = Vec2f(w * 0.7, 0);
    pt2.at<Vec2f>(0, 2) = Vec2f(w, h);
    pt2.at<Vec2f>(0, 3) = Vec2f(0, h);
    Mat c = getPerspectiveTransform(pt1, pt2);
    Mat resultado;
    warpPerspective(img, resultado, c, img.size());
    imshow("Doraemon", img);
    imshow("Transforma_prespectiva", resultado);
    imwrite("Transforma_prespectiva.jpg", resultado);*/

    /**/
    Mat img = cv::imread("d1.jpg");
    Mat mapa1(img.size(), CV_32F);
    Mat mapa2(img.size(), CV_32F);
    int m = 20;//1,5,20
    for (int y = 0; y < img.size().height; y++)
        for (int x = 0; x < img.size().width; x++) {
        mapa1.at<float>(y, x) = x + rand() % (2 * m + 1) - m;   // Mapa 1
        mapa2.at<float>(y, x)= y+rand()%(2*m+1) - m;   // Mapa2
        }
    Mat resultado;
    remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
    imshow("Doraemon", img);
    imshow("Destino", resultado);
    imwrite("Transforma_r20.jpg", resultado);*/

    /*Mat img = cv::imread("d1.jpg");
    Mat mapa1(img.size(), CV_32FC1);
    Mat mapa2(img.size(), CV_32FC1);
    int m = 15;//1,5,20
    for (int y = 0; y < img.size().height; y++)
        for (int x = 0; x < img.size().width; x++) {
            mapa1.at<float>(y, x) = x - x % m + y % m;
            mapa2.at<float>(y, x) = y - y % m + x % m;
        }
    Mat resultado;
    remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
    imshow("Doraemon", img);
    imshow("Destino", resultado);

    imwrite("Transforma_acristilado15.jpg", resultado);*/

    waitKey(0);
    return(0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
