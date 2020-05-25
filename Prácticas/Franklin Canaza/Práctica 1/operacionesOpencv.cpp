#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace cv;
using namespace std;
void gamma(string);
void add(string,string);
void sub(string,string);
int main(int argc, char** argv){
    add("image1.jpg","image2.jpg");
    sub("image1.jpg","image2.jpg");
    gamma("image1.jpg");
    return 0;
}
void gamma(string image){

Mat img= imread("image", 1);
    imshow("Entrada", img);
    
    Mat im32F;
    img.convertTo(im32F, CV_32F, 1.0/255.0);
    pow(im32F, 0.85, im32F);
    im32F.convertTo(img, CV_8U, 255);
    
    imshow("Gamma", im32F);    
    
    waitKey(0); 
}
void add(string image1,string image2){
double alpha = 0.5; double beta; double input=0;

 Mat src1, src2, dst; 
 
 src1 = imread(image1);
 src2 = imread(image2);

 namedWindow("Linear Blend", 1);

 beta = ( 1.0 - alpha );

 addWeighted( src1, alpha, src2, beta, 0.0, dst);

 imshow( "Linear Blend", dst );

 waitKey(0);
 return 0;
}
void sub(string image1,string image2){
double alpha = 0.5; double beta; double input=1;

 Mat src1, src2, dst; 
 
 src1 = imread(image1);
 src2 = imread(image2);

 namedWindow("Linear Blend", 1);

 beta = ( 1.0 - alpha );
 
 cv.subtract( src1, alpha, src2, beta, 0.0, dst);

 imshow( "Linear Blend", dst );

 waitKey(0);
 return 0;
}