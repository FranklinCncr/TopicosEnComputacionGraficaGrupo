Estudiante: Franklin Canaza

Pasando datos de la matriz de host a device y de device a host:

```c
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
```

Realizando la operación en Kernel:

```c
__global__ void addKernel(int* c, const int* a, const int* b, int size) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < size) {
    	for(int j=0;j<10;j=j+1){
            r[i]=r[i]+m[j][i];
        }
    }
}
````

Suma de los elementos de una matriz simple:

                        {{4,  2,  3,  1,  5, 6, 8, 1, 6, 4},

                        {2,  2,  3,  4,  7, 10, 5, 8, 6, 3},

                        {4,  8,  1,  2,  5, 6, 10, 9, 6, 8},
                              
                        {4,  2,  3,  4,  2, 3, 2, 11, 6, 3},
                              
                        {1,  2,  1,  14,  5, 6, 1, 10, 6, 7},
                              
                        {4,  2,  3,  11,  5, 1, 8, 4, 6, 4},
                              
                        {7,  6,  3,  4,  4, 6, 8, 10, 6, 5},
                              
                        {4,  2,  8,  4,  1, 2, 9, 3, 6, 3},
                              
                        {2,  8,  3,  9,  9, 6, 6, 1, 6, 9},
                              
                        {1,  2,  3,  4,  5, 4, 8, 2, 6, 1}}

**Captura de la salida del programa por consola**

![](suma.jpg)
