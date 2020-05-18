#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>
//maximo numero es 0.15
using namespace std;
#define NUM_THREADS 100
mutex g_pages_mutex;
unsigned t0, t1;
int i,j;
int f=4096;
int c=2048;
int * lista=new int [c];
int ** matriz=new int* [f];
void suma_secuencial(){
    i=0;
    while (i<f){
        j=0;
        while (j<c){
            matriz[i][j]=1;
            j+=1;
        }
        i+=1;
    }

    i=j=0;
    t0=clock();
    while(i<f){
        int j=0;
        while(j<c){
            lista[i]+=matriz[i][j];
            j+=1;
        }
        i+=1;
    }
    // Code to execute

    t1 = clock();
    double time = (double(t1-t0));
    //cout<<"Erika tu puedes "<<CLOCKS_PER_SEC<<endl;
    cout << "Tiempo en milisegundos: " << time << endl;
    j=0;
    while(j<c){
        cout<<lista[j]<<"\t";
        j+=1;
    }

}


void inicio(){
    matriz=new int* [f];
    i=0;
    while (i<f){
        matriz[i]=new int [c];
        i+=1;
    }
    i=0;
    while(i<c){
        lista[i]=0;
        i+=1;
        //cout<<"lista"<<lista[i]<<endl;
    }
    i=0;
    while (i<f){
        j=0;
        while(j<c){
            matriz[i][j]=1;
            j+=1;

        }
        i+=1;
    }
    i=0;
    /*cout<<"Imprime matriz"<<endl;
    while(i<f){
        j=0;
        while(j<c){
            cout<<matriz[i][j]<<" ";
            j+=1;
        }
        i+=1;
        cout<<endl;
    }*/
}
int main()
{

    inicio();
    suma_secuencial();

    return 0;
}
