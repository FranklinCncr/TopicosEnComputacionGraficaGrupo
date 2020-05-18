#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>

using namespace std;
#define NUM_THREADS 512
mutex g_pages_mutex;
unsigned t0, t1;
int i,j;
int f=1048576;//1024
int c=524288;//512;
int * lista=new int [c];
int ** matriz=new int* [f];
int pasos=0;
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
    /*i=0;
    cout<<"Imprime matriz"<<endl;
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
void* decir_hola(void *threadid)
{
    int indice = *((int*)threadid);
    cout << "ID : " <<indice<<endl;
    j=0;
    int cantidad=0;
    cout<<lista[indice]<<endl;

    i=0;
    while(i<=f-1){
        lista[indice]=lista[indice]+matriz[i][indice];
        i+=1;
    }


    pthread_exit(NULL);
}
int main()
{
    inicio();
     j=0;
    while(j<c){
        cout<<lista[j]<<"\t";
        j+=1;
    }

    pthread_t hilos[NUM_THREADS];
    int indexes[NUM_THREADS];
    t0=clock();

    for(int i = 0; i < NUM_THREADS; ++i)
    {
        indexes[i] = i;
        int ret = pthread_create(&hilos[i], NULL, decir_hola, (void *)&(indexes[i]) );
        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    // joining and waiting for all threads to complete
    void *status;
    int rc;

    for (int m = 0; m < NUM_THREADS; m++){
         rc = pthread_join(hilos[m], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         exit(-1);
      }
    }
    t1=clock();
    double time = (double(t1-t0));
    cout << "Tiempo en  milisegundos: " << time << endl;

    cout<<endl<<"Imprimiendo la lista"<<endl;

   j=0;
    while(j<c){
        cout<<lista[j]<<" \t ";
        j+=1;
    }

    return 0;
}
