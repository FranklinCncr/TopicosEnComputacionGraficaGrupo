%%cu
#include <stdio.h>
#include <math.h>
#include "iostream"
//Imagen de 10x10
#define SIZE	100
using namespace std;

__global__ void VectorAdd(int *a, int *r, int n, double gamma)
{
	int i=threadIdx.x;

	if(i<n)
		r[i] = (int)(255.0*pow((double)a[i]/255.0,1.0/gamma));
}

int main()
{
	int *a;
	int *r;
	double gamma=0.5;
	
	cudaMallocManaged(&a, SIZE * sizeof(int));
	cudaMallocManaged(&r, SIZE * sizeof(int));

	cout<<"Matriz de entrada"<<endl;

	for (int i = 1; i <= SIZE; ++i){
		a[i]=rand() % 255;
    cout<<a[i]<<"\t";
		if(i%10==0){
				cout<<endl;
		}
	}
		
	VectorAdd <<<1, SIZE>>> (a, r, SIZE, gamma);

  cudaDeviceSynchronize();

	cout<<"Matriz de salida con Gamma = 0.5"<<endl;

	for (int i = 1; i <= SIZE; ++i){
    cout<<r[i]<<"\t";
		if(i%10==0){
				cout<<endl;
		}
	}

	cudaFree(a);
	cudaFree(r);

	return 0;
}