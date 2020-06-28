#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <opencv2/highgui.hpp> // import no include errors
#include <opencv2/imgproc.hpp> // import no include errors 
#include <opencv2/core.hpp>       // import no include errors

#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;
#define PI 3.14159265
__global__ void SumaMatrizKernel_1(int M, float* Md_1, float* Md_2, float* Md_3) {
    int columna = blockIdx.x * blockDim.x + threadIdx.x;

    Md_3[columna] = Md_2[columna] + Md_1[columna];
}

//suma por columnas
__global__ void SumaMatrizKernel_2(int N,int M, float* Md_1,  float* Md_3, int chanales) {
    float Pvalue = 0;
    int x = blockIdx.x;//*blockDim.x * 3;
    int y = threadIdx.x;//*3;
   
    int fila = blockIdx.x;
    int columna = threadIdx.x;
    int dx = 2;
    int dy = 1;

    int ix = 10;
    int iy = 10;

    int teta = 1;
    int arreglo[3][3] = { {1,0,dx},{0,1,dy},{0,0,1} };
    int pos[3][1] = { {fila},{columna},{1} };
    int salida[3][1] = { {0},{0},{0} };

    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 1;j++) {

            for (int k = 0;k < 3;k++) {
                salida[i][j] += arreglo[i][k] * pos[k][j];
            }
        }
    }
    int nuevo_fila = salida[0][0];
    int nuevo_columna = salida[1][0];
    //printf("(%d,%d) -> (%d,%d) \n", fila, columna, nuevo_fila, nuevo_columna);
    if (nuevo_fila < M & nuevo_columna < N) {
        Md_3[chanales * nuevo_fila*blockDim.x + nuevo_columna*chanales] = Md_1[chanales * x* blockDim.x + y*chanales];
        Md_3[chanales * nuevo_fila * blockDim.x + nuevo_columna * chanales+1] = Md_1[chanales * x* blockDim.x + y * chanales + 1];
        Md_3[chanales * nuevo_fila * blockDim.x + nuevo_columna * chanales+2] = Md_1[chanales * x* blockDim.x + y * chanales + 2];
    }
    else {
        int pos_px;
        int pos_py;
        if (x < M - 1) {
            pos_px = x;//M y N cambia /////falta arreglar
            pos_py = y - (M - 1);
        }
        else {
            pos_px = x-(N-1);//M y N cambia
            pos_py = y;
        }
        printf("(%d,%d) -> (%d,%d) \n", x, y, pos_px, pos_py);
        int vecinos[3] = {0,0,0};
        if (pos_px - 1 >= 0 & pos_py - 1 >= 0) {
            vecinos[0]+= Md_1[chanales * (pos_px-1) * blockDim.x + (pos_py - 1) * chanales + 0];
            vecinos[1] += Md_1[chanales * (pos_px - 1) * blockDim.x + (pos_py - 1) * chanales + 1];
            vecinos[2] += Md_1[chanales * (pos_px - 1) * blockDim.x + (pos_py - 1) * chanales + 2];
        }
        if (pos_px + 1 >= 0 & pos_py + 1 >= 0) {
            vecinos[0] += Md_1[chanales * (pos_px + 1) * blockDim.x + (pos_py + 1) * chanales ];
            vecinos[1] += Md_1[chanales * (pos_px + 1) * blockDim.x + (pos_py + 1) * chanales + 1];
            vecinos[2] += Md_1[chanales * (pos_px + 1) * blockDim.x + (pos_py + 1) * chanales + 2];
        }
        if (pos_px >= 0 & pos_py-1 >= 0) {
            vecinos[0] += Md_1[chanales * pos_px * blockDim.x + (pos_py - 1) * chanales + 0];
            vecinos[1] += Md_1[chanales * pos_px * blockDim.x + (pos_py - 1) * chanales + 1];
            vecinos[2] += Md_1[chanales * pos_px * blockDim.x + (pos_py - 1) * chanales + 2];
        }
        if (pos_px>= 0 & pos_py + 1 >= 0) {
            vecinos[0] += Md_1[chanales * pos_px * blockDim.x + (pos_py + 1) * chanales + 0];
            vecinos[1] += Md_1[chanales * pos_px * blockDim.x + (pos_py + 1) * chanales + 1 ];
            vecinos[2] += Md_1[chanales * pos_px * blockDim.x + (pos_py + 1) * chanales + 2];
        }
        if (pos_px < M & pos_py < N) {
           Md_3[chanales * pos_px * blockDim.x + pos_py * chanales] = vecinos[0];
            Md_3[chanales * pos_px * blockDim.x + pos_py * chanales + 1] = vecinos[1];
            Md_3[chanales * pos_px * blockDim.x + pos_py * chanales + 2] = vecinos[2];
        }
    }
}

// Suma por columnas de una matriz
__global__ void SumaColMatrizKernel_3(int M, float* Md_1, float* Md_2, float* Md_3) {
    int columna = blockIdx.x;
    int pasos = M / blockDim.x;
    int posIni = columna * M + threadIdx.x * pasos;
    for (int k = 0; k < pasos; ++k) {
        Md_3[posIni + k] = Md_2[posIni + k] + Md_1[posIni + k];
    }
}

void SumaMatriz(int M, int N, float* Mh_1, float* Mr_3,  int chanales) {
    int size = M * N * 3 * sizeof(float);
    float* Md_1;
    float* Md_3;
    // Allocate en device
    cudaMalloc(&Md_1, size);
    cudaMalloc(&Md_3, size);

    // Inicializo matrices en el device
    cudaMemcpy(Md_1, Mh_1, size, cudaMemcpyHostToDevice);
    //SumaMatrizKernel_1 <<< 1,M*N*3 >>>(M, Md_1, Md_2, Md_3);
    //si hubiera tantos hilos suficientes
    /////////////oprimero es bloques y despues hilos
    /*int chunk = 2;
    SumaColMatrizKernel_3 << < N, M / chunk >> > (M, Md_1, Md_2, Md_3);*/
    SumaMatrizKernel_2 << < M, N >> > (N, M, Md_1, Md_3, chanales);
    cudaMemcpy(Mr_3, Md_3, size, cudaMemcpyDeviceToHost);
    cv::Mat imgSalidaFR(M, N, CV_32FC3, Mr_3);
    cv::imwrite("salida.jpg", imgSalidaFR);
    cv::Mat uno = cv::imread("salida.jpg", CV_32F);
    cv::imshow("Resultado", uno);

    cudaFree(Md_1);

}

int main() {
    //profundidad 24


    cv::Mat A = cv::imread("d2.jpg", CV_32F);
    

    int M = A.rows;//alto
    int N = A.cols;
    
    int chaneles = A.channels();
    
    float* Mh_1 = new float[M * N * 3];//matriz host

    float* Mr_3 = new float[M * N * 3];//matriz host
    uchar * temp1=A.data;

    for (int i = 0; i < M * N * 3; i += 1) {
        Mh_1[i] = (float)temp1[i];

        Mr_3[i] = 0;
    }
    SumaMatriz(M, N, Mh_1, Mr_3, chaneles);
       
    cv::waitKey(0);
    return 0;
}