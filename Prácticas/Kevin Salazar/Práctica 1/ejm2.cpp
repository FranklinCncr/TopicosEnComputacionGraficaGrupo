#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
    Mat img= imread("img.jpg", 1);
    Mat hist;
    int canales[2]= {2, 1}; // El 2 es el canal R, y el 1 es el canal G
    int bins[2]= {64, 64};
    float rango[2]= {0, 256};
    const float *rangos[]= {rango, rango};
    calcHist(&img, 1, canales, noArray(), hist, 2, bins, rangos);

    
    Mat pinta(64, 64, CV_8UC1);
    double minval, maxval;
    minMaxLoc(hist, &minval, &maxval); // Para escalar el color entre blanco y negro
    for (int r= 0; r<64; r++)
        for (int g= 0; g<64; g++)
            pinta.at<uchar>(r, g)= 255-255*hist.at<float>(r, g)/maxval;
    namedWindow("Histograma R-G", 0);
    imshow("Histograma R-G", pinta);
            
    waitKey(0); // Wait for any keystroke in one of the windows

    destroyAllWindows(); //Destroy all open windows
            
    return 0;
}




