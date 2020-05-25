#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <bits/stdc++.h>

#define DIMBLOCKX 32

__global__ void SumaColMatrizKernel (int M, int N, float *Md, float *Nd){
  __shared__ float Nds[DIMBLOCKX];
  float Pvalue = 0;
  int columna = blockIdx.x * (N/gridDim.x) + threadIdx.x;
  int pasos = M/blockDim.x;
  int posIni = columna * M + threadIdx.x * pasos;

  for (int k=0; k<pasos; k++){
      Pvalue += Md[posIni + k];
  }

  atomicAdd(&Nd[columna],Pvalue);
  
  __syncthreads();

  if (threadIdx.x == 0){
      for (int i=1; i<blockDim.x; i++){
          Nds[0] += Nds[i];
      }
      atomicAdd(&Nd[blockIdx.x],Nds[0]);
  }
  
  
}  

void SumaColMatriz (int M, int N, float *Mh, float *Nh){
    
  int size = M*N*sizeof(float), size2=N*sizeof(float);
  float *Md, *Nd;

  cudaMalloc(&Md, size);
  cudaMalloc(&Nd, size2);

  cudaMemcpy(Md, Mh, size,  cudaMemcpyHostToDevice);
  cudaMemset(Nd, 0, size2);

  int chunk = 32;
  dim3 tamGrid(N/chunk, 1);
  dim3 tamBlock(M/chunk, chunk, 1);
  SumaColMatrizKernel<<<tamGrid, tamBlock>>> (M, N, Md, Nd);

  cudaMemcpy(Nh,Nd, size2, cudaMemcpyDeviceToHost);

  cudaFree(Md); cudaFree(Nd);
}

int main(){

  int M = 1024;
  int N = 512;

  float *Mh = new float[M*N];//matriz host
  for (int i=0; i<M; i++)
    for (int j=0; j<N; j++)
      Mh[i*N+j] = 1;

  float *Nh = new float[N];//suma de columnas

  SumaColMatriz(M,N,Mh,Nh);

  for (int i=0; i<N; i++)
    std::cout<<Nh[i]<<" ";

  return 0;
}
