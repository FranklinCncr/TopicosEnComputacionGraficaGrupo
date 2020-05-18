#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>
#include <cuda_runtime.h> 

__global__ void addKernel(int* c, const int* a, const int* b, int size) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < size) {
    	for(int j=0;j<10;j=j+1){
            r[i]=r[i]+m[j][i];
        }
    }
}

void sum Cuda(int* r, const int* m, int size) {
    int* dev_m = nullptr;
    int* dev_r = nullptr;

    cudaMalloc((void**)&dev_m, size * sizeof(int));
    cudaMalloc((void**)&dev_r, size * sizeof(int));

    cudaMemcpy(dev_m, m, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_r, r, size * sizeof(int), cudaMemcpyHostToDevice);

    addKernel<<<2, (size + 1) / 2>>>(dev_m, dev_r, size);
    
    cudaDeviceSynchronize();

    cudaMemcpy(r, dev_r, size * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(dev_m);
    cudaFree(dev_r);
}

int main(int argc, char** argv) {
    const int size = 10;
    const int m[size][size] = 	{{4,  2,  3,  1,  5, 6, 8, 1, 6, 4},
                            	{2,  2,  3,  4,  7, 10, 5, 8, 6, 3},
                            	{4,  8,  1,  2,  5, 6, 10, 9, 6, 8},
                            	{4,  2,  3,  4,  2, 3, 2, 11, 6, 3},
                            	{1,  2,  1,  14,  5, 6, 1, 10, 6, 7},
                            	{4,  2,  3,  11,  5, 1, 8, 4, 6, 4},
                            	{7,  6,  3,  4,  4, 6, 8, 10, 6, 5},
                            	{4,  2,  8,  4,  1, 2, 9, 3, 6, 3},
                            	{2,  8,  3,  9,  9, 6, 6, 1, 6, 9},
                            	{1,  2,  3,  4,  5, 4, 8, 2, 6, 1}}
    int r[size] = { 0 };

    sumCuda(r, m, size);

    printf("r = %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9]);

    cudaDeviceReset();

    return 0;
}