# Transformaciones Afines

Imagen de ***entrada***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/6%20Transformaciones%20afines%20en%20CUDA/Entrada/d1.jpg)

***Traslación*** de ***10 pixeles para las filas y columnas de la imagen***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/6%20Transformaciones%20afines%20en%20CUDA/Salida/salida_doraemon.jpg)

### Lanzamiento del kernel

Secuencia de proceso:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/6%20Transformaciones%20afines%20en%20CUDA/Entrada/explicacion.png)

Con ello se manejarán los rangos que se necesitan:

***blockIdx.x***, manejará el rango [0...M[

***threadIdx.x***, manejará el rango [0...N[

En donde M es el alto y N es el ancho.

Entonces se tendrá:

*SumaMatrizKernel_2 << < M, N >> > (N, M, Md_1, Md_3, chanales);

***Probandolo***

Para poder rellenar la fila y columna faltantes cuando se traslada, se hizo el promedio de los vecinos(arriba,abajo,derecha,izquierda) de la imagen de entrada :
Imagen de ***entrada***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/6%20Transformaciones%20afines%20en%20CUDA/Entrada/d2.jpg)

***Traslación*** de ***1 posiciones***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/6%20Transformaciones%20afines%20en%20CUDA/Salida/salida.jpg)
