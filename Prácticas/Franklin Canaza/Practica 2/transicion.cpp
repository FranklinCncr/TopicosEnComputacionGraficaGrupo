#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;
int main(){
    
    Mat img1 = imread("tierra.jpg");
    Mat img2 = imread("marte.jpg");  

    if (img1.empty() || img2.empty()) return 0;

    Mat int1, int2, res;

    for (int i= 0; i<100; i+=9) {        
      blur(img1, int1, Size(i*4+1, 1));
      blur(img2, int2, Size((99-i)*4+1, 1));
      addWeighted(int1, 1-i/100.0, int2, i/100.0, 0, res);
      imwrite("transicion"+to_string(i)+".jpg", res);
    }         

    return 0;
}