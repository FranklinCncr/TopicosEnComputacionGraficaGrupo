// filtros.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>

#define M_PI 3.14159265
using namespace cv;
using namespace std;

//Rotar y escalar una imagen indicando ángulo y escala:
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

int main()
{
    //////////////Ejercicio1
    /*Mat img2, img3, res;
    Mat img = cv::imread("Entrada/d1.jpg", 1);
    imshow("Original imagen", img);
    resize(img, img2, Size(), 1, 2);
    imshow("Realizar el zoom alarga el ancho", img2);
    imwrite("Resultados/zoom/Zoon_alargar_ancho.jpg", img2);
    resize(img, img3, Size(), 2, 1);
    imshow("Realizar el zoom alarga el alto", img3);
    imwrite("Resultados/zoom/Zoon_alargar_alto.jpg", img3);

    resize(img, img3, Size(), 2, 2);
    imshow("Realizar el zoom alarga el alto de 2,2", img3);
    imwrite("Resultados/zoom/Zoon_2_2.jpg", img3);*/

    //////////////Ejercicio2
    /*Mat dest;
    Mat img = cv::imread("Entrada/d1.jpg", 1);
    imshow("Real", img);
    //lo puso de cabeza
    flip(img, dest, 0);//muestra el pesca de manera izquierda
    imshow("Eje_x", dest);//horizontal
    imwrite("Resultados/Espejo/Eje_x.jpg", dest);

    flip(img, dest, 1);//muestra el pesca de manera derecha
    imshow("Eje_y", dest);//vertical
    imwrite("Resultados/Espejo/Eje_y.jpg", dest);

    flip(img, dest, -1);//muestra el pesca de manera derecha
    imshow("Eje_x_y", dest);//vertical
    imwrite("Resultados/Espejo/Eje_x_y.jpg", dest);*/

    /////////////////Ejercicio 3
    /*Mat salida;
    Mat img = cv::imread("Entrada/d1.jpg", 1);
    Rotar(img, salida, 45);
    imshow("Rotaryescala360", salida);
    imwrite("Resultados/Rotaryescala360.jpg", salida);*/

    /////////////////Ejercicio 4 
    
    // Inclinar (shear) la imagen img en X en angulo grados y
    //desplazar en X para que se quede centrada
    /*Mat img = cv::imread("Entrada/d1.jpg", 1);
    double inc = tan(100 * M_PI /100);//menor numero no se nota mucho la variacion
    Mat c = (Mat_<double>(2, 3) << 1, inc, -inc * img.size().height / 2.0, 0, 1, 0);
    warpAffine(img, img, c, img.size());
    imshow("Inclinar e desplaza30r",img );
    imwrite("Resultados/Inclinar/A_100_d_100.jpg", img);*/

    //al aumentar la cantidad de desplazamiento tambien se aumenta el angulo para poder centrarse la imagen pero al aumentar mucho puede tambien no notarse nada de la imágen 
    //Entonces el angulo debe ser igual al desplazamiento
    /////////////////Ejercicio 5
    Mat img = cv::imread("Entrada/d1.jpg", 1);
    Mat pt1(1, 3, CV_32FC2); // Puntos en el origen
    pt1.at<Vec2f>(0, 0) = Vec2f(139, 12); // Rellenar los tres puntos
    pt1.at<Vec2f>(0, 1) = Vec2f(121, 27);
    pt1.at<Vec2f>(0, 2) = Vec2f(148, 29);
    Mat pt2(1, 3, CV_32FC2); // Puntos en el destino
    pt2.at<Vec2f>(0, 0) = Vec2f(171, 22); // Rellenar los tres puntos
    pt2.at<Vec2f>(0, 1) = Vec2f(149, 31);
    pt2.at<Vec2f>(0, 2) = Vec2f(173, 40);
    Mat c = getAffineTransform(pt1, pt2);
    warpAffine(img, img, c, img.size());
    imshow("Transformación", img);
    imwrite("Resultados/Transformacion2.jpg", img);

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
