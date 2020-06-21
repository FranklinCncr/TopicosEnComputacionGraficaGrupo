# Convolución en CUDA
## 2D

Imagen de ***entrada***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/5%20Convolucion%20en%20CUDA/imagenes/coliseo.jpg)

***Difuminación*** con un ***kernel de 9x9***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/5%20Convolucion%20en%20CUDA/imagenes/salida.jpg)

### Lanzamiento del kernel

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/5%20Convolucion%20en%20CUDA/imagenes/estr.png)

Con ello se manejarán los rangos que se necesitan:

Bx es ***blockIdx.x*** manejará el rango [0...h[

By es***blockIdx.y*** manejará el rango [0...w[

Bz es ***blockId.z*** manejará el rango [0...9[

Tx es ***threadIdx.x*** manejará el rango [0...9[

Ty es ***threadIdx.y*** manejará el rango [0...3[

Entonces se tendrá:

* dim3 blocks( h, w, kernelDim ); 
* dim3 threads( kernelDim, ch ); //ch = canales 
* conv<<<blocks,threads>>>(d_imgFR, d_kernel, d_salida, w, h, ch, kernelDim);
