%%cu
#include <bits/stdc++.h>

using namespace std;

__global__ void ecualizacion(int *dev_img, int *dev_funcion){
    
    int x = threadIdx.x + blockIdx.x*blockDim.x;
  
    dev_img[x] = dev_funcion[dev_img[x]];

}

int main(){
    
    int w = 640;
    int h = 425;

    int img[h*w];

    // matriz de imagen y arreglo de funcion de ecualizacion

    ifstream archImg("/content/drive/My Drive/topicos en grafica/laboratorio 4/img.txt");
    if (!archImg.is_open()) cout<<"No se abrió el archivo\n";
  
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++)
            archImg >> img[i*w+j];
    archImg.close();

    ifstream archFuncion("/content/drive/My Drive/topicos en grafica/laboratorio 4/funcion.txt");
    if (!archFuncion.is_open()) cout<<"No se abrió el archivo\n";
  
    int funcion[256];
    for(int i=0; i<256; i++)
            archFuncion >> funcion[i];
    archFuncion.close();

    // proceso

    int *dev_img, *dev_funcion;

    cudaMalloc((void **) &dev_img, sizeof(int)*w*h);
    cudaMalloc((void **) &dev_funcion, sizeof(int)*256);

    cudaMemcpy(dev_img, img, sizeof(int)*w*h, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_funcion, funcion, sizeof(int)*256, cudaMemcpyHostToDevice);

    ecualizacion<<<h,w>>>(dev_img, dev_funcion);

    cudaMemcpy(img, dev_img, sizeof(int)*w*h, cudaMemcpyDeviceToHost);

    ofstream arch("/content/drive/My Drive/topicos en grafica/laboratorio 4/imgEcualizada.txt");

    for(int i=0; i<h; i++){
      for (int j=0; j<w; j++)
          arch<<img[i*w+j]<<"\n";
    }

    arch.close();

    cudaFree(dev_img);
    cudaFree(dev_funcion);

    cout<<"ok."<<'\n';

    return 0;
}
