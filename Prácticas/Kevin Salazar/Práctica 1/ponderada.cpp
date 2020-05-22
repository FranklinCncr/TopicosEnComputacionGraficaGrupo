#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
    Mat A= imread("img.jpg", 1);
    Mat B= imread("img2.jpg", 1);
    Mat res;
   
    addWeighted(A,0.7, B,0.3, 0, res);
    imshow("Suma ponderada", res);
    waitKey(0);

                
    return 0;
}




