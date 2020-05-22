#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
    Mat img= imread("img.jpg", 1);
    Mat gris;
    Mat hist;
    cvtColor(img, gris, COLOR_BGR2GRAY); // Conversión a gris
    int canales[1]= {0};
    int bins[1]= {256};
    float rango[2]= {0, 256};
    const float *rangos[]= {rango};
    calcHist(&gris, 1, canales, noArray(), hist, 1, bins, rangos);

    
// Plot the histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/256 );

    Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    
    for( int i = 1; i < 256; i++ )
    {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
    }

    imshow("Entrada", img);
    imshow( "Histograma", histImage );
    waitKey(0);    

            
    return 0;
}




