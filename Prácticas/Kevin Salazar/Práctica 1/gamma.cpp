#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
    Mat img= imread("img.jpg", 1);
    imshow("Entrada", img);
    
    Mat im32F;
    img.convertTo(im32F, CV_32F, 1.0/255.0);
    pow(im32F, 0.25, im32F);
    im32F.convertTo(img, CV_8U, 255);
    
    imshow("Gamma", im32F);    
    
    waitKey(0);    

            
    return 0;
}




