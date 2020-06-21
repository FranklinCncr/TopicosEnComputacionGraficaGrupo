# Convolución en CUDA
## 2D

Imagen de ***entrada***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/5%20Convolucion%20en%20CUDA/imagenes/coliseo.jpg)

***Difuminación*** con un ***kernel de 9x9***:

![](https://github.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/blob/master/5%20Convolucion%20en%20CUDA/imagenes/salida.jpg)

### Lanzamiento del kernel

* dim3 blocks( h, w, kernelDim ); 
* dim3 threads( kernelDim, ch );  

Con ello se manejarán los rangos que se necesitan:

***blockIdx.x*** manejará el rango [0...h[

***blockIdx.y*** manejará el rango [0...w[
***blockId.z*** manejará el rango [0...9[
***threadIdx.x*** manejará el rango [0...9[
***threadIdx.y*** manejará el rango [0...3[
 
 conv<<<blocks,threads>>>(d_imgFR, d_kernel, d_salida, w, h, ch, kernelDim);
