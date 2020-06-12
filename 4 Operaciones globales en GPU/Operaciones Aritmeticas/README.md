## Estudiante : Erika Tamo Turpo
# Operaciones aritmeticas por GPU
En el archivo kernel.cu se encuentra los archivo en cuda, una anterior version se hizo en colab que se muestra en este archivo:
https://colab.research.google.com/drive/1Nq-QFTJVur_Y0zs3bETmRhJpiYjH67rG?usp=sharing

Sumando matrizes en cuda.Tambien se probo con opencv con python obteniendo similar resulado.

Primer imagen :A

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/4%20Operaciones%20globales%20en%20GPU/Operaciones%20Aritmeticas/imagenes/poesia.bmp)!

Segunda imagen :B
Imagen de entrada:

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/4%20Operaciones%20globales%20en%20GPU/Operaciones%20Aritmeticas/imagenes/poesia_2.bmp) 


Como se puede dar cuenta está imagen esta compuesta por un rectangula blanco y negro.

Entonces la suma de A+B con opencv y python:

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/4%20Operaciones%20globales%20en%20GPU/Operaciones%20Aritmeticas/imagenes/suma_resultado_py.bmp) 

Se observo que la funcion de opencv equaliza la imágen. Entonces lo sume A+B con ayuda de numpy. El resultado es el mismo al sumar en c++.

Se tiene que tener cuidado cuando se sobrepasa la cantidad de hilos sobrepase a los hilos de la computadora, porque simplemente ya no lo suma al sobrepasar, produciendo errores como:

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/4%20Operaciones%20globales%20en%20GPU/Operaciones%20Aritmeticas/imagenes/Salida_suma.bmp) 


Link del codigo: https://colab.research.google.com/drive/1Z2wNoO6rtSGv0ObOWTo4-2iNiajurbYZ?usp=sharing
