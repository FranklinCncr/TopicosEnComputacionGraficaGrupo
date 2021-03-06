#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
    Mat img= imread("img.jpg", 1);
    imshow("Entrada", img);
    Mat gris, hist;
    cvtColor(img, gris, COLOR_BGR2GRAY);
    int canales[1]= {0}, bins[1]= {256};
    float rango[2]= {0, 256};
    const float *rangos[]= {rango};
    calcHist(&gris, 1, canales, noArray(), hist, 1, bins, rangos);
    hist*= 255.0/norm(hist, NORM_L1);
    Mat lut(1, 256, CV_8UC1);
    float acum= 0.0;
    for (int i= 0; i<256; i++) {
        lut.at<uchar>(0, i)= acum;
        acum+= hist.at<float>(i);
    }
    Mat res;
    LUT(img, lut, res);
    imshow("Ecualizada", res);    
    
    waitKey(0);    

            
    return 0;
}




