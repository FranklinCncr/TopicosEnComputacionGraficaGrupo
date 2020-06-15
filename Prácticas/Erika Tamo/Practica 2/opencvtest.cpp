/**
 * @file Drawing_1.cpp
 * @brief Simple geometric drawing
 * @author OpenCV team
 */
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;


void MinLocal(Mat entrada, Mat& salida, int ancho, int alto)
{
    erode(entrada, salida, Mat::ones(alto, ancho, CV_8U),
        Point(-1, -1), 1, BORDER_REPLICATE);
}
void MaxLocal(Mat entrada, Mat& salida, int ancho, int alto)
{
    dilate(entrada, salida, Mat::ones(alto, ancho, CV_8U),
        Point(-1, -1), 1, BORDER_REPLICATE);
}

/**
 * @function main
 * @brief Main function
 */
int main(void) {
    
    //////////////////////////BLUR//////////////
    /*
    Mat A;
    A = cv::imread("pirata.jpg",1);//, 1
    Mat B;
    B = cv::imread("poesia_2.bmp",1);//, 1
    blur(A, B, Size(17,17), Point(8,8));
    //GaussianBlur(A, B, Size(1, 5), 60.1415,45.14);
    imshow("Pirata real", A);
    imshow("Pirata con blur", B);
    imwrite("Tarea_2/Pirata_blur.jpg", B);

    */

    //////////////////////////FILTRO SOBEL//////////////
    /*Mat dx, dy, gradiente,img;
    img= cv::imread("peces.jpg", 1);
    Sobel(img, dx, CV_32F, 1, 0, -1);
    Sobel(img, dy, CV_32F, 0, 1, -1);
    pow(dx, 2.0, dx);
    pow(dy, 2.0, dy);
    gradiente = dx + dy;
    sqrt(gradiente, gradiente);
    Mat imgrad;
    gradiente.convertTo(imgrad, CV_8U);
    imshow("Gradiente", gradiente);
    //imshow("Real", img);
    imwrite("Gradiente.jpg", gradiente);*/

    //Detecta bastante bien las rectas :o
    //obtiene las gradientes :) en donde se dirige las variaciones
    

    ///////////////////////FILTRO LAPLACE /////////////
    /*Mat img = cv::imread("peces.jpg", 1);
    Mat lap, suma;
    Laplacian(img, lap, CV_16S);
    imshow("bordes_laplaciana", lap);
    imwrite("bordes_laplaciana.jpg", lap);
    img.convertTo(img, CV_16S);
    suma = img - 0.4 * lap;
    suma.convertTo(img, CV_8U);
    imshow("Perfilado_laplaciana", suma);
    imwrite("Perfilado_laplaciana.jpg", suma);*/
   
    ////////////////////////FILTRO CANNY
    /*Mat img = cv::imread("peces.jpg", 1);
    Mat gris, bordes;
    cvtColor(img, gris, COLOR_BGR2GRAY); //
    Canny(gris, bordes, 100, 60);
    imshow("bordes_laplaciana", bordes);
    imwrite("Tarea_2/Canny.jpg", bordes);*/
    //parece dibujo

    ////////////////////////Perfilado y la derivada
    Mat img = cv::imread("A3.jpg", 1);
    Mat salida1, salida2;
    Mat kernelPerfilado = (Mat_<float>(3, 3) << -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1);
    filter2D(img, salida1, CV_8U, kernelPerfilado);
    imshow("Perfilado", salida1);
    imwrite("Tarea_2/perfilado.jpg", salida1);
    Mat kernelDerivada = (Mat_<float>(3, 3) << -2, -1, 0, -1, 0, 1, 0, 1, 2);
    filter2D(img, salida2, CV_8U, kernelDerivada, Point(-1, -1), 128);
    imshow("Derivada", salida2);
    imwrite("Tarea_2/Derivada.jpg", salida2);
    

    //////////////////////FILTROS MAXIMOS yMINIMOS
    /*Mat img = cv::imread("pirata.jpg", 1);
    Mat  maxi;
    int tam = 12;
    MaxLocal(img, maxi, tam, tam);
    imshow("estiramiento", maxi);
    imwrite("Tarea_2/maximo_12.jpg", maxi);
    //perdida de bordes ya no se noto la cara del pirata
    
    Mat  min;
    MaxLocal(img, maxi, tam, tam);
    imshow("estiramiento22", maxi);
    imwrite("Tarea_2/minimo_12.jpg", maxi);
    */

    //perdida de bordes ya no se noto la cara del pirata


    ////////////////Ejemplo1 Estiramiento local histograma/////
    /*Mat mini, maxi, res;
    Mat img = cv::imread("peces.jpg", 1);
    int ancho = 3;
    int tam = 2 * ancho + 1; // tamaño de vecindad local
    MinLocal(img, mini, tam, tam);
    MaxLocal(img, maxi, tam, tam);
    res = img - mini;
    maxi = maxi - mini;
    divide(res, maxi, res, 255.0);
    imshow("Imagen", img);
    imshow("estiramiento", res);
    imwrite("Tarea_2/Estiramiento_a_3.jpg", res);*/
    //Estiramiento de 200 vuelve a la normalidad la imagen

    ///////Transicion entre dos imagenes
    /*Mat img2 = imread("pirata.jpg");
    Mat img1 = imread("pirata2.jpg");
    
    namedWindow("Transicion", 0);
    Mat int1, int2, res;
    for (int i = 0; i < 100; i++) {
        blur(img1, int1, Size(i * 4 + 1, 1));
        blur(img2, int2, Size((99 - i) * 4 + 1, 1));
        addWeighted(int1, 1 - i / 100.0, int2, i / 100.0, 0, res);
        imshow("Transicion", res);
        if (i % 9)
        {
            imwrite("Tarea_2/Transicion" + to_string(i)+".jpg", res);
        }
        waitKey(1);
    }*/

    /*int F = 604;
    int C = 83;
    Mat pinta(604, 83, CV_8UC1);
    int i = 0;
    while(i<F){
        int j = 0;
        while (j < C) {
            pinta.at <uchar>(i, j) = A.at<float>(i, j) + B.at<float>(i, j);
                j += 1;
        }
        i += 1;
    }
    imshow("Paisaje", A);
    imshow("Pirata3", B);*/
    
   
    
    waitKey(0);
    return(0);
}
