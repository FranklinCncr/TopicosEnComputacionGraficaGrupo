#include <iostream>
#include "stdio.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <vector>
#include "BMP.h"

#include <stdio.h>
using namespace cv;
using namespace std;
// Suma por columnas de una matriz
__global__ void SumaMatrizKernel_1(int M, float* Md_1, float* Md_2, float* Md_3) {
    int columna = blockIdx.x * blockDim.x + threadIdx.x;

    Md_3[columna] = Md_2[columna] + Md_1[columna];
}

//suma por columnas
__global__ void SumaMatrizKernel_2(int N, float* Md_1, float* Md_2, float* Md_3,int chanales) {
    float Pvalue = 0;
    int columna = blockIdx.x * blockDim.x + threadIdx.x;//blockIdx.x* blockDim.x + threadIdx.x;
    int posIni = blockIdx.x * blockDim.x + threadIdx.x; //columna * N;
    for (int k = 0; k < N; k+=1) {
        Md_3[chanales*(posIni*N + k)] = Md_2[chanales * (posIni * N + k)] + Md_1[chanales * (posIni * N + k)];
        Md_3[chanales * (posIni * N + k) +1] = Md_2[chanales * (posIni * N + k) +1] + Md_1[chanales * (posIni * N + k)+1];
        Md_3[chanales * (posIni * N + k) + 2] = Md_2[chanales * (posIni * N + k) + 2] + Md_1[chanales * (posIni * N + k)+2];
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

void SumaMatriz(int M, int N, float* Mh_1, float* Mh_2, float* Mr_3,int chanales) {
    int size = M * N * sizeof(float);
    float* Md_1;
    float* Md_2;
    float* Md_3;
    // Allocate en device
    cudaMalloc(&Md_1, size);
    cudaMalloc(&Md_2, size);
    cudaMalloc(&Md_3, size);

    // Inicializo matrices en el device
    cudaMemcpy(Md_1, Mh_1, size, cudaMemcpyHostToDevice);
    cudaMemcpy(Md_2, Mh_2, size, cudaMemcpyHostToDevice);
    //SumaMatrizKernel_1 <<<1, M*N*3>>>(M, Md_1, Md_2, Md_3);
    //si hubiera tantos hilos suficientes
    
    SumaMatrizKernel_2 <<<1, M>>>(N, Md_1, Md_2, Md_3, chanales);
    /*int chunk = 2;
    SumaColMatrizKernel_3 << < N, M / chunk >> > (M, Md_1, Md_2, Md_3);*/
    cudaMemcpy(Mr_3, Md_3, size, cudaMemcpyDeviceToHost);
    cout << "Entra" << endl;
    int i = 0;
    while (i < M) {
        int j = 0;
        while (j < N) {
            cout << Mr_3[i*N+j] << " ";
            j += 1;
        }
        cout << endl;
        i += 1;
    }

    cudaFree(Md_1);

}

int main() {
//profundidad 24

    BMP bmp_po("poesia.bmp");

    BMP bmp_po2("poesia_2.bmp");

    vector<uint8_t> datosMh_1 = bmp_po.get_data();
    vector<uint8_t> datosMh_2 = bmp_po2.get_data();

    cout << "total_datos" << datosMh_1.size() << endl;//150396 datos 
    int tamano_to = datosMh_1.size();
    int M = bmp_po.get_alto();
    int N = bmp_po.get_ancho();
    uint32_t chaneles = bmp_po.get_chaneles();
    float* Mh_1 = new float[tamano_to];//matriz host

    float* Mh_2 = new float[tamano_to];//matriz host

    float* Mr_3 = new float[tamano_to];//matriz host

    for (int i = 0; i < tamano_to; i += 1) {
        Mh_1[i] = datosMh_1[i];
        Mh_2[i] = datosMh_2[i];
        Mr_3[i] = 0;
    }


    /////////////////////SUMA SECUENCIA///////////////////////
    /*
   for (int i = 0; i < tamano_to; i += 3) {
       Mr_3[i] = datosMh_1[i] + datosMh_2[i];
   }*/
   

   /*
   for (int i = 0; i < M; i++) {
       for (int j = 0; j < N; j++) {
           Mr_3[chaneles*(i * N + j)+0] = datosMh_1[chaneles * (i * N + j)+0] + datosMh_2[chaneles * (i * N + j)+0];
           Mr_3[chaneles*(i * N + j) + 1] = datosMh_1[chaneles * (i * N + j) + 1] + datosMh_2[chaneles * (i * N + j) + 1];
           Mr_3[chaneles*(i * N + j) + 2] = datosMh_1[chaneles * (i * N + j) + 2] + datosMh_2[chaneles * (i * N + j) + 2];
       }
   }*/
   //va a saltando con la cantidad 
   /////////////////////////SUMA PARALELA////////////////////

    SumaMatriz(M, N, Mh_1, Mh_2, Mr_3, chaneles);

    vector<uint8_t> nuevo_data;
    for (int i = 0; i < tamano_to; i++) {
        nuevo_data.push_back(Mr_3[i]);
    }
    cout << "tamano de la imagen" << nuevo_data.size() << endl;

    bmp_po2.write_image_data("Salida_suma.bmp", nuevo_data);

    cout << "Erika animo tú puedes de verdad" << endl;

    return 0;
}