#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
    
  Mat img = imread("coliseo.jpg");
    double w= img.size().width, h= img.size().height;
    Mat pt1(1, 4, CV_32FC2);                  // Cuatro puntos en el origen
    pt1.at<Vec2f>(0,0)= Vec2f(0, 0);
    pt1.at<Vec2f>(0,1)= Vec2f(w, 0);
    pt1.at<Vec2f>(0,2)= Vec2f(w, h);
    pt1.at<Vec2f>(0,3)= Vec2f(0, h);
    Mat pt2(1, 4, CV_32FC2);                  // Cuatro puntos en el destino
    pt2.at<Vec2f>(0,0)= Vec2f(w*0.1, 0);
    pt2.at<Vec2f>(0,1)= Vec2f(w*0.9, 0);
    pt2.at<Vec2f>(0,2)= Vec2f(w, h);
    pt2.at<Vec2f>(0,3)= Vec2f(0, h);
    Mat c= getPerspectiveTransform(pt1, pt2);
    Mat resultado;
    warpPerspective(img, resultado, c, img.size());
    imwrite( "perspectiva2.jpg", resultado );
    return 0;  
    

    return 0;
}
